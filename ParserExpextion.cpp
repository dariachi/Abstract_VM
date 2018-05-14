#include "ParserExpextion.hpp"
#include <iostream>

const char* ParserExpextion::what() const noexcept {
	std::string ret;
	std::string str = parser_error;
	for(auto er = error.begin(); er != error.end(); er++)
		str += "\n" + *er + "\0";
	std::cout << str + '\n' << std::endl;
	return ret.c_str();
}

ParserExpextion::ParserExpextion(std::vector<std::string> v) {
	error = v;
}

ParserExpextion::ParserExpextion(const ParserExpextion &src) : error(src.error), parser_error(src.parser_error) {
}

ParserExpextion &ParserExpextion::operator=(ParserExpextion &src) {
	this->error = src.error;
	this->parser_error = src.parser_error;
	return *this;
}