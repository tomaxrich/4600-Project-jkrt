#ifndef TOKEN_H
#define TOKEN_H
#include <iostream>
#include "Symbol.h"
#include <string>
//Definition of base class Token, doesn't do anything and can't be instantiated on its own due to pure virtual function, however still needed to implement that as a function so that each child could call it with minimum code repition.
class Token
{
public:
	//Destructor
	virtual ~Token();

	//Constructor
	Token(Symbol sn);

	//name Getter
	Symbol getSymbolName() const;
	
	//name Setter
	void setSymbolName(Symbol snts);

	//Insert function for writing Token to provided ostream
	virtual void insert(std::ostream &os) const =0;

	//Overload of the << operator
	friend std::ostream & operator << (std::ostream&, Token&);
private:
	//Enumerator Symbol type, terminal symbol name
	Symbol sname;
};


#endif //TOKEN_H

