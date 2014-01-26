#ifndef dm_main_window
#define dm_main_window

#include <Windows.h>
#include "GL/gl.h"

// The main window class. It wraps the HANDLE of the window and initializes the 
// openGL rendering context. It is also in charge of processing the different
// event messages.
class DMMainWindow {

public:

	DMMainWindow(int iWidth, int iHeight, bool bFullScreen);
	~DMMainWindow();

	// Called by the application class to update the game logic
	void Update(DWORD dwCurrentTime);
	
	// Called by the application class when the window need to be redrawn.
	void Draw();

private:

	// Register the window class with the correct window procedure (OnEvent)
	void RegisterWindowClass();

	// Create the rendering context used by OpenGL
	void CreateContext();

	// Initialize openGL
	void InitGL();

	// Called when a WM_SIZE message is received
	void OnSize(GLsizei width, GLsizei height);

	// Static function which will be the window procedure callback
	static LRESULT CALLBACK OnEvent(HWND Handle, UINT Message, WPARAM wParam, LPARAM lParam);

	// Processes the messages that were received in OnEvent.
	void ProcessEvent(UINT Message, WPARAM wParam, LPARAM lParam);

	// The window handle
	HWND	m_hWindow;

	// The window device context
	HDC     m_hDeviceContext;

	// The openGL context.
	HGLRC   m_hGLContext;

	// Specifies if the window is fullscreen.

	bool m_bFullScreen;

};

#endif  // _MAINWINDOW_H_