#ifndef SYMTOKEN_H
#define SYMTOKEN_H

#include "Token.h"
#include "Symbol.h"
#include <string>
#include <iostream>
//class to define a symbol token, has a name
class SymToken : public Token
{
public:
	//Constructor
	SymToken(Symbol sn);

	//Destructor
	virtual ~SymToken();

	//Virtual of insert
	virtual void insert(std::ostream &os) const;

};
#endif // !SYMTOKEN_H
