#ifndef PARSER_H
#define PARSER_H

#include "Symbol.h"
#include "Scanner.h"

class Parser
{
   public:
      Parser(Scanner& scanner);
      virtual ~Parser();
      int parse();

   protected:

   private:

      void Program(); //start symbol
      void Block();
      void DefinitionPart();
      void StatementPart();
      void Definition();
      void ConstantDefinition();
      void VariableDefinition();
      void VariableDefinitionA();
      void TypeSymbol();
      void VariableList();
      void VariableListA();
      void ProcedureDefinition();
      void Statement();
      void EmptyStatement();
      void ReadStatement();
      void WriteStatement();
      void AssignmentStatement();
      void ProcedureStatement();
      void IfStatement();
      void DoStatement();
      void VariableAccessList();
      void VariableAccessListA();
      void VariableAccess();
      void ExpressionList();
      void ExpressionListA();
      void GuardedCommand();
      void GuardedCommmandList();
      void GuardedCommmandListA();
      void Expression();
      void ExpressionA();
      void PrimaryOperator();
      void PrimaryExpression();
      void PrimaryExpressionA();
      void RelationalOperator();
      void SimpleExpression();
      void SimpleExpressionA();
      void SimpleExpressionB();
      void AddingOperator();
      void Term();
      void TermA();
      void Factor();
      void MultiplyingOperator();
      void VariableName();
      void VariableNameA();
      void IndexedSelector();
      void Constant();
      void BooleanSymbol();
      void Numeral();
      void NumeralA();
      void ConstantName();
      void ProcedureName();
      void Name();
      void NameA();
      void Error();

      void match(Symbol sym);
      //bool isMember();


      Token *laToken, *currToken;

      Scanner* scptr;

      char SymbolTypeString[47][20] = {
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
      "SYM_RIGHTPAREN",
      "SYM_LEFTPAREN",
      "SYM_ASSIGNMENT",
      "SYM_GUARD",
      "SYM_RIGHTARROW",
      "SYM_COMMENT",
      "BAD_NUMERAL",
      "BAD_ID",
      "BAD_SYM",
      "BAD_SCAN",
      "NONAME",
      "EOF"
      };
};

#endif // PARSER_H
