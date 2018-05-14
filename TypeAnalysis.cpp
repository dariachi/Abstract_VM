#include "TypeAnalysis.hpp"
#include <iostream>
#include <iomanip>

TypeAnalysis::TypeAnalysis(const TypeAnalysis &src) : command(src.command), fm(src.fm), stack(src.stack){
}

TypeAnalysis &TypeAnalysis::operator=(TypeAnalysis &src)
{
	this->command = src.command;
	this->fm = src.fm;
	this->stack = src.stack;
	this->_exit = src._exit;
	return *this;
}

TypeAnalysis::TypeAnalysis(void) {
	
}
TypeAnalysis::~TypeAnalysis(void) {
}


TypeAnalysis::TypeAnalysis(std::vector<std::vector<std::string>> const &command)
{
	this->command = &command;
	SearchCommandType();

}

eOperandType	TypeAnalysis::converts(std::string const &value)
{
	if(value == "int8")
		return INT8;
	else if(value == "int16")
		return INT16;
	else if(value == "int32")
		return INT32;
	else if(value == "float")
		return FLOAT;
	else
		return DOUBLE;
}

int 	TypeAnalysis::converts_back(eOperandType eOp, const std::string &value)
{
	if(eOp == INT8 && value == "int8")
		return 1;
	else if(eOp == INT16 && value == "int16")
		return 1;
	else if(eOp == INT32 && value == "int32")
		return 1;
	else if(eOp == FLOAT && value == "float")
		return 1;
	else if(eOp == DOUBLE && value == "double")
		return 1;
	else
		return -1;
}

void 	TypeAnalysis::sub(void) {

	if((stack.rbegin() == stack.rend() - 1) || stack.empty())
	{
		clear();
		throw CommandException("Сan not execute the command 'sub'. Stack must have at least two values.");
	}
	auto v1 = *(stack.rbegin());
	auto v2 = *((stack.rbegin() + 1));
	stack.pop_back();
	stack.pop_back();
	stack.push_back(*v2 - *v1);
	delete v2;
	delete v1;
}

void 	TypeAnalysis::mul(void) {
	if((stack.rbegin() == stack.rend() - 1) || stack.empty())
	{
		clear();
		throw CommandException("Сan not execute the command 'mul'. Stack must have at least two values.");
	}
	auto v1 = *(stack.rbegin());
	auto v2 = *((stack.rbegin() + 1));
	stack.pop_back();
	stack.pop_back();
	stack.push_back(*v2 * *v1);
	delete v2;
	delete v1;
}
void 	TypeAnalysis::div(void) {
	if((stack.rbegin() == stack.rend() - 1) || stack.empty())
	{
		clear();
		throw CommandException("Сan not execute the command 'div'. Stack must have at least two values.");
	}
	auto v1 = *(stack.rbegin());
	if(strtold(v1->toString().c_str(), nullptr) == 0)
	{
		clear();
		throw CommandException("Division by zero is impossible.");
	}
	auto v2 = *((stack.rbegin() + 1));
	stack.pop_back();
	stack.pop_back();
	stack.push_back(*v2 / *v1);
	delete v2;
	delete v1;
}
void 	TypeAnalysis::mod(void) {
	if((stack.rbegin() == stack.rend() - 1) || stack.empty())
	{
		clear();
		throw CommandException("Сan not execute the command 'mod'. Stack must have at least two values.");
	}
	auto v1 = *(stack.rbegin());
	if(strtold(v1->toString().c_str(), nullptr) == 0)
	{
		clear();
		throw CommandException("Division by zero is impossible.");
	}
	auto v2 = *((stack.rbegin() + 1));
	stack.pop_back();
	stack.pop_back();
	stack.push_back(*v2 % *v1);
	delete v2;
	delete v1;

}
void 	TypeAnalysis::print(void) {

	if(stack.empty())
	{
		clear();
		throw CommandException("Сan not execute the command 'print'. Stack is empty.");
	}
	auto v1 = *(stack.rbegin());
	if(v1->getPrecision() == 0)
	{
		char temp = strtold(v1->toString().c_str(), nullptr);
		if(temp < 32)
		{
			std::ostringstream ost; 
			ost << (int)temp;
			clear();
			throw CommandException("Non-displayable character: " + ost.str());
		}
		else
			std::cout << (char)strtold(v1->toString().c_str(), nullptr) << std::endl;
	}
	else
	{
		clear();
		throw CommandException("Error: Cannot print. Top value not 8-bit integer");
	}
}
void 	TypeAnalysis::exit(void) {
	this->_exit = 1;
}


void	TypeAnalysis::pop(void) {
	if(stack.empty())
	{
		clear();
		throw CommandException("Error. Unable to execute the command 'pop'. Stack empty");
	}
	else
	{
		auto v2 = *((stack.rbegin()));
		delete v2;
		stack.pop_back();
	}
}

void	TypeAnalysis::elevationMap(void)
{
	com[0] = "push";
	com[1] = "assert";
	com[2] = "add";
	com[3] = "dump";
	com[4] = "sub";
	com[5] = "mul";
	com[6] = "div";
	com[7] = "mod";
	com[8] = "pop";
	com[9] = "print";
	com[10] = "exit";
	com[11] = "clear";
	com[12] = "pow";
	com[13] = "more";
	com[14] = "less";
	com[15] = "size";
}

int 	TypeAnalysis::NumberCommand(std::string const &pv)
{
	int i = 0;

	while(pv != com[i] && i < 15)
		i++;
	i = (i == 0) ? 0 : i--;
	return i;
}

void	TypeAnalysis::add(void) {
	if((stack.rbegin() == stack.rend() - 1) || stack.empty())
	{
		clear();
		throw CommandException("Сan not execute the command 'add'. Stack must have at least two values.");
	}
	auto v1 = *(stack.rbegin());
	auto v2 = *((stack.rbegin() + 1));
	stack.pop_back();
	stack.pop_back();
	stack.push_back(*v2 + *v1);
	delete v2;
	delete v1;
}


void	TypeAnalysis::push(std::string const &string1, std::string const &string2) 
{
	eOperandType type = converts(string1);
	if(type < 3 && string2.find('.') != std::string::npos)
	{
		clear();
		throw CommandException("Error. The precision in an unsigned variable is specified");
	}
	stack.push_back(FactoryMethod::Instance().createOperand(type, string2));
}

void TypeAnalysis::assept(std::string const &string1, std::string const &string2)
{
	if(stack.empty())
	{
		clear();
		throw CommandException("Сan not execute the command 'assert'. Stack is empty.");
	}
	auto v1 = *(stack.rbegin());
	if(converts_back(v1->getType(), string1) == -1)
	{
		// stack.clear();
		clear();
		throw CommandException("Error. Assertion is not true");
	}
	else if(strtold(string2.c_str(), nullptr) != strtold(v1->toString().c_str(), nullptr))
	{
		stack.clear();
		// clear();
		throw CommandException("Error. Assertion is not true");
	}
}

void  TypeAnalysis::dump(void)
{
	for (auto i = stack.rbegin(); i != stack.rend(); i++)
	{
		if((*i)->getPrecision() < 3)
			std::cout << (int)strtold((*i)->toString().c_str(), nullptr) << std::endl;
		else if((*i)->getPrecision() == 3)
			std::cout << std::setprecision(7) << (float)strtold((*i)->toString().c_str(), nullptr) << std::endl;
		else
			std::cout << std::setprecision(14) << (double)strtold((*i)->toString().c_str(), nullptr) << std::endl;
	}
}

void TypeAnalysis::clear(void)
{
	for (auto i = stack.rbegin(); i != stack.rend(); i++)
	{
		delete *i;
		stack.pop_back();
	}
}

void TypeAnalysis::pow(void)
{
	if(stack.empty())
	{
		clear();
		throw CommandException("Сan not execute the command 'pow'. Stack must have at least two values.");
	}
	std::ostringstream string; 
	IOperand const *z = *stack.rbegin();
	double v1 = (double)strtold(z->toString().c_str(), nullptr);
	double value = v1 * v1;
	eOperandType type = z->getType();
	if(value < (TYPES.at(type) + 1) * -1 || value > TYPES.at(type))
	{
		clear();
		throw CommandException("Error 'pow'. The value is out of range of possible values type. ");
	}
	string << value;
	stack.pop_back();
	delete z;
	stack.push_back(FactoryMethod::Instance().createOperand(type, string.str()));
}

void TypeAnalysis::more(void) {
	if((stack.rbegin() == stack.rend() - 1) || stack.empty())
		throw CommandException("Сan not execute the command 'more'. Stack must have at least two values.");
	auto v1 = *(stack.rbegin());
	auto v2 = *((stack.rbegin() + 1));
	if(strtold(v1->toString().c_str(), nullptr) < strtold(v2->toString().c_str(), nullptr))
	{
		clear();
		throw CommandException("Error: " + v1->toString() + " <= " + v2->toString());
	}
	else
		std::cout << v1->toString() + " > " + v2->toString() << std::endl;
}

void TypeAnalysis::less(void) {
	if((stack.rbegin() == stack.rend() - 1) || stack.empty())
	{
		clear();
		throw CommandException("Сan not execute the command 'less'. Stack must have at least two values.");
	}
	auto v1 = *(stack.rbegin());
	auto v2 = *((stack.rbegin() + 1));
	if(strtold(v1->toString().c_str(), nullptr) > strtold(v2->toString().c_str(), nullptr))
	{
		clear();
		throw CommandException("Error: " + v1->toString() + " >= " + v2->toString());
	}
	else
		std::cout << v1->toString() + " < " + v2->toString() << std::endl;
}

void TypeAnalysis::size(void)
{
	int i = 0;
	for(auto ps = stack.begin(); ps != stack.end(); ps++)
		i++;
	if(i > 0)
	 	std::cout << "Stack consists of " << i << " elements. " << std::endl; 
	else
		std::cout << "The stack is empty." << std::endl; 
} 

void	TypeAnalysis::SearchCommandType(void)
{
	for(auto ps = this->command->begin(); ps != this->command->end(); ps++)
	{
		auto pv = (*ps).begin();
		elevationMap();

		int j = NumberCommand(*pv);
		if(j < 2)
		{
			void (TypeAnalysis::*m3[2])(std::string const &string1, std::string const &string2) = {
				&TypeAnalysis::push,
				&TypeAnalysis::assept
			};
			pv++;
			std::string g = *pv;
				pv++;
			(this->*m3[j])(g, *pv);
		}
		else
		{
			void (TypeAnalysis::*m1[14])(void) = {
				&TypeAnalysis::add,
				&TypeAnalysis::dump,
				&TypeAnalysis::sub,
				&TypeAnalysis::mul,
				&TypeAnalysis::div,
				&TypeAnalysis::mod,
				&TypeAnalysis::pop,
				&TypeAnalysis::print,
				&TypeAnalysis::exit,
				&TypeAnalysis::clear,
				&TypeAnalysis::pow,
				&TypeAnalysis::more,
				&TypeAnalysis::less,
				&TypeAnalysis::size
			};
			(this->*m1[j - 2])();
		}
	}
	if(this->_exit != 1)
	{
		clear();
		throw CommandException("Error: Missing command 'exit'");
	}
}
