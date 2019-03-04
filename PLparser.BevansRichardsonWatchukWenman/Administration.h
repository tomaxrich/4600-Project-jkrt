


//Admin class is concerned with providing services as error reporting,
//and for the overall admin of the scanner;
//its role will change a new phases are added

#ifndef ADMINISTRATION_H
#define ADMINISTRATION_H
#include <string>
#include <iostream>
#include <fstream>
#include "Scanner.h"
//this is the max number of errors before the compiler bails out
#define MAXERRORS 10

//each phase has its kind of errors
//enum errorkind{ScanE,ParseE,ScopeE,TypeE};

using namespace std;

class Administration
{
  public:

	//set up input and output files for scanning
	Administration(ifstream& in, ofstream &out, Scanner &sc);

	//destructor
	~Administration();

	//Begin a new line of input
	void NewLine(){lineNo++; correctline = true;}

	//Error function for the phases
	void error(string text);

	//call scanner from here
	int scan();

	int getLinecount(){return lineNo;};

	private:
	//output file
	ofstream *outputfileptr;

	//input file
	ifstream *inputfileptr;

	//scanner
	Scanner *scannerptr;

	//maintain the current line number
	int lineNo;

	//report error only if correct line is true; prevents multiple/redundant error/line
	bool correctline;

	//count the number of errors
	int errorCount;

	enum errorkind {ScanE,ParseE,ScopeE,TypeE};
};
#endif
