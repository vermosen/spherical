#ifndef APPLICATION_WINDOW_HPP
#define APPLICATION_WINDOW_HPP

#include <Windows.h>
#include "GL/gl.h"

// The main window class. It wraps the HANDLE of the window and initializes the 
// openGL rendering context. It is also in charge of processing the different
// event messages.
namespace spherical
{
	class window 
	{
	public:

		window(int iWidth, int iHeight, bool bFullScreen);
		~window();

		// Called by the application class to update the game logic
		void update(DWORD dwCurrentTime);

		// Called by the application class when the window need to be redrawn.
		void draw();

	private:
		void registerWindowClass();							// Register the window class with callback
		bool createContext();								// Create the rendering context used by OpenGL
		void initGL();										// Initialize openGL
		void onSize(GLsizei width, GLsizei height);			// Called when a WM_SIZE message is received

		// Static function which will be the window procedure callback
		static LRESULT CALLBACK onEvent(HWND Handle, UINT Message, WPARAM wParam, LPARAM lParam);

		// Processes the messages that were received in OnEvent.
		void processEvent(UINT Message, WPARAM wParam, LPARAM lParam);

		HWND	m_hWindow;									// The window handle
		HDC     m_hDeviceContext;							// The window device context
		HGLRC   m_hGLContext;								// The openGL context.
		bool	m_bFullScreen;								// Specifies if the window is fullscreen.
	};
}


#endif  // _MAINWINDOW_H_