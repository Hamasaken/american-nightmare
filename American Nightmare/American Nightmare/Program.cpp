#include "Program.h"

Program::Program()
{
	m_game = nullptr;
	m_openGL = nullptr;
}

Program::Program(const Program& other) { }

Program::~Program() { }

bool Program::Start()
{
	srand(time_t(NULL));
	m_screenSize = DEFAULT_SCREEN_SIZE;

	////////////////////////////////////////////////////////////
	// Creating OpenGL Object, check StartWindow for more openGL initializing
	////////////////////////////////////////////////////////////
	m_openGL = new OpenGL();
	if (m_openGL == nullptr) return false;

	////////////////////////////////////////////////////////////
	// Creating a window for the program
	////////////////////////////////////////////////////////////
	StartWindow();

	////////////////////////////////////////////////////////////
	// Creating Grahpics Object
	// - Updates & Renders Graphics
	////////////////////////////////////////////////////////////
	m_game = new Game();
	if (m_game == nullptr) return false;
	if (!m_game->Start(m_openGL, m_hwnd))
	{
		MessageBox(m_hwnd, L"Could not start Game class.", L"Woops", MB_OKCANCEL);
		return false;
	}

	// Setting self-pointer
	pgr = this;

	return true;
}

void Program::Stop() 
{
	// Deleting graphics
	if (m_game != nullptr)
	{
		m_game->Stop();
		delete m_game;
		m_game = nullptr;
	}

	// Deleting openGL
	if (m_openGL != nullptr)
	{
		m_openGL->Stop(m_hwnd);
		delete m_openGL;
		m_openGL = nullptr;
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
	m_hInstance = GetModuleHandle(NULL);

	// Application name
	m_appName = APP_NAME;

	// Windows class setup, default settings
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc; // This is where we want the window messages to be sent to
	wc.cbClsExtra = NULL;
	wc.cbWndExtra = NULL;
	wc.hInstance = m_hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = m_appName.c_str();
	wc.cbSize = sizeof(WNDCLASSEX);

	// Register the windows class (!remember,  RegisterClassExA (expect msg's with ANSI), RegisterClass ExW for expecting msg's with Unicode)
	RegisterClassEx(&wc);

	// Creating the temp window
	m_hwnd = CreateWindowEx(WS_EX_APPWINDOW, m_appName.c_str(), m_appName.c_str(), WS_POPUP,
		0, 0, m_screenSize.x, m_screenSize.y, NULL, NULL, m_hInstance, NULL);

	// Setting window as hidden for now
	ShowWindow(m_hwnd, SW_HIDE);
	if (!m_openGL->StartExtentions(m_hwnd))
	{
		MessageBox(m_hwnd, L"Could not start openGL extentions.", L"Woops", MB_OKCANCEL);
		return false;
	}

	// Destroying tempwindow
	DestroyWindow(m_hwnd);
	m_hwnd = NULL;

	// Getting resolution from computer
	m_screenSize.x = GetSystemMetrics(SM_CXSCREEN);
	m_screenSize.y = GetSystemMetrics(SM_CYSCREEN);

	// Fullscreen or not, different settings
	if (FULL_SCREEN_ON)
	{
		// If full screen set the screen to maximum size of the users desktop and 32bit.
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = (unsigned long)m_screenSize.x;
		dmScreenSettings.dmPelsHeight = (unsigned long)m_screenSize.y;
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
		m_screenSize = DEFAULT_SCREEN_SIZE;

		// Placing the window in the center 
		posX = (GetSystemMetrics(SM_CXSCREEN) - m_screenSize.x) / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - m_screenSize.y) / 2;
	}

	m_hwnd = CreateWindowEx(WS_EX_APPWINDOW, m_appName.c_str(), m_appName.c_str(), WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
		posX, posY, m_screenSize.x, m_screenSize.y, NULL, NULL, m_hInstance, NULL);

	// Starting openGL now that extentions are in place
	if (!m_openGL->StartOpenGL(m_hwnd, DEFAULT_SCREEN_SIZE, SCREEN_DEPTH, SCREEN_NEAR, VSYNC_ON))
	{
		MessageBox(m_hwnd, L"Could not start OpenGL, check if video card supports it.", L"Woops", MB_OKCANCEL);
		return false;
	}

	// Setting window to show and setting it as focus
	ShowWindow(m_hwnd, SW_SHOW);
	SetForegroundWindow(m_hwnd);
	SetFocus(m_hwnd);

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
	DestroyWindow(m_hwnd);
	m_hwnd = NULL;

	// Unregister window & setting hinstance to 0
	UnregisterClass(m_appName.c_str(), m_hInstance);
	m_hInstance = NULL;
} 

bool Program::Update() 
{
	// Check if user exits
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
		return false;

	// Update game
	if (!m_game->Update())
		return false;

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