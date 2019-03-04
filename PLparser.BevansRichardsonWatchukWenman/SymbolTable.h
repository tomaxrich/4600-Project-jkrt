#ifndef SymbolTable_H
#define SymbolTable_H

#include <string>
#include <vector>
#include "Token.h"
#include "NameToken.h"

#define TABLESIZE 307

/**
Stores Token pointers to keywords and user IDs/names (scannner part of project)

later : storing more info, scoping

extra goals / does it make sense to :
	extendible hashing : more efficient? Does it matter?
**/

/*
reserved words :

begin , end, const, array, integer, Boolean, proc, skip, read, write, call, if, do, fi, od, false, true

*/

using namespace std;


class SymbolTable
{
	public:
		/** Default constructor */
		SymbolTable();
		/** Default destructor */
		~SymbolTable();

		//init table with reserved words
		void loadReserve();

		//search table for token with given lexeme
		Token* search(string lex);

		//insert a given name token
		Token* insert(NameToken* tok);

		bool full(){return occupied == TABLESIZE;};

		int getOccupied(){return occupied;}

		//for debugging, prints table to console
		void printTable();
	protected:

	private:
		int occupied;			         //number of occupied cells
		vector<NameToken*> htable; 	//hash table that uses tokens
		int hashfunc(string lexeme); 	//hash function
};

#endif // SymbolTable_H
