#include "ExceptionRead.hpp"

const char* ExceptionRead::what() const noexcept {
	std::cout << this->string << std::endl;
	return this->string.c_str();
}

ExceptionRead::ExceptionRead(std::string const &s) {
	string = s;
}

ExceptionRead::ExceptionRead(const ExceptionRead &src) : string(src.string) {
}

ExceptionRead &ExceptionRead::operator=(ExceptionRead &src) {
	this->string = src.string;
	return *this;
}
