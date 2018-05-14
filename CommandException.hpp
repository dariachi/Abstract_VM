#ifndef COMMANDEXCEPTION_HPP
#define COMMANDEXCEPTION_HPP

#include <exception>
#include <iostream>
#include <vector>

class CommandException : public std::exception
{
private:
	std::string error;
public:
	CommandException(const CommandException &src);
	CommandException &operator=(CommandException &src);
	CommandException() = default;
	CommandException(const std::string &str);
	~CommandException() = default;
	virtual const char* what() const throw();
};

#endif