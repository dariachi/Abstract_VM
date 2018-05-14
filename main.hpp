#ifndef MAIN_HPP
#define MAIN_HPP

#include <iostream>
#include <cstring>
#include <vector>
#include <stdio.h>
#include <regex>
#include <map>
#include "ExceptionRead.hpp"
#include "Check.hpp"
#include "main.hpp"
#include <fstream>
#include "LexerExpextion.hpp"
#include "ParserExpextion.hpp"
#include "CommandException.hpp"

enum eOperandType {INT8, INT16, INT32, FLOAT, DOUBLE};

const std::map<eOperandType, double> TYPES = {
	{INT8, 127},
	{INT16, 32767},
	{INT32, 2147483647},
	{FLOAT, 3.40282e+38},
	{DOUBLE, 1.79769e+308}
};


#endif