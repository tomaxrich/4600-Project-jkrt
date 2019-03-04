#ifndef NAMETOKEN_H
#define NAMETOKEN_H

#include "Token.h"
#include "Symbol.h"
#include <string>
#include <iostream>
//Class to define a token for identifiers and keywords, inherits from Token, has a name, array position, and a lexeme
class NameToken : public Token
{
public:

	//Constructor
	NameToken(Symbol sn, int pos, std::string lxm);

	//Destructor
	virtual ~NameToken();
	
	//virtual implementation of insert
	virtual void insert(std::ostream &os) const;
	
	//getter for position variable
	int getPosition() const;

	//setter for position variable
	void setPosition(int pts);

	//getter fore lexeme variable
	std::string getLexeme();

	//setter for lexeme variable
	void setLexeme(std::string lts);

private:
	//Integer representing hashtable position of lexeme (i.e. the identifier)
	int position;

	//string representing the lexeme
	std::string lexeme;
};
#endif // !NAMETOKEN_H
