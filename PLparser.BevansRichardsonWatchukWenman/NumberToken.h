#ifndef NUMBERTOKEN_H
#define NUMBERTOKEN_H

#include "Token.h"
#include "Symbol.h"

//Class to define a token for numerals, has a name and a value
class NumberToken : public Token
{
public:
	//Constructor
	NumberToken(Symbol sn, int vl);

	//Destructor
	virtual ~NumberToken();

	//Virtual implementation of insert function
	virtual void insert(std::ostream &os) const;

	//getter for value variable
	int getValue() const;

	//setter for value variable
	void setValue(int vts);

private:
	//int representing value of number.
	int value;

};
#endif // !NUMBERTOKEN_H
