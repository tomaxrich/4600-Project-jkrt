//Author: Thomas Richardson

#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include "Administration.h"
#include "Token.h"
#include "Scanner.h"
#include "Parser.h"

using namespace std;

//int main(int argc, char* argv[]){
//   cout << "Welcome to Our 4600 compiler!\n";
//
//   ifstream ifs;
//   ofstream ofs;
//
//   if(argc != 3){
//    cout << "Correct usage : ./plc inputFile outputFile \nExiting\n.";
//    return 0;
//   }
//
//   cout << "input from : " << argv[1] << "  output to : " << argv[2] << "\n";
//
//   ofs.open(argv[2], ofstream::out);
//
//   ifs.open(argv[1], ifstream::in);
//
//   SymbolTable symtab;
//
//   Scanner sc(ifs, symtab);
//
//   Administration compiler(ifs, ofs, sc);
//
//   if(compiler.scan() != 0){
//	cout << "\nScanning error, exiting.\n";
//   }
//
//   cout << "Total Line count " << compiler.getLinecount() << '\n';
//
//   cout << "done scanning\n";
//
//return 0;
//}

int main(int argc, char* argv[])
{

    cout << "PARSER TESTING \n";

    ifstream ifs;
    ofstream ofs;

    if(argc != 3)
    {
        cout << "Correct usage : ./plc inputFile outputFile \nExiting\n.";
        return 0;
    }

    cout << "input from : " << argv[1] << "  output to : " << argv[2] << "\n";
    ofs.open(argv[2], ofstream::out);
    ifs.open(argv[1], ifstream::in);

    SymbolTable symtab;
    Scanner sc(ifs, symtab);
    //Administration compiler(ifs, ofs, sc);
    Parser pa(sc);

    if(pa.parse() == 1)
        cout << "Error in parsing" << endl;
    else
        cout << "Parsing completed successfully" << endl;

        return 0;
}
