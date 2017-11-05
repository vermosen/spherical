#include "application.hpp"
#include "mainWindow.hpp"
#include <string>

// Disable the warnings for deprecated functions (strtok and stricmp)
#pragma warning(disable:4996)

namespace spherical
{
	application::application(HINSTANCE hInstance) 
		: m_hInstance(hInstance)
		, m_fullScreen(false) {}

	application::~application() {}

	void application::parseStartArgs(LPSTR lpCmdLine) 
	{
		LPSTR lpArgument = strtok(lpCmdLine, " ");

		while (lpArgument)
		{
			if (stricmp(lpArgument, "-f") == 0)
				m_fullScreen = true;

			lpArgument = strtok(NULL, " ");
		}
	}

	void application::run()
	{
		// Create the main window first
		mainWindow mainWindow(800, 600, m_fullScreen);

		MSG message;
		message.message = ~WM_QUIT;
		DWORD dwNextDeadLine = GetTickCount() + FRAME_TIME;
		DWORD dwSleep = FRAME_TIME;
		bool bUpdate = false;

		// Loop until a WM_QUIT message is received
		while (message.message != WM_QUIT) {

			// Wait until a message comes in or until the timeout expires. The
			// timeout is recalculated so that this function will return at
			// least every FRAME_TIME msec.
			DWORD dwResult = MsgWaitForMultipleObjectsEx(0, NULL, dwSleep, QS_ALLEVENTS, 0);

			if (dwResult != WAIT_TIMEOUT) {

				// If the function returned with no timeout, it means that at 
				// least one message has been received, so process all of them.
				while (PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) {

					// If a message was waiting in the message queue, process it
					TranslateMessage(&message);
					DispatchMessage(&message);

				}

				// If the current time is close (or past) to the 
				// deadline, the application should be processed.
				if (GetTickCount() >= dwNextDeadLine)
					bUpdate = true;
				else
					bUpdate = false;
			}

			else
				// On a timeout, the application should be processed.
				bUpdate = true;

			// Check if the application should be processed
			if (bUpdate) 
			{
				DWORD dwCurrentTime = GetTickCount();

				// Update the main window
				mainWindow.update(dwCurrentTime);

				// Draw the main window
				mainWindow.draw();
				dwNextDeadLine = dwNextDeadLine + FRAME_TIME;
			}

			// Process the sleep time, which is the difference
			// between the current time and the next deadline.
			dwSleep = dwNextDeadLine - GetCurrentTime();

			// If the sleep time is larger than the frame time,
			// it probably means that the processing was stopped 
			// (e.g. the window was being moved,...), so recalculate
			// the next deadline.
			if (dwSleep > FRAME_TIME) {

				dwSleep = FRAME_TIME;
				dwNextDeadLine = GetCurrentTime() + FRAME_TIME;
			}
		}
	}
}
