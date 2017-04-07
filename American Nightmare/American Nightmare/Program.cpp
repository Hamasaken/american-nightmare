#include "Program.h"

Program::Program()
{
	screenManager = nullptr;
	openGL = nullptr;
}

Program::Program(const Program& other) { }

Program::~Program() { }

bool Program::Start()
{
	srand(time_t(NULL));
	screenSize = DEFAULT_SCREEN_SIZE;

	////////////////////////////////////////////////////////////
	// Creating OpenGL Object, check StartWindow for more openGL initializing
	////////////////////////////////////////////////////////////
	openGL = new OpenGL();
	if (openGL == nullptr) return false;

	////////////////////////////////////////////////////////////
	// Creating a window for the program
	////////////////////////////////////////////////////////////
	StartWindow();
	// StartSFMLWindow();

	////////////////////////////////////////////////////////////
	// Creating Grahpics Object
	// - Updates & Renders Graphics
	////////////////////////////////////////////////////////////
	screenManager = new ScreenManager();
	if (screenManager == nullptr) return false;
	if (!screenManager->Start(hwnd, openGL))
	{
		MessageBox(hwnd, L"Could not start ScreenManager class.", L"Woops", MB_OKCANCEL);
		return false;
	}

	// Setting self-pointer
	pgr = this;

	return true;
}

void Program::StartSFMLWindow()
{
	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 4;
	settings.majorVersion = 3;
	settings.minorVersion = 0;

	sf::Uint32 style = (FULL_SCREEN_ON ? sf::Style::Fullscreen : sf::Style::Default);

	sf::Window window(sf::VideoMode(screenSize.x, screenSize.y), appName, style, settings);
	window.setVerticalSyncEnabled(VSYNC_ON);

	// How the fuck do I get the HWND
	hwnd = window.getSystemHandle();
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

	// Deleting openGL
	if (openGL != nullptr)
	{
		openGL->Stop(hwnd);
		delete openGL;
		openGL = nullptr;
	}

	pgr = nullptr;

	StopWindow();
}

bool Program::Run()
{
	// Making the msg spot in memory, filling it with zeros
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	bool done = false;
	while (!done)
	{
		// Windows sends messages direcly to callback function, but some are placed in queue. (keyboard/mouse inputs mostly)
		// Each loop, we check if something is in the queue. If one is found, we translate it and dispatch it.
		if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
		{
			TranslateMessage(&msg); // converts virtual keys messages to character input messages
			DispatchMessage(&msg); // sends message of to window procedure 
		}

		// Checking to see if windows signals to quit
		if (msg.message == WM_QUIT)
			done = true;

		// Updating everything
		if (!Update())
			done = true;
	}

	return false;
}

bool Program::StartWindow()
{
	// We're using extended just in case I want to change window style some day 
	WNDCLASSEX wc;
	DEVMODE dmScreenSettings;
	int posX, posY;

	// Get instance of this program
	hInstance = GetModuleHandle(NULL);

	// Application name
	appName = APP_NAME;

	// Windows class setup, default settings
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc; // This is where we want the window messages to be sent to
	wc.cbClsExtra = NULL;
	wc.cbWndExtra = NULL;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = appName.c_str();
	wc.cbSize = sizeof(WNDCLASSEX);

	// Register the windows class (!remember,  RegisterClassExA (expect msg's with ANSI), RegisterClass ExW for expecting msg's with Unicode)
	RegisterClassEx(&wc);

	// Creating the temp window
	hwnd = CreateWindowEx(WS_EX_APPWINDOW, appName.c_str(), appName.c_str(), WS_BORDER,
		0, 0, screenSize.x, screenSize.y, NULL, NULL, hInstance, NULL);

	// Setting window as hidden for now
	ShowWindow(hwnd, SW_HIDE);
	if (!openGL->StartExtentions(hwnd))
	{
		MessageBox(hwnd, L"Could not start openGL extentions.", L"Woops", MB_OKCANCEL);
		return false;
	}

	// Destroying tempwindow
	DestroyWindow(hwnd);
	hwnd = NULL;

	// Getting resolution from computer
	screenSize.x = GetSystemMetrics(SM_CXSCREEN);
	screenSize.y = GetSystemMetrics(SM_CYSCREEN);

	// Fullscreen or not, different settings
	if (FULL_SCREEN_ON)
	{
		// If full screen set the screen to maximum size of the users desktop and 32bit.
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = (unsigned long)screenSize.x;
		dmScreenSettings.dmPelsHeight = (unsigned long)screenSize.y;
		dmScreenSettings.dmBitsPerPel = 64;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Change the display settings to full screen.
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		// Put window in upper-left corner.
		posX = posY = NULL;
	}
	else
	{
		// Setting to default for this application (graphicsclass.h)
		screenSize = DEFAULT_SCREEN_SIZE;

		// Placing the window in the center 
		posX = (GetSystemMetrics(SM_CXSCREEN) - screenSize.x) / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - screenSize.y) / 2;
	}

	// Creating window
	hwnd = CreateWindowEx(WS_EX_APPWINDOW, appName.c_str(), appName.c_str(), WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_CAPTION | WS_SYSMENU | WS_MAXIMIZEBOX | WS_MINIMIZEBOX,
		posX, posY, screenSize.x, screenSize.y, NULL, NULL, hInstance, NULL);

	// Starting openGL now that extentions are in place
	if (!openGL->StartOpenGL(hwnd, screenSize, SCREEN_DEPTH, SCREEN_NEAR, VSYNC_ON))
	{
		MessageBox(hwnd, L"Could not start OpenGL, check if video card supports it.", L"Woops", MB_OKCANCEL);
		return false;
	}

	// Setting window to show and setting it as focus
	ShowWindow(hwnd, SW_SHOW);
	SetForegroundWindow(hwnd);
	SetFocus(hwnd);

	// If the mouse should be hidden or not
	ShowCursor(SHOW_CURSOR);

	return true;
}

void Program::StopWindow()
{
	// Showing the mouse cursor 
	if (!SHOW_CURSOR)
		ShowCursor(true);

	// Fix settings if we were just in fullscreen mode
	if (FULL_SCREEN_ON)
		ChangeDisplaySettings(NULL, NULL);

	// Destroy window
	DestroyWindow(hwnd);
	hwnd = NULL;

	// Unregister window & setting hinstance to 0
	UnregisterClass(appName.c_str(), hInstance);
	hInstance = NULL;
}

bool Program::Update()
{
	// Check if user exits
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
		return false;

	// Update game
	screenManager->Update();

	// Draw game
	screenManager->Draw();

	return true;
}

static LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
	switch (umessage)
	{
		// Check if we're closed 
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;

		// Other messages are being sent to our msg handler
	default:
		return DefWindowProc(hwnd, umessage, wparam, lparam);
	}
}