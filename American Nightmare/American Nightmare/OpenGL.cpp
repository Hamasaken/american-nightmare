#include "OpenGL.h"

OpenGL::OpenGL()
{
	deviceContext = nullptr;
	renderingContext = nullptr;
}

OpenGL::OpenGL(const OpenGL & other) { }

OpenGL::~OpenGL() { }

bool OpenGL::StartExtentions(HWND hwnd) 
{
	// Creating some temp contexts
	HDC tempDeviceContext = nullptr;
	HGLRC tempRenderContext = nullptr;
	PIXELFORMATDESCRIPTOR tempPixelFormat;
	int error;

	// Getting window device context from hwnd
	tempDeviceContext = GetDC(hwnd);
	if (tempDeviceContext == nullptr) return false;

	// Setting default pixel format from the information in deviceContext
	error = SetPixelFormat(tempDeviceContext, 1, &tempPixelFormat);
	if (error != 1) return false;

	// Setting Render Context
	tempRenderContext = wglCreateContext(tempDeviceContext);
	if (tempRenderContext == nullptr) return false;

	// Setting the rendering context on the window
	error = wglMakeCurrent(tempDeviceContext, tempRenderContext);
	if (error != 1) return false;

	// Getting every function pointer
	if (!LoadExtentions()) return false;

	// We can now remove the temporary contexts
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(tempRenderContext);
	tempRenderContext = nullptr;
	ReleaseDC(hwnd, tempDeviceContext);
	tempDeviceContext = nullptr;

	return true;
}

bool OpenGL::LoadExtentions() 
{
	// Getting pointers to functions

	wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)wglGetProcAddress("wglChoosePixelFormatARB");
	if (!wglChoosePixelFormatARB) return false;

	wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");
	if (!wglCreateContextAttribsARB) return false;

	wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");
	if (!wglSwapIntervalEXT) return false;

	glAttachShader = (PFNGLATTACHSHADERPROC)wglGetProcAddress("glAttachShader");
	if (!glAttachShader) return false;

	glBindBuffer = (PFNGLBINDBUFFERPROC)wglGetProcAddress("glBindBuffer");
	if (!glBindBuffer) return false;

	glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)wglGetProcAddress("glBindVertexArray");
	if (!glBindVertexArray) return false;

	glBufferData = (PFNGLBUFFERDATAPROC)wglGetProcAddress("glBufferData");
	if (!glBufferData) return false;

	glCompileShader = (PFNGLCOMPILESHADERPROC)wglGetProcAddress("glCompileShader");
	if (!glCompileShader) return false;

	glCreateProgram = (PFNGLCREATEPROGRAMPROC)wglGetProcAddress("glCreateProgram");
	if (!glCreateProgram) return false;

	glCreateShader = (PFNGLCREATESHADERPROC)wglGetProcAddress("glCreateShader");
	if (!glCreateShader) return false;

	glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)wglGetProcAddress("glDeleteBuffers");
	if (!glDeleteBuffers) return false;

	glDeleteProgram = (PFNGLDELETEPROGRAMPROC)wglGetProcAddress("glDeleteProgram");
	if (!glDeleteProgram) return false;

	glDeleteShader = (PFNGLDELETESHADERPROC)wglGetProcAddress("glDeleteShader");
	if (!glDeleteShader) return false;

	glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)wglGetProcAddress("glDeleteVertexArrays");
	if (!glDeleteVertexArrays) return false;

	glDetachShader = (PFNGLDETACHSHADERPROC)wglGetProcAddress("glDetachShader");
	if (!glDetachShader) return false;

	glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)wglGetProcAddress("glEnableVertexAttribArray");
	if (!glEnableVertexAttribArray) return false;

	glGenBuffers = (PFNGLGENBUFFERSPROC)wglGetProcAddress("glGenBuffers");
	if (!glGenBuffers) return false;

	glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)wglGetProcAddress("glGenVertexArrays");
	if (!glGenVertexArrays) return false;

	glGetAttribLocation = (PFNGLGETATTRIBLOCATIONPROC)wglGetProcAddress("glGetAttribLocation");
	if (!glGetAttribLocation) return false;

	glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)wglGetProcAddress("glGetProgramInfoLog");
	if (!glGetProgramInfoLog) return false;

	glGetProgramiv = (PFNGLGETPROGRAMIVPROC)wglGetProcAddress("glGetProgramiv");
	if (!glGetProgramiv) return false;

	glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)wglGetProcAddress("glGetShaderInfoLog");
	if (!glGetShaderInfoLog) return false;

	glGetShaderiv = (PFNGLGETSHADERIVPROC)wglGetProcAddress("glGetShaderiv");
	if (!glGetShaderiv) return false;

	glLinkProgram = (PFNGLLINKPROGRAMPROC)wglGetProcAddress("glLinkProgram");
	if (!glLinkProgram) return false;

	glShaderSource = (PFNGLSHADERSOURCEPROC)wglGetProcAddress("glShaderSource");
	if (!glShaderSource) return false;

	glUseProgram = (PFNGLUSEPROGRAMPROC)wglGetProcAddress("glUseProgram");
	if (!glUseProgram) return false;

	glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)wglGetProcAddress("glVertexAttribPointer");
	if (!glVertexAttribPointer) return false;

	glBindAttribLocation = (PFNGLBINDATTRIBLOCATIONPROC)wglGetProcAddress("glBindAttribLocation");
	if (!glBindAttribLocation) return false;

	glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)wglGetProcAddress("glGetUniformLocation");
	if (!glGetUniformLocation) return false;

	glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)wglGetProcAddress("glUniformMatrix4fv");
	if (!glUniformMatrix4fv) return false;

	glActiveTexture = (PFNGLACTIVETEXTUREPROC)wglGetProcAddress("glActiveTexture");
	if (!glActiveTexture) return false;

	glUniform1i = (PFNGLUNIFORM1IPROC)wglGetProcAddress("glUniform1i");
	if (!glUniform1i) return false;

	glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC)wglGetProcAddress("glGenerateMipmap");
	if (!glGenerateMipmap) return false;

	glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC)wglGetProcAddress("glDisableVertexAttribArray");
	if (!glDisableVertexAttribArray) return false;

	glUniform3fv = (PFNGLUNIFORM3FVPROC)wglGetProcAddress("glUniform3fv");
	if (!glUniform3fv) return false;

	glUniform4fv = (PFNGLUNIFORM4FVPROC)wglGetProcAddress("glUniform4fv");
	if (!glUniform4fv) return false;

	return true;
}

bool OpenGL::StartOpenGL(HWND hwnd, glm::vec2 screenSize, float screenDepth, float screenNear, bool vSyncOn) 
{
	// Result variables
	int result;

	// Getting the device context from active window
	deviceContext = GetDC(hwnd);
	if (deviceContext == nullptr) return false;

	// Setting up settings and supports for different things.
	// Feel free to change stuff
	int attributes[19] =
	{
		WGL_SUPPORT_OPENGL_ARB, TRUE,						// Support for OpenGL rendering
		WGL_DRAW_TO_WINDOW_ARB, TRUE,						// Support for rendering to a window
		WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,	// Support for hardware acceleration
		WGL_COLOR_BITS_ARB, 24,								// Amount of color bits
		WGL_DEPTH_BITS_ARB, 24,								// Amount of depth buffer bits
		WGL_DOUBLE_BUFFER_ARB, TRUE,						// Support for double buffer
		WGL_SWAP_METHOD_ARB, WGL_SWAP_EXCHANGE_ARB,			// Support for swapping back and front buffer
		WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,				// Which type of pixel type
		WGL_STENCIL_BITS_ARB, 8,							// Amount of stencil bits
		NULL,												// End
	};

	// Query the pixel format with the attributes, note: returns false if video card can't handle it
	int pixelFormat;
	UINT numFormats;
	result = wglChoosePixelFormatARB(deviceContext, attributes, NULL, 1, &pixelFormat, &numFormats);
	if (result != 1) return false;

	// Setting the pixel format
	PIXELFORMATDESCRIPTOR pixelFormatDescriptor;
	result = SetPixelFormat(deviceContext, pixelFormat, &pixelFormatDescriptor);
	if (result != 1) return false;

	// Setting the current OpenGL version to the rendering context
	int attributesVersion[5] =
	{
		WGL_CONTEXT_MAJOR_VERSION_ARB, 4,	// Major OpenGL version
		WGL_CONTEXT_MINOR_VERSION_ARB, 0,	// Minor OpenGL version
		NULL								// End
	};
	renderingContext = wglCreateContextAttribsARB(deviceContext, NULL, attributesVersion);
	if (renderingContext == nullptr) return false;

	// Activating the rendering context
	result = wglMakeCurrent(deviceContext, renderingContext);
	if (result != 1) return false;

	// Setting various OpenGL settings, check header for variables
	glViewport(0, 0, screenSize.x, screenSize.y);
	glClearDepth(DEPTH_BUFFER_CLEAR);				// Threshold for depthbuffer to clear
	glFrontFace(GL_CW);								// ClockWise = CW, CounterClockWise = CCW
	glEnable(GL_CULL_FACE);							// Enable Culling
	glCullFace(GL_BACK);							// GL_BACK is default, (backculling), we can also use GL_FRONT, and GL_FRONT_AND_BACK if needed
	glEnable(GL_DEPTH_TEST);						// Enable Depth test

	// Building a world matrix (just identity matrix)
	worldMatrix = glm::mat4(1.f);

	// Building a projection matrix
	float fov = glm::pi<float>() / 0.40f;
	projectionMatrix = glm::perspective(fov, screenSize.x / screenSize.y, screenNear, screenDepth);

	// Setting vSync on/off
	result = (vSyncOn) ? wglSwapIntervalEXT(1) : wglSwapIntervalEXT(0);
	if (result != 1) return false;

	return true;
}

void OpenGL::Stop(HWND hwnd) 
{
	// Deleting the rendering context
	if (renderingContext != nullptr) 
	{
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(renderingContext);
		renderingContext = nullptr;
	}
	
	// Deleting the device context
	if (deviceContext != nullptr)
	{
		ReleaseDC(hwnd, deviceContext);
		deviceContext = nullptr;
	}
}

void OpenGL::StartDraw(glm::vec4 color) 
{
	// Clearing the screen to the clear color
	glClearColor(color.r, color.g, color.b, color.a);

	// Cleaning screen & depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	///////////////////////////////////////////////////////////////////////
	// GL_COLOR_BUFFER_BIT		- Indicates that the buffers are using colors
	// GL_DEPTH_BUFFER_BIT		- Indicates the depth buffer
	// GL_ACCUBUFFER_BIT		- Indicates the accumulation buffer
	// GL_STENCIL_BUFFER_BIT	- Indicates the stencil buffer
	///////////////////////////////////////////////////////////////////////
}

void OpenGL::EndDraw() 
{
	// Changing to back buffer since rendering is completed
	SwapBuffers(deviceContext);
}

glm::mat4 OpenGL::getWorldMatrix() { return worldMatrix; }
glm::mat4 OpenGL::getProjectionMatrix() { return projectionMatrix; } 
