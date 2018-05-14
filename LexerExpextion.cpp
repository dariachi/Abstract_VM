#include "LexerExpextion.hpp"

const char* LexerExpextion::what() const noexcept {
	std::string str = lex_error;
	for(auto er = _error.begin(); er != _error.end(); er++)
		str += "\n" + *er + "\0";
	str += '\n';
	std::cout << str << std::endl;
	return(str.c_str());
}


LexerExpextion::LexerExpextion(std::string const &str) {
	_str = str;
}

LexerExpextion::LexerExpextion(std::vector<std::string> error) {
	_error = error; 
}


LexerExpextion &LexerExpextion::operator=(LexerExpextion &src) {
	this->_str = src._str;
	this->_error = src._error;
	this->lex_error = src.lex_error;
	return *this;
}

LexerExpextion::LexerExpextion(const LexerExpextion &src) : _str(src._str), _error(src._error), lex_error(src.lex_error) {
}

	