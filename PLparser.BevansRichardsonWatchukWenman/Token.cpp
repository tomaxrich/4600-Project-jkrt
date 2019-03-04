//#include "pch.h"
#include "Token.h"


using namespace std;

//Implementation of token, override of pure virtual function

//Destructor
Token::~Token()
{

}

//Constructor
Token::Token(Symbol sn) :sname(sn)
{
}

//Insert function for writing Token to provided ostream
void Token::insert(ostream &os) const
{
	int i = getSymbolName();
	i = i - 256;
	char SymbolTypeString[46][20] = {
	"ID",
	"KW_BEGIN",
	"KW_END",
	"KW_CONST",
	"KW_ARRAY",
	"KW_INTEGER",
	"KW_BOOLEAN",
	"KW_PROC",
	"KW_SKIP",
	"KW_READ",
	"KW_WRITE",
	"KW_CALL",
	"KW_IF",
	"KW_DO",
	"KW_FI",
	"KW_OD",
	"KW_FALSE",
	"KW_TRUE",
	"NUMERAL",
	"SYM_PERIOD",
	"SYM_COMMA",
	"SYM_SEMICOLON",
	"SYM_RIGHTSQUARE",
	"SYM_LEFTSQUARE",
	"SYM_AND",
	"SYM_OR",
	"SYM_NOT",
	"SYM_LESSTHAN",
	"SYM_EQUAL",
	"SYM_GREATERTHAN",
	"SYM_PLUS",
	"SYM_MINUS",
	"SYM_MULTIPLY",
	"SYM_DIVIDE",
	"SYM_MODULO",
	"SYM_RIGHTBRACKET",
	"SYM_LEFTBRACKET",
	"SYM_ASSIGNMENT",
	"SYM_GUARD",
	"SYM_RIGHTARROW",
	"SYM_COMMENT",
	"BAD_NUMERAL",
	"BAD_ID",
	"BAD_SYM",
	"BAD_SCAN",
	"NONAME"
	};

	os << "Token Symbol name: " << SymbolTypeString[i];
}

//name Getter
Symbol Token::getSymbolName() const
{
	return sname;
}

//name Setter
void Token::setSymbolName(Symbol snts)
{
	sname = snts;
}

//Overload of the << operator
ostream& operator<<(ostream& out, Token& t)
{
	t.insert(out);
	return out;
}
