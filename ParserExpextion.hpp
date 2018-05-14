#ifndef PARSEREXPEXTION_HPP
#define PARSEREXPEXTION_HPP

#include <exception>
#include <vector>
#include <string>

class ParserExpextion : public std::exception {
private:
	std::vector<std::string> error;
	std::string parser_error = "Parser error: ";
public:
	ParserExpextion(const ParserExpextion &src);
	ParserExpextion &operator=(ParserExpextion &src);
	ParserExpextion() = default;
	~ParserExpextion() throw() = default;
	virtual const char* what() const throw();
	ParserExpextion(std::vector<std::string> v);
};

#endif