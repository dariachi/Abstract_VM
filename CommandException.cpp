#include "CommandException.hpp"
#include <cstring>

const char* CommandException::what() const noexcept {
	return (error.c_str());
}

CommandException::CommandException(const std::string &string) {
	error += string;
}

CommandException::CommandException(const CommandException &src) : error(src.error) {
}

CommandException &CommandException::operator=(CommandException &src) {
	this->error = src.error;
	return *this;
}