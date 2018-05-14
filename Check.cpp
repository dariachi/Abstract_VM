#include "Check.hpp"

const std::string type[5] = {"int8", "int16", "int32", "float", "double"};
const std::string commands[16] = {"push", "pop", "dump", "assert", "add",
"sub", "mul", "div", "mod", "print", "exit", "clear", "pow", "more", "less", "size"};

Check::Check(Check &src) {
	*this = src;
}

Check &Check::operator=(Check &src) {
	this->_s = src._s;
	this->string = src.string;
	this->mass = src.mass;
	this->error = src.error;
	return (*this);
}

void Check::read(std::istream &i)
{
	int j = 0;
    std::string str;
    while (getline(i, str))
    {
    	if(!str.empty() && j == 0)
		{
			trim(str);
			string.emplace_back(str);
		}
		if(strstr(str.c_str(), "exit") != nullptr)
			j = 1;
	}
	if(string.empty())
		throw ExceptionRead("Empty file or folder");
}

int 	Check::read_file(char **argv)
{
    std::ifstream f(argv[1]);

    if (!f.is_open())
    	throw ExceptionRead("Can't open the file");
    read(f);
	return 1;
}

Check::Check(int argc, char **argv)
{
	if(argc == 2)
	{
		if(!read_file(argv))
			throw ExceptionRead("No valied file");
	}
	else
		write_flow();
}

void Check::ltrim(std::string &s) {
    std::regex reg("^(\\s+)");
    s = regex_replace(s.c_str(), reg, "");
}

void Check::rtrim(std::string &s) {
    std::regex reg("(\\s+)$");
    s = regex_replace(s.c_str(), reg, "");
}

void Check::trim(std::string &s) {
	if(s.find_first_of(";") != std::string::npos)
		s.erase(s.find_first_of(";"));
	std::regex reg("(\\s+)");
    ltrim(s);
    rtrim(s);
    s = regex_replace(s.c_str(), reg, " ");
}
void	Check::write_flow()
{
	std::string str;
	int i = 0;
	for(; getline(std::cin, str) && str != ";;"; str.clear())
	{
		if(!str.empty() && i == 0)
		{
			trim(str);
			string.emplace_back(str);
		}
		if(strstr(str.c_str(), "exit") != nullptr)
			i = 1;
	}
}

std::string Check::cut_the_word(std::string &help)
{
	std::string ret;
	for (int i = 0; (help[i] != ' ' && help[i] != '\0'); i++)
				ret += help[i];
	return ret;
}

void	Check::lexer()
{
	std::vector<std::string> v;
	std::regex first_argument("(^[a-z]{3,6})$");
	int i = 0;

	for (auto ps = string.begin(); ps != string.end(); ps++)
	{
		std::ostringstream ost;
    	ost << i;
		std::string help = *ps;
		std::string new_str;
		if(help.empty())
			continue ;
		new_str = help.substr(0, help.find_first_of(" "));
		v.push_back(new_str);
		if (!std::regex_match(new_str.c_str(), first_argument))
			error.push_back("Line: " + ost.str() + ". Unknown instruction '" + cut_the_word(help) + "'");
		if (help.find_first_of(" ") != std::string::npos)
		{
			help.erase(0, help.find_first_of(" ") + 1);
			v.push_back(help.substr(0, (help.find('('))));
			if(help.find_first_of("(") != std::string::npos && help.find_first_of(")") != std::string::npos)
				v.push_back(help.substr((help.find('(') + 1), (help.find(')') - (help.find('(') + 1))));
			std::regex second_argument("([\\w])+\\(([\\d\\-+.]+)\\)(.*)");
			std::regex number("^[-+]?[0-9]*[.,]?[0-9]+(?:[-+]?[0-9]+)?$");
			if ((!std::regex_match(help.c_str(), second_argument)) || (!std::regex_match((v.end() - 1)->c_str(), number)))
				error.push_back("Line: " + ost.str() + ". Invalid syntax: '" + cut_the_word(help) + "'");
			help.erase(0,  help.find(")") + 1);
			if(!help.empty())
			{
				std::regex comment("^(\\s)*?#(.)*");
				if(!regex_match(help.c_str(), comment))
					error.push_back("Line: " + ost.str() + ". Two arguments");
			}
		}
		mass.push_back(v);
		v.clear();
		i++;
	}
	if(!error.empty())
		throw LexerExpextion(error);
}

int	Check::check_second_parametr(const std::string &s, int count)
{
	int j = 0;
	std::ostringstream ost; 
	ost << count;
	for (int i = 0; i < 5; i++)
	{
		if((s) == type[i])
			j++;
	}
	if(j != 1)
	{
		error.push_back("Line: " + ost.str() +". Type error '" + s + "'");
		return -1;
	}
	return j;
}

void	Check::check_third_parametr(const std::string &s, const std::string &s1, int count)
{
	int i = 0;
	std::ostringstream ost; 
	ost << count;
	for(i = 0; i < 5 && type[i] != s1; i++) {}
	if(s.empty() || strspn(s.c_str(), "0123456789-+") == 0)
	{
		error.push_back("There is no specific number");
		return ;
	}
	double number = std::stold(s);

	std::cout << number << std::endl;
	if(number < ((TYPES.at((eOperandType)i) + 1) * -1) || number > TYPES.at((eOperandType)i))
		error.push_back("Line: " + ost.str() + ". Error: " + s +" is out of range of possible values " + s1);
}

int Check::lex_e(void) {
	if(!error.empty())
		return 1;
	else
		return 0;
}

std::vector<std::vector<std::string>>	Check::parser()
{
	error.clear();
	int count = 0;
	for (auto ps = mass.begin(); ps != mass.end(); ps++)
	{
		std::ostringstream ost; 
		ost << count;
		auto px = (*ps).begin();
		for(int i = 0; i < 16; i++)
		{
			if((*px) == commands[i])
			{
				if((i == 0 || i == 3) && ps->size() != 3)
				{
					error.push_back("Line: " + ost.str() + ". The command '" + commands[i] + "' have 3 arguments");
					break ;
				}
				px++;
				if(i == 0 || i == 3)
				{
					std::string help = *px;
					if(check_second_parametr(*px, i) == 1)
					{
						px++;
						check_third_parametr(*px, help, i);
					}
				}
				else
				{
					if(px != (*ps).end() && *px->begin() != ';')
						error.push_back("Line: " + ost.str() + ". The command '" + commands[i] + "' haven't arguments");
				}
				break ;
			}
			if (i == 15)
				error.push_back("Line: " + ost.str() + ". Unknown value type: '" + *px + "'");
		}
		count++;
	}
	if(!error.empty())
		throw ParserExpextion(error);
	return mass;
}