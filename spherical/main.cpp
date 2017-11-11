#include <application/application.hpp> 
#include <application/exception.hpp>

int WINAPI WinMain(HINSTANCE Instance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT) 
{
	try	
	{
		spherical::application app(Instance);
		app.parseStartArgs(lpCmdLine);
		app.run();
	}

	catch (spherical::exception& ex) 
	{
		WCHAR str[sizeof(ex.what())/sizeof("a")];
		MessageBox(NULL, str, TEXT("error"), 
			MB_OK | MB_ICONEXCLAMATION);
	}

	return 0;
}
