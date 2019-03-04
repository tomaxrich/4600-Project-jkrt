//#include "pch.h"
#include "SymToken.h"
#include "Symbol.h"

//Implementation of SymToken.h

//Constructor (Calls parent constructor)
SymToken::SymToken(Symbol sn) : Token::Token(sn)
{

}

//Destructor
SymToken::~SymToken()
{

}

//Virtual implementation of Token insert
void SymToken::insert(std::ostream &os) const
{
	Token::insert(os);
}

