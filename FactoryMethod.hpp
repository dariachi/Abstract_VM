#ifndef FACTORY_METHOD_HPP
#define FACTORY_METHOD_HPP

#include "IOperand.hpp"
#include "main.hpp"

class FactoryMethod
{
public:
	FactoryMethod();
	~FactoryMethod();
	FactoryMethod(const FactoryMethod &src) = delete;
	FactoryMethod &operator=(FactoryMethod &src) = default;
	static FactoryMethod& Instance();
private:
	IOperand const * createInt8( std::string const & value ) const;
	IOperand const * createInt16( std::string const & value ) const;
	IOperand const * createInt32( std::string const & value ) const;
	IOperand const * createFloat( std::string const & value ) const;
	IOperand const * createDouble( std::string const & value ) const;	
public:
	IOperand const *createOperand(eOperandType type, std::string const & value ) const;
};

#endif