#include <application/window.hpp>
#include <application/exception.hpp>

#include <graphics/sprite.hpp>
#include <graphics/sprites/all.hpp>

#define WINDOW_CLASSNAME "spherical"  // Window class name

namespace spherical
{
	window::window (int iWidth, int iHeight, bool bFullScreen) : m_hWindow(NULL), m_hDeviceContext(NULL), m_hGLContext(NULL),

		m_bFullScreen(bFullScreen) {

		registerWindowClass();
		RECT WindowRect;
		WindowRect.top = WindowRect.left = 0;
		WindowRect.right = iWidth;
		WindowRect.bottom = iHeight;

		// Window Extended Style
		DWORD dwExStyle = 0;

		// Windows Style
		DWORD dwStyle = 0;

		if (m_bFullScreen) 
		{
			DEVMODE dmScreenSettings;
			memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
			dmScreenSettings.dmSize = sizeof(dmScreenSettings);
			dmScreenSettings.dmPelsWidth = iWidth;
			dmScreenSettings.dmPelsHeight = iHeight;
			dmScreenSettings.dmBitsPerPel = 32;
			dmScreenSettings.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL;

			// Change the display settings to fullscreen. On error, throw 
			// an exception.
			if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
				throw exception("Unable to swith to fullscreen mode");

			dwExStyle = WS_EX_APPWINDOW;
			dwStyle = WS_POPUP;

			// In fullscreen mode, we hide the cursor.
			ShowCursor(FALSE);
		}
		else 
		{
			dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
			dwStyle = WS_OVERLAPPEDWINDOW;
		}

		// Adjust the window to the true requested size
		AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);

		// Now create the main window
		m_hWindow = CreateWindowEx(dwExStyle, TEXT(WINDOW_CLASSNAME),
			TEXT("Tutorial1"),
			WS_CLIPSIBLINGS | WS_CLIPCHILDREN | dwStyle,
			0, 0, WindowRect.right - WindowRect.left,
			WindowRect.bottom - WindowRect.top,
			NULL, NULL,
			GetModuleHandle(NULL),
			this);

		if (m_hWindow == NULL)
			throw exception("Cannot create the main window");

		createContext();
		initGL();
		ShowWindow(m_hWindow, SW_SHOW);

		// Call OnSize manually because in fullscreen mode it will be 
		// called only when the window is created (which is too early
		// because OpenGL is not initialized yet).
		onSize(iWidth, iHeight);
	}

	window::~window () {

		if (m_bFullScreen) {
			// Remove the full screen setting
			ChangeDisplaySettings(NULL, 0);
			ShowCursor(TRUE);
		}

		if (m_hGLContext) {
			// Make the rendering context not current
			wglMakeCurrent(NULL, NULL);

			// Delete the OpenGL rendering context
			wglDeleteContext(m_hGLContext);
			m_hGLContext = NULL;
		}

		if (m_hDeviceContext) {

			// Release the device context
			ReleaseDC(m_hWindow, m_hDeviceContext);
			m_hDeviceContext = NULL;

		}

		// Finally, destroy our main window and unregister the
		// window class.
		DestroyWindow(m_hWindow);
		UnregisterClass(TEXT(WINDOW_CLASSNAME), GetModuleHandle(NULL));
	}

	LRESULT window::onEvent(HWND handle, UINT message, WPARAM wParam, LPARAM lParam) 
	{
		if (message == WM_NCCREATE) 
		{
			// Get the creation parameters.
			CREATESTRUCT* pCreateStruct = reinterpret_cast<CREATESTRUCT*>(lParam);

			// Set as the "user data" parameter of the window
			SetWindowLongPtr(handle, GWLP_USERDATA,
				reinterpret_cast<long>(pCreateStruct->lpCreateParams));

		}

		// Get the window  instance corresponding to the window handle

		window * pWindow = reinterpret_cast<window *>(GetWindowLongPtr(handle, GWLP_USERDATA));
		if (pWindow) pWindow->processEvent(message, wParam, lParam);
		return DefWindowProc(handle, message, wParam, lParam);

	}

	void window::processEvent(UINT message, WPARAM wParam, LPARAM lParam) 
	{
		switch (message)
		{
			case WM_CLOSE:										// Quit when we close the main window
				PostQuitMessage(0);
				break;

			case WM_SIZE:
				onSize(LOWORD(lParam), HIWORD(lParam));
				break;

			case WM_CHAR:
			{
				switch (wParam)
				{
					case 17:
					{
						if (GetKeyState(VK_CONTROL) & 0x8000)
						{
							PostQuitMessage(0);
						}
					}
				}
			}
			case WM_KEYDOWN:
			{
				int i = 0;
				break;
			}

		
			case WM_KEYUP:
			{
				int j = 0;
				break;
			}
		}
	}

	void window::registerWindowClass() 
	{
		WNDCLASS WindowClass;
		WindowClass.style			= 0;
		WindowClass.lpfnWndProc		= &window ::onEvent;
		WindowClass.cbClsExtra		= 0;
		WindowClass.cbWndExtra		= 0;
		WindowClass.hInstance		= GetModuleHandle(NULL);
		WindowClass.hIcon			= NULL;
		WindowClass.hCursor			= 0;
		WindowClass.hbrBackground	= 0;
		WindowClass.lpszMenuName	= NULL;
		WindowClass.lpszClassName	= TEXT(WINDOW_CLASSNAME);
		RegisterClass(&WindowClass);
	}

	bool window::createContext()
	{
		PIXELFORMATDESCRIPTOR pfd;						// Describes the pixel format of the drawing surface
		memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
		pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
		pfd.nVersion = 1;								// Version Number
		pfd.dwFlags = 
			PFD_DRAW_TO_WINDOW |						// Draws to a window
			PFD_SUPPORT_OPENGL |						// The format must support OpenGL
			PFD_DOUBLEBUFFER;							// Support for double buffering

		pfd.iPixelType = PFD_TYPE_RGBA;					// Uses an RGBA pixel format
		pfd.cColorBits = 32;							// 32 bits colors

		if (!(m_hDeviceContext = GetDC(m_hWindow)))
			throw exception("Unable to create rendering context");

		int PixelFormat;

		// Do Windows find a matching pixel format ?
		if (!(PixelFormat = ChoosePixelFormat(m_hDeviceContext, &pfd)))
			throw exception("Unable to create rendering context");

		// Set the new pixel format
		if (!SetPixelFormat(m_hDeviceContext, PixelFormat, &pfd))
			throw exception("Unable to create rendering context");

		// Create the OpenGL rendering context
		if (!(m_hGLContext = wglCreateContext(m_hDeviceContext)))
			throw exception("Unable to create rendering context");

		// Activate the rendering context
		if (!wglMakeCurrent(m_hDeviceContext, m_hGLContext))
			throw exception("Unable to create rendering context");
		return true;
	}

	void window::initGL()
	{
		glEnable(GL_TEXTURE_2D);						// Enable 2D texturing
		glShadeModel(GL_SMOOTH);						// Choose a smooth shading model
		glClearColor(0.0, 0.0, 0.0, 0.0);				// Set the clear color to black
		glEnable(GL_ALPHA_TEST);						// enable alpha
		glAlphaFunc(GL_GREATER, 0.0f);
	}

	void window::onSize(GLsizei width, GLsizei height) 
	{
		// Sets the size of the OpenGL viewport
		glViewport(0, 0, width, height);

		// Select the projection stack and apply 
		// an orthographic projection
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0.0, width, height, 0.0, -1.0, 1.0);
		glMatrixMode(GL_MODELVIEW);
	}

	void window::loadObjects()
	{
		m_sprites.emplace_back(new graphics::square());
		m_sprites.emplace_back(new graphics::triangle());
	}

	void window::update(DWORD dwCurrentTime) {}

	void window::draw()
	{
		// Clear the buffer
		glClear(GL_COLOR_BUFFER_BIT);

		for (auto& it : m_sprites)
		{
			it->draw();
		}

		for (int i = 0; i < 20; i++) 
		{
			// vertical lines
			glBegin(GL_LINE);
			glColor3f(1.0, 0.0, 1.0);  glVertex3i(50 * i, 0, 0);
			glColor3f(0.0, 1.0, 0.0);  glVertex3i(50 * i, 600, 0);
			glEnd();
			
			// horizontal lines
			glBegin(GL_LINE);
			glColor3f(0.0, 1.0, 0.0);  glVertex3i(0, 50 * i, 0);
			glColor3f(1.0, 0.0, 1.0);  glVertex3i(1000, 50 * i, 0);
			glEnd();
		}
		SwapBuffers(m_hDeviceContext);
	}
}
