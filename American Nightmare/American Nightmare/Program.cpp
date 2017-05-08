#include "Program.h"

Program::Program()
{
	screenManager = nullptr;
	window = nullptr;
}

Program::Program(const Program& other) { }

Program::~Program() { }

bool Program::Start()
{
	srand(time_t(NULL));
	
	////////////////////////////////////////////////////////////
	// Creating a window for the program
	////////////////////////////////////////////////////////////
	StartSDLWindow();

	////////////////////////////////////////////////////////////
	// Creating Grahpics Object
	// - Updates & Renders Graphics
	////////////////////////////////////////////////////////////
	screenManager = new ScreenManager();
	if (screenManager == nullptr) return false;
	if (!screenManager->Start(screenSize, glm::vec2(posX, posY), hwnd))
	{
		MessageBox(hwnd, L"Could not start ScreenManager class.", L"Woops", MB_OKCANCEL);
		return false;
	}

	return true;
}

void Program::StartSDLWindow()
{
	screenSize = DEFAULT_SCREEN_SIZE;
	appName = APP_NAME;

	// Initialize SDL
	SDL_Init(SDL_INIT_EVERYTHING);

	// Initialize SDL text
	if (TTF_Init() == -1)
		std::runtime_error("Could not start SDL-TTF, Check your External Folder! Updated Version on Github ReadMe File.");

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	// Creating window
	if (FULL_SCREEN_ON) {
		window = SDL_CreateWindow(appName.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_OPENGL);
		screenSize.x = GetSystemMetrics(SM_CXSCREEN);
		screenSize.y = GetSystemMetrics(SM_CYSCREEN);
	}
	else {
		window = SDL_CreateWindow(appName.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenSize.x, screenSize.y, SDL_WINDOW_OPENGL);
	}



	context = SDL_GL_CreateContext(window);

	// Activate v-sync
	SDL_GL_SetSwapInterval(1);

	// Getting Windowhandl
	SDL_SysWMinfo systemInfo;
	SDL_VERSION(&systemInfo.version);
	SDL_GetWindowWMInfo(window, &systemInfo);

	// Getting window position
	SDL_GetWindowPosition(window, &posX, &posY);

	hwnd = systemInfo.info.win.window;

	glewExperimental = GL_TRUE;

	// Initialize GLEW
	if (glewInit() != GLEW_OK)
	{
		printf("%s", glewGetErrorString(glewInit()));
		throw std::runtime_error("Could not initialize GLEW");
		return;
	}

	// Setting various OpenGL settings, check header for variables
	glViewport(0, 0, screenSize.x, screenSize.y);
	glEnable(GL_DEPTH_TEST);						// Enable Depth test
	glClearDepth(1);								// Threshold for depthbuffer to clear
	glDepthFunc(GL_LESS);
	//glFrontFace(GL_CW);							// ClockWise = CW, CounterClockWise = CCW
	glEnable(GL_CULL_FACE);							// Enable Culling
	glCullFace(GL_BACK);							// GL_BACK is default, (backculling), we can also use GL_FRONT, and GL_FRONT_AND_BACK if needed
	glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//glEnable(GL_FRAMEBUFFER_SRGB);				// Gamma correction
}

void Program::Stop()
{
	// Deleting graphics
	if (screenManager != nullptr)
	{
		screenManager->Stop();
		delete screenManager;
		screenManager = nullptr;
	}

	StopWindow();
}

bool Program::Run()
{
	// Making the msg spot in memory, filling it with zeros
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));
	SDL_Event event;

	GLint deltaT = 0;
	Uint32 lastFrameTime = 0;

	bool done = false;
	while (!done)
	{
		Uint32 currentTime = SDL_GetTicks();
		deltaT = (currentTime - lastFrameTime);
		lastFrameTime = currentTime;

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				done = true;
		}

		// Updating everything
		if (!Update(deltaT))
			done = true;
	}

	return false;
}

void Program::StopWindow()
{
	// Showing the mouse cursor 
	if (!SHOW_CURSOR)
		ShowCursor(true);

	// Destroy window
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	TTF_Quit();
	SDL_Quit();
}

bool Program::Update(GLint deltaT)
{
	// Check if user exits
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
		return false;

	if (screenManager->getState() == Exit)
		return false;

	// Update game
	screenManager->Update(deltaT);

	// Draw game
	screenManager->Draw(window, glm::vec4(0.f, 0.f, 0.f, 1.f));

	return true;
}