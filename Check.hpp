#ifndef CHECK_HPP
#define CHECK_HPP

#include <sstream>
#include <string.h>
#include "main.hpp"

class Check
{
private:
	std::string _s;
	enum {COUNT = 11};
	std::vector<std::string> string;
	std::vector<std::vector<std::string>> mass;
	std::vector<std::string> error;
public:
	Check(int argc, char **argv);
	Check(Check &src);
	Check &operator=(Check &src);
	void write_flow();
	int read_file(char **argv);
	void ltrim(std::string &s);
	void rtrim(std::string &s);
	void trim(std::string &s);
	void lexer();
	std::vector<std::vector<std::string>> parser();
	int check_second_parametr(const std::string &s, int i);
	void check_third_parametr(const std::string &s, const std::string &s1, int i);
	void read(std::istream &i);
	std::string cut_the_word(std::string &s);
	int lex_e(void);
};

#endif