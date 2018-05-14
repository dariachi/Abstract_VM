#ifndef TYPEANALYSIS_HPP
#define TYPEANALYSIS_HPP

#include <map>
#include <stdio.h>
#include "Operand.hpp"
#include <vector>
#include "FactoryMethod.hpp"
#include "CommandException.hpp"
#include <sstream>

class TypeAnalysis
{
private:
	const std::vector<std::vector<std::string>> *command;
	std::string com[15];
	FactoryMethod &fm = FactoryMethod::Instance();
	std::vector<IOperand const*>			stack;
	int _exit = 0;
public:
	TypeAnalysis();
	~TypeAnalysis();

	TypeAnalysis(const TypeAnalysis &src);
	TypeAnalysis &operator=(TypeAnalysis &src);

	TypeAnalysis(std::vector<std::vector<std::string>> const &command);
	eOperandType	converts(std::string const &value);
	void			SearchCommandType(void);
	void			push(std::string const &string1, std::string const &string2);
	void 			assept(std::string const &string1, std::string const &string2);
	void			add(void);
	void 			dump(void);
	void 			sub(void);
	void 			mul(void);
	void 			div(void);
	void			mod(void);
	void 			print(void);
	void 			exit(void);
	void 			pop(void);
	void 			clear(void);
	void 			pow(void);
	void 			more(void);
	void 			less(void);
	void 			size(void);
	int 			converts_back(eOperandType eOp, const std::string &value);
	void			elevationMap();
	int 			NumberCommand(std::string const &pv);
	// void 			clear_memory(void);
};

#endif