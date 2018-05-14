#include "main.hpp"
#include "TypeAnalysis.hpp"

int 		main(int argc, char **argv)
{
	std::vector<std::vector<std::string>> commands;

	try {
		if(argc > 2)
			throw ExceptionRead("Too many arguments");
		Check obj(argc, argv);
		try {
			obj.lexer();
			commands = obj.parser();
			try {
				if(obj.lex_e() != 1)
					TypeAnalysis mass(commands);
			}
			catch(CommandException &e) {
				std::cout << e.what() << std::endl;
			}
		}
		catch(ParserExpextion &e) {
			e.what();
		}
		catch(LexerExpextion &e) {
			e.what();
		}
	}
	catch(ExceptionRead &e) {
		e.what();
	}
	// while(1);
	return 0;
}
