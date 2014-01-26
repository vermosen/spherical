#include "DMApplication.hpp" 
#include "DMException.hpp"


int WINAPI WinMain(HINSTANCE Instance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT) {

	try	{

		// Create the application class, 
		// parse the command line and
		// start the app.
		DMApplication theApp(Instance);
		theApp.ParseCmdLine(lpCmdLine);
		theApp.Run();

	}

	catch (DMException& e) {

		// crappy, a refaire
		WCHAR str3[sizeof(e.what())/sizeof("a")];

		MultiByteToWideChar(0, 0, e.what(), sizeof(e.what()) / sizeof("a"), 
						    str3, sizeof(e.what()) / sizeof("a") + 1);

		MessageBox(NULL, str3, TEXT("Error"), MB_OK | MB_ICONEXCLAMATION);

	}

	return 0;

}
