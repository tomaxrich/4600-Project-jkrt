//#include "pch.h"

#include "NameToken.h"
#include "Symbol.h"

//Implementation of NameToken.h

//Constructor, parent constructor is called.
NameToken::NameToken(Symbol sn, int pos, std::string lxm) : Token(sn)
{
	position = pos;
	lexeme = lxm;
}

//Destructor
NameToken::~NameToken()
{

}

//virtual implementation of the insert function
void NameToken::insert(std::ostream &os) const
{
	Token::insert(os);
	os << " Position is: " << position << " and lexeme is: " << lexeme;
}

//Getter for position variable
int NameToken::getPosition() const
{
	return position;
}


//setter for position variable.
void NameToken::setPosition(int pos)
{
	position = pos;
}

//getter for lexeme variable
std::string NameToken::getLexeme()
{
	return lexeme;
}

//setter for lexeme variable
void NameToken::setLexeme(std::string lxm)
{
	lexeme = lxm;
}

