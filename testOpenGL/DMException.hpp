#ifndef _EXCEPTION_H_
#define _EXCEPTION_H_

#include <exception>
#include <string>

class DMException : public std::exception {

public:

	const char* what() const  { return m_strMessage.c_str(); }

	DMException(const std::string& strMessage = "") : m_strMessage(strMessage)  { }

	virtual ~DMException()  { }

	std::string m_strMessage;

};

#endif  // _EXCEPTION_H_
