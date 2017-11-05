#ifndef _EXCEPTION_H_
#define _EXCEPTION_H_

#include <exception>
#include <string>

namespace spherical
{
	class exception : public std::exception 
	{
	public:
		const char* what() const { return m_message.c_str(); }
		exception(const std::string& message = "") : m_message(message) {}
		virtual ~exception() {}
	
	private:
		std::string m_message;
	};
}


#endif  // _EXCEPTION_H_
