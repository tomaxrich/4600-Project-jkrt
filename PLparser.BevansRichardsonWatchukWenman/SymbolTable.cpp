/***
Author : Jesse Bevans
For CPSC 4600 Compilers project
***/

#include <iostream>
#include "SymbolTable.h"

using namespace std;

SymbolTable::SymbolTable():occupied(0), htable(TABLESIZE){

	for(int i = 0; i < TABLESIZE; i++){
		htable[i] = nullptr;
	}
loadReserve();

}

SymbolTable::~SymbolTable(){
	for(int i = 0; i < TABLESIZE; i++){
		delete htable[i]; //ensure that all the token pointers are properly deleted on destruction
		htable[i] = nullptr;
	}
}

//Inserts PL reserve words into the symbol table.
void SymbolTable::loadReserve(){
	insert(new NameToken(KW_BEGIN, -1, "begin"));
	insert(new NameToken(KW_END, -1, "end"));
	insert(new NameToken(KW_CONST, -1, "const"));
	insert(new NameToken(KW_ARRAY, -1, "array"));
	insert(new NameToken(KW_INTEGER, -1, "integer"));
	insert(new NameToken(KW_BOOLEAN, -1, "Boolean"));
	insert(new NameToken(KW_PROC, -1, "proc"));
	insert(new NameToken(KW_SKIP, -1, "skip"));
	insert(new NameToken(KW_READ, -1, "read"));
	insert(new NameToken(KW_WRITE, -1, "write"));
	insert(new NameToken(KW_CALL, -1, "call"));
	insert(new NameToken(KW_IF, -1, "if"));
	insert(new NameToken(KW_DO, -1, "do"));
	insert(new NameToken(KW_FI, -1, "fi"));
	insert(new NameToken(KW_OD, -1, "od"));
	insert(new NameToken(KW_FALSE, -1, "false"));
	insert(new NameToken(KW_TRUE, -1, "true"));
}

//search the symbol table for a given lexeme, return position if found, nullptr if not
Token* SymbolTable::search(string lex){

	int hash = hashfunc(lex);
	int done = hash - 1; //if the table is full, keep track of where the search started in case the lexeme is not found

	while(true){
        if(htable[hash] == nullptr){ //not found
            return nullptr;
        } else if(htable[hash]->getLexeme() == lex){ //if the found token matches the given lexeme
            return htable[hash];
        } else { //look at the next table entry
            ++hash;
            if(hash == done) return nullptr; //finish search if the entire table has been looked at
            if(hash == TABLESIZE) hash = 0; //wrap to 0 if max size reached
        }
	}

	return nullptr;
}

//inserts a given name token into the hash table, updates the token's position, returns pointer to the token.
Token* SymbolTable::insert(NameToken *tok){

	if(full()) return search(tok->getLexeme()); //if the table is full, search for the token in table.

	int hash = hashfunc(tok->getLexeme());

	//find open cell for the lexeme
	while(htable[hash] != nullptr){ //if cell is not empty
	if(htable[hash]->getLexeme() == tok->getLexeme()){
        	return htable[hash];}

		++hash;
		if(hash == TABLESIZE)
			hash = 0;
	}

	//when cell has been found, insert into table and update token's position value
	htable[hash] = tok;
	tok->setPosition(hash);
	++occupied;

	return htable[hash];
}

//djb2 hash function
int SymbolTable::hashfunc(string lexeme){

    unsigned long hash = 5381;
    for (char c : lexeme) {
        hash = (hash << 5) + hash + c;
    }

	hash = hash%TABLESIZE; //adjust the given hash to fit into the table
    return hash;
}

//print the symbol table to the console, for testing/debugging purposes only
void SymbolTable::printTable(){

	for(int i = 0; i < TABLESIZE; ++i){
		cout << i << " = ";
		if(htable[i] == nullptr)
			cout << "--NULL--" <<endl;
		else
			cout << htable[i]->getLexeme() << endl;
	}

}
