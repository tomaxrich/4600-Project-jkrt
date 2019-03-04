// reading a text file
#include <iostream>
#include <fstream>
#include <string>
#include "Administration.h"
#include "Token.h"
#include "Scanner.h"
#include "Symbol.h"

using namespace std;

Administration::Administration(ifstream& in, ofstream &out, Scanner &sc)
{
	outputfileptr = &out;
	inputfileptr = &in;
	scannerptr = &sc;

	lineNo = 0;
	errorCount = 0;
	string str;
};

Administration::~Administration(){}

int Administration::scan()
{
   if(inputfileptr->peek() == EOF){lineNo = 0; return 0;}

   while(inputfileptr->peek() == '\n'){
      NewLine();
      inputfileptr->get();
   }

	Token* tok;
	int x;
	while(inputfileptr->good()){

		tok = scannerptr->getToken();

		if(tok != nullptr){
             x = tok->getSymbolName();

             if(correctline && x >= 297 && x <= 300){
                switch(x){
                    case 297:
                        error("BAD_NUMERAL");
                        break;
                    case 298:
                        error("BAD_ID");
                        break;
                    case 299:
                        error("BAD_SYM");
                        break;
                    case 300: //symbol table full
                        cout << "\nFATAL ERROR : Symbol table full on line " << ++lineNo << "\n\n";
                        outputfileptr->close();
                        return 1;
                        break;
                    default:
                        break;
                }
                correctline = false;
            }
                *outputfileptr << *tok << "\n";
                //delete the token pointer if it is not a name
                if(tok->getSymbolName()  > 273){
                    delete tok;
                }
        }

        while(inputfileptr->peek() == '\n'){
            NewLine();
            inputfileptr->get();
        }
	}

    if(errorCount >= MAXERRORS){
        cout << "Max errors reached. Stopping scanning.\n";
        return 1;
    }



	outputfileptr->close();

	return 0;
};

void Administration::error(string text)
{
   string str = text;
   cout << "On line " << lineNo << " Error: " << str << "\n";
   errorCount++;
};
