//#include "pch.h"

#include "NumberToken.h"
#include "Symbol.h"

//Implementation of NumberToken.h

//Constructor, parent constructor is called.
NumberToken::NumberToken(Symbol sn, int vl) : Token(sn)
{
	value = vl;
}

//Destructor
NumberToken::~NumberToken()
{

}

//virtual implementation of insert
void NumberToken::insert(std::ostream &os) const
{
	Token::insert(os);
	os << " Numerical value is: " << getValue();
}

//getter for value variable
int NumberToken::getValue() const
{
	return value;
}

//setter for value variable
void NumberToken::setValue(int vts)
{
	value = vts;
}