#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <windows.h>

namespace spherical
{
	class application 
	{
	public:
		application(HINSTANCE hInstance);
		~application();

		void parseStartArgs(LPSTR lpCmdLine);
		void run();

	private:
		static const int	FRAME_TIME = 75;
		HINSTANCE			m_hInstance;
		bool				m_fullScreen;

	};
}

#endif  // APPLICATION_HPP