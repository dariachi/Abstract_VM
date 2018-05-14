#ifndef LEXEREXPEXTION_HPP
#define LEXEREXPEXTION_HPP
#include <exception>
#include <iostream>
#include <vector>

class LexerExpextion : public std::exception {

	std::string _str;
	std::vector<std::string> _error;
	std::string lex_error = "Lexical error:";
public:
	LexerExpextion &operator=(LexerExpextion &src);
	LexerExpextion(const LexerExpextion &src);
	LexerExpextion(std::string const &str);
	LexerExpextion(std::vector<std::string> error);
	virtual const char* what() const throw();
	LexerExpextion(void) = default;
	~LexerExpextion() throw() = default;
};


#endif