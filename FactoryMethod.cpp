#include "FactoryMethod.hpp"
#include "Operand.hpp"

FactoryMethod::FactoryMethod() {}
FactoryMethod::~FactoryMethod() {}

FactoryMethod& FactoryMethod::Instance(void)
{
	static FactoryMethod variable_fm;
	return variable_fm;
}

IOperand const * FactoryMethod::createInt8( std::string const & value ) const {
	return new Operand<char>(value, INT8);
}
IOperand const * FactoryMethod::createInt16( std::string const & value ) const {
	return new Operand<short>(value, INT16);
}
IOperand const * FactoryMethod::createInt32( std::string const & value ) const {
	return new Operand<int>(value, INT32);
}
IOperand const * FactoryMethod::createFloat( std::string const & value ) const {
	return new Operand<float>(value, FLOAT);
}
IOperand const * FactoryMethod::createDouble( std::string const & value ) const {
	return new Operand<double>(value, DOUBLE);
}

IOperand const *FactoryMethod::createOperand(eOperandType type, std::string const & value ) const
{
	IOperand const *(FactoryMethod::*mass[5])(std::string const &) const = 
	{
		&FactoryMethod::createInt8,
		&FactoryMethod::createInt16,
		&FactoryMethod::createInt32,
		&FactoryMethod::createFloat,
		&FactoryMethod::createDouble
	};
	IOperand const *ret = (this->*mass[type])(value);
	return ret;
}

