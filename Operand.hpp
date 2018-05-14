#ifndef OPERAND_HPP
#define OPERAND_HPP

#include "main.hpp"
#include "IOperand.hpp"
#include "FactoryMethod.hpp"
#include <cstdlib>

template <class T> class Operand : public IOperand 
{
private:

	T _value;
	std::string _value_string;
	int _precision;
	eOperandType _type;
	Operand &operator=(const Operand &src) = default;
	Operand(const Operand &src);
public:
	Operand(void);
	int getPrecision( void ) const override;
	Operand(std::string const &value, eOperandType const &type);
	IOperand const * operator+(IOperand const &rhs) const override;
	IOperand const * operator-(IOperand const & rhs) const override;
	IOperand const * operator*( IOperand const & rhs ) const override;
	IOperand const * operator/( IOperand const & rhs ) const override;
	IOperand const * operator%( IOperand const & rhs ) const override;
	std::string const & toString( void ) const override;
	eOperandType getType(void) const override;
};

template<class T>
eOperandType Operand<T>::getType(void) const {
	return this->_type;
}
template<class T>
int  Operand<T>::getPrecision( void ) const {
	return this->_precision;
}

template<class T>
Operand<T>::Operand(const Operand &src) {
	this = src;
}

template<class T>
IOperand const * Operand<T>::operator%( IOperand const & rhs ) const {
	eOperandType type = (this->getType() > rhs.getType()) ? this->getType() : rhs.getType();
	int temp = strtold(toString().c_str(), nullptr) / strtold(rhs.toString().c_str(), nullptr);
	double value = strtold(toString().c_str(), nullptr) - (strtold(rhs.toString().c_str(), nullptr) * temp);
	if(value < (TYPES.at(type) + 1) * -1 || value > TYPES.at(type))
		throw CommandException("Error 'mod'. The value is out of range of possible values type. ");
	IOperand const *ret = FactoryMethod::Instance().createOperand(type, std::to_string(value));
	return ret;
}

template<class T>
IOperand const * Operand<T>::operator/( IOperand const & rhs ) const {
	eOperandType type = (this->getType() > rhs.getType()) ? this->getType() : rhs.getType();
	double value = strtold(toString().c_str(), nullptr) / strtold(rhs.toString().c_str(), nullptr);
	if(value < (TYPES.at(type) + 1) * -1 || value > TYPES.at(type))
		throw CommandException("Error 'div'. The value is out of range of possible values type. ");
	IOperand const *ret = FactoryMethod::Instance().createOperand(type, std::to_string(value));
	return ret;
}

template <class T>
IOperand const * Operand<T>::operator*( IOperand const & rhs ) const {
	eOperandType type = (this->getType() > rhs.getType()) ? this->getType() : rhs.getType();
	double value = strtold(toString().c_str(), nullptr) * strtold(rhs.toString().c_str(), nullptr);
	if(value < (TYPES.at(type) + 1) * -1 || value > TYPES.at(type))
		throw CommandException("Error 'mul'. The value is out of range of possible values type. ");
	IOperand const *ret = FactoryMethod::Instance().createOperand(type, std::to_string(value));
	return ret;
}

template <class T>
IOperand const *Operand<T>::operator+(IOperand const &rhs) const{


	eOperandType type = (this->getType() > rhs.getType()) ? this->getType() : rhs.getType();
	double value = strtold(toString().c_str(), nullptr) + strtold(rhs.toString().c_str(), nullptr);
	if(value < (TYPES.at(type) + 1) * -1 || value > TYPES.at(type))
		throw CommandException("Error 'add'. The value is out of range of possible values type. ");
	IOperand const *ret = FactoryMethod::Instance().createOperand(type, std::to_string(value));
	return ret;
}

template <class T>
IOperand const *Operand<T>::operator-(IOperand const &rhs) const{
	eOperandType type = (this->getType() > rhs.getType()) ? this->getType() : rhs.getType();
	double value = strtold(toString().c_str(), nullptr) - strtold(rhs.toString().c_str(), nullptr);
	if(value < (TYPES.at(type) + 1) * -1 || value > TYPES.at(type))
		throw CommandException("Error 'sub'. The value is out of range of possible values type. ");
	IOperand const *ret = FactoryMethod::Instance().createOperand(type, std::to_string(value));
	return ret;
}



template <class T>
Operand<T>::Operand(std::string const &value, eOperandType const &type)
{
	std::ostringstream ost;
	this->_value_string = value;
	this->_value = strtold(value.c_str(), nullptr);
	this->_type = type;
	this->_precision = type;
}



template<class T>
std::string const &Operand<T>::toString(void) const
{
	std::ostringstream ost; 
	ost << _value;
	return this->_value_string;
}


#endif