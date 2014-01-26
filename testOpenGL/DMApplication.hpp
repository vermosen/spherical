#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include <windows.h>

// The application class, which simply wraps the message queue and process
// the command line.
class DMApplication {

public:

	DMApplication(HINSTANCE hInstance);
	~DMApplication();

	// Parses the command line to see if the application

	// should be in fullscreen mode.
	void ParseCmdLine(LPSTR lpCmdLine);

	// Creates the main window and start the message loop.
	void Run();



private:

	static const int FRAME_TIME = 75;
	HINSTANCE m_hInstance;

	// Specifies if the application has to be started in fullscreen
	// mode. This option is supplied through the command line
	// ("-fullscreen" option).
	bool m_bFullScreen;

};

#endif  // _APPLICATION_H_