#ifndef EXCEPTIONREAD_HPP
#define EXCEPTIONREAD_HPP

#include <iostream>
#include <exception>
#include <string>

class ExceptionRead
{
private:
	std::string string;

public:
	ExceptionRead(const ExceptionRead &src);
	ExceptionRead &operator=(ExceptionRead &src);
	ExceptionRead() = default;
	~ExceptionRead() throw() = default;
	virtual const char* what() const throw();
	ExceptionRead(std::string const &s);
};

#endif