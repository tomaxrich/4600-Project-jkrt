/****

Author : Jesse Bevans

TODO : simplify logic : don't need to check that the symbol matches after entering a statement
    they should only be able to reach some statements if that symbol is already the lookahead, so double checking is redundant (but good for making sure we are correct in the first pass)

    Can also make actual 'first sets' for each function and match to that list to check whether we should go to that function or there is an error
    currently it is hard coded at each selection point instead of using a membership check
****/



#include "Parser.h"
#include <iostream>

using namespace std;

Parser::Parser(Scanner& sc)
{
    //ctor
    scptr = &sc;
    laToken = nullptr;
}

Parser::~Parser()
{
    //dtor
}

int Parser::parse()
{

    while(laToken == nullptr)
    {
        laToken = scptr->getToken();
    }
    cout << "First token : " << SymbolTypeString[laToken->getSymbolName() - 256] << endl;
    if(laToken->getSymbolName() == KW_BEGIN)
    {
        Program();
    }
    else if(laToken->getSymbolName() == SYM_EOF)
    {
        cout << "EOF\n";
        return 0;
    }
    else
    {
        Error();
        return 1;
    }


    return 0;
}

//first set :  begin
//follow set :  E
void Parser::Program()
{
    cout << "Program\n";

    if(laToken->getSymbolName() == KW_BEGIN)
    {
        Block();
    }
    else
    {
        Error();
        //return;
    }

    if(laToken->getSymbolName() == SYM_PERIOD)
        match(laToken->getSymbolName());
    else
    {
        Error();
        //return;
    }
}

//first set :  begin
//follow set :  ; .
void Parser::Block()
{
    cout << "Block\n";
    if(laToken->getSymbolName() == KW_BEGIN)
    {
        match(laToken->getSymbolName());

        //match definition part
        switch(laToken->getSymbolName())
        {
        case KW_CONST:
        case KW_PROC:
        case KW_INTEGER:
        case KW_BOOLEAN:
            DefinitionPart();
            break;
        default:
            break;
        }
        //match statement part
        switch(laToken->getSymbolName())
        {
        case KW_SKIP:
        case KW_READ:
        case KW_WRITE:
        case KW_CALL:
        case KW_IF:
        case KW_DO:
        case ID:
            StatementPart();
            break;
        default:
            break;
        }
        //match end
        if(laToken->getSymbolName() == KW_END)
        {
            match(laToken->getSymbolName());
        }
        else
        {
            Error();
            //return;
        }
    }
    else
    {
        Error();
        //return;
    }

}

//first set :  const proc integer Boolean
//follow set :  skip read write call if do name end
void Parser::DefinitionPart()
{
    cout << "DefinitionPart\n";

    switch(laToken->getSymbolName())
    {
    case KW_CONST:
    case KW_PROC:
    case KW_INTEGER:
    case KW_BOOLEAN:
        Definition();
        break;
    case KW_SKIP:
    case KW_READ:
    case KW_WRITE:
    case KW_CALL:
    case KW_IF:
    case KW_DO:
    case ID:
    case KW_END:
        return;
    default:
        Error();
        //return;
    }

    if(laToken->getSymbolName() == SYM_SEMICOLON)
    {
        match(laToken->getSymbolName());
        DefinitionPart();
    }
    else
    {
        Error();
        //return;
    }

    DefinitionPart();
}

//first set :  skip read write call if do letter
//follow set :  [] fi if od end
void Parser::StatementPart()
{
    cout << "StatementPart\n";
    switch(laToken->getSymbolName())
    {
    case KW_SKIP:
    case KW_READ:
    case KW_WRITE:
    case KW_CALL:
    case KW_IF:
    case KW_DO:
    case ID:
        Statement();
        break;
    case SYM_GUARD:
    case KW_FI:
    case KW_OD:
    case KW_END:
        return;
    default:
        Error();
        //return;
    }

    if(laToken->getSymbolName() == SYM_SEMICOLON)
    {
        match(laToken->getSymbolName());
        StatementPart();
    }
    else
    {
        Error();
        //return;
    }

}

//first set :  const proc integer Boolean
//follow set :  ;
void Parser::Definition()
{
    cout << "Definition\n";
    switch(laToken->getSymbolName())
    {
    case KW_CONST:
        ConstantDefinition();
        return;
    case KW_INTEGER:
    case KW_BOOLEAN:
        VariableDefinition();
        return;
    case KW_PROC:
        ProcedureDefinition();
        return;
    case SYM_SEMICOLON:
        return;
    default:
        cout << "DEFN ERROR";
        Error();
        break;
    }

    Definition();
}

//first set :  const
//follow set :  ;
void Parser::ConstantDefinition()
{
    cout << "ConstantDefinition\n";
    //const
    if(laToken->getSymbolName() == KW_CONST)
    {
        match(laToken->getSymbolName());
    }
    else
    {
        Error();
        //return;
    }
    //const name
    if(laToken->getSymbolName() == ID)
    {
        ConstantName();
    }
    else
    {
        Error();
        //return;
    }

    //equals
    if(laToken->getSymbolName() == SYM_EQUAL)
    {
        match(laToken->getSymbolName());
    }
    else
    {
        Error();
        //return;
    }

    //constant
    switch(laToken->getSymbolName())
    {
    case NUMERAL:
    case KW_FALSE:
    case KW_TRUE:
    case ID:
        Constant();
        break;
    default:
        Error();
        //return;
    }
}

//first set :  integer boolean
//follow set :  ;
void Parser::VariableDefinition()
{
    cout << "VariableDefinition\n";
    //type symbol
    if(laToken->getSymbolName() == KW_INTEGER | laToken->getSymbolName() == KW_BOOLEAN)
    {
        TypeSymbol();
    }
    else
    {
        Error();
        //return;
    }
    //variable definition A
    if(laToken->getSymbolName() == ID | laToken->getSymbolName() == KW_ARRAY)
    {
        VariableDefinitionA();
    }
    else
    {
        Error();
        //return;
    }
}

//first set :  array letter
//follow set :  ;
void Parser::VariableDefinitionA()
{
    cout << "VariableDefinitionA\n";
    if(laToken->getSymbolName() == ID)
    {
        VariableList();
        return;
    }
    else if(laToken->getSymbolName() == KW_ARRAY)
    {
        match(laToken->getSymbolName());
        if(laToken->getSymbolName() == ID)
        {
            VariableList();
        }
        else
        {
            Error();
            //return;
        }

        if(laToken->getSymbolName() == SYM_LEFTSQUARE)
        {
            match(laToken->getSymbolName());
        }
        else
        {
            Error();
            //return;
        }

        switch(laToken->getSymbolName())
        {
        case NUMERAL:
        case KW_TRUE:
        case KW_FALSE:
        case ID:
            Constant();
            break;
        default:
            Error();
            //return;
            break;
        }

        if(laToken->getSymbolName() == SYM_RIGHTSQUARE)
        {
            match(laToken->getSymbolName());
        }
        else
        {
            Error();
            //return;
        }
    }
    else
    {
        Error();
        //return;
    }


}

void Parser::TypeSymbol()
{
    switch(laToken->getSymbolName())
    {
    case KW_INTEGER:
    case KW_BOOLEAN:
        match(laToken->getSymbolName());
        break;
    default:
        Error();
        //return;
    }
}

//first set :  letter
//follow set :   := [ ;
void Parser::VariableList()
{
    cout << "VariableList\n";

    switch(laToken->getSymbolName())
    {
    case ID:
        VariableName();
        VariableListA();
        break;
    default:
        Error();
        //return;
    }
}

//first set :  ,
//follow set :  := ;
void Parser::VariableListA()
{
    switch(laToken->getSymbolName())
    {
    case SYM_COMMA:
        match(laToken->getSymbolName());
        VariableList();
        break;
    case SYM_ASSIGNMENT:
    case SYM_LEFTSQUARE:
    case SYM_SEMICOLON:
        return;
    default:
        Error();
        //return;
    }

}

//first set :  proc
//follow set :  ;
void Parser::ProcedureDefinition()
{
    if(laToken->getSymbolName() == KW_PROC)
    {
        match(laToken->getSymbolName());
        ProcedureName(); ///add in more IF to make sure? redundant
        Block();
    }
    else
    {
        Error();
        //return;
    }
}

//first set : skip read write call if do letter
//follow set : ;
void Parser::Statement()
{
    cout << "Statement\n";

    switch(laToken->getSymbolName())
    {
    case KW_SKIP:
        EmptyStatement();
        break;
    case KW_CALL:
        ProcedureStatement();
        break;
    case KW_READ:
        ReadStatement();
        break;
    case KW_WRITE:
        WriteStatement();
        break;
    case KW_IF:
        IfStatement();
        break;
    case KW_DO:
        DoStatement();
        break;
    case ID: //assignment statement
        AssignmentStatement();
        break;
    default:
        Error();
        //return;
    }
}

//first set : skip
//follow set : ;
void Parser::EmptyStatement()
{
    cout << "EmptyStatement\n";
    if(laToken->getSymbolName() == KW_SKIP)
    {
        match(laToken->getSymbolName());
    }
    else
    {
        Error();
        //return;
    }

}

//first set : read
//follow set : ;
void Parser::ReadStatement()
{
    cout << "ReadStatement\n";

    if(laToken->getSymbolName() == KW_READ)
    {
        match(laToken->getSymbolName());
        VariableAccessList();
    }
    else
    {
        Error();
        //return;
    }

}

//first set : write
//follow set : ;
void Parser::WriteStatement()
{
    cout << "WriteStatement \n";

    if(laToken->getSymbolName() == KW_WRITE)
    {
        match(laToken->getSymbolName());
        ExpressionList();
    }
    else
    {
        Error();
        //return;
    }
}

//first set : letter
//follow set : ;
void Parser::AssignmentStatement()
{
    cout << "AssignmentStatement  \n";
    //variable access list
    if(laToken->getSymbolName() == ID)
    {
        VariableAccessList();
    }
    else
    {
        Error();
        //return;
    }
    //assignment symbol
    if(laToken->getSymbolName() == SYM_ASSIGNMENT)
    {
        match(laToken->getSymbolName());
    }
    else
    {
        Error();
        //return;
    }
    //Expression - ( ~ false true number letter
    switch(laToken->getSymbolName())
    {
    case SYM_MINUS:
    case SYM_LEFTPAREN:
    case KW_FALSE:
    case KW_TRUE:
    case NUMERAL:
    case ID:
        ExpressionList();
        break;
    default:
        Error();
        //return;
    }

}

//first set : call
//follow set : ;
void Parser::ProcedureStatement()
{
    cout << "ProcedureStatement\n";
    if(laToken->getSymbolName() == KW_CALL)
    {
        match(laToken->getSymbolName());
    }
    else
    {
        Error();
        //return;
    }

    if(laToken->getSymbolName() == ID)
    {
        ProcedureName();
    }
    else
    {
        Error();
        //return;
    }
}

//first set : if
//follow set : ;
void Parser::IfStatement()
{
    cout << "IfStatement\n";

    if(laToken->getSymbolName() == KW_IF)
    {
        match(laToken->getSymbolName());
    }
    else
    {
        Error();
        //return;
    }
    ///add checks for this (expression)
    GuardedCommmandList();

    if(laToken->getSymbolName() == KW_FI)
    {
        match(laToken->getSymbolName());
    }
    else
    {
        Error();
        //return;
    }
}

//first set : do
//follow set : ;
void Parser::DoStatement()
{
    cout << "DoStatement\n";

    if(laToken->getSymbolName() == KW_DO)
    {
        match(laToken->getSymbolName());
    }
    else
    {
        Error();
        //return;
    }

    GuardedCommmandList();

    if(laToken->getSymbolName() == KW_OD)
    {
        match(laToken->getSymbolName());
    }
    else
    {
        Error();
        //return;
    }
}

//first set : letter
//follow set : := ;
void Parser::VariableAccessList()
{
    cout << "VariableAccessList\n";

    if(laToken->getSymbolName() == ID)
    {
        VariableAccess();
        VariableAccessListA();
    }
    else
    {
        Error();
        //return;
    }


}

//first set : ,
//follow set : := ;
void Parser::VariableAccessListA()
{
    cout << "VariableAccessListA\n";

    switch(laToken->getSymbolName())
    {
    case SYM_COMMA:
        match(laToken->getSymbolName());
        VariableList();
        break;
    case SYM_ASSIGNMENT:
    case SYM_SEMICOLON:
        return;
    default:
        Error();
        //return;

    }


}

//first set : letter
//follow set : * / \ + - < > = ^ | := ( [ , ;
void Parser::VariableAccess()
{
    cout << "VariableAccess \n";

    if(laToken->getSymbolName() == ID)
    {
        VariableName();
        IndexedSelector();
    }
}

//first set : - ( ~ false true number letter
//follow set : ;
void Parser::ExpressionList()
{
    cout << "ExpressionList \n";

    switch(laToken->getSymbolName())
    {
    case SYM_MINUS:
    case SYM_LEFTPAREN:
    case SYM_NOT:
    case KW_FALSE:
    case KW_TRUE:
    case NUMERAL:
    case ID:
        Expression();
        ExpressionListA();
        break;
    default:
        Error();
        //return;
    }
}

//first set : ,
//follow set : ;
void Parser::ExpressionListA()
{
    cout << "ExpressionListA \n";

    switch(laToken->getSymbolName())
    {
    case SYM_COMMA:
        match(laToken->getSymbolName());
        ExpressionList();
        break;
    case SYM_SEMICOLON:
        return;
    default:
        Error();
        //return;
    }
}

//first set: - ( ~ false true name
//follow set: guard fi od
void Parser::GuardedCommand()
{
    switch(laToken->getSymbolName())
    {
    case SYM_MINUS:
    case SYM_LEFTPAREN:
    case SYM_NOT:
    case KW_TRUE:
    case KW_FALSE:
    case ID:
        Expression();
        if(laToken->getSymbolName() == SYM_RIGHTARROW)
        {
            match(laToken->getSymbolName());
            StatementPart();
        }
        else
        {
            Error();
            //return;
        }
        break;
    default:
        Error();
        //return;
        break;
    }
}

//first set : - ( ~ false true name
//follow set : fi od
void Parser::GuardedCommmandList()
{
    cout << "GuardedCommandList \n";

    GuardedCommand();
///
    switch(laToken->getSymbolName())
    {
	case SYM_GUARD:
		GuardedCommmandListA();
		break;
	case KW_FI:
	case KW_OD:
		return;
	default:
		Error();
		//return;
    }

}

//first set : []
//follow set : fi od
void Parser::GuardedCommmandListA()
{
    cout << "GuardedCommandListA \n";

    switch(laToken->getSymbolName())
    {
    case SYM_GUARD:
        match(laToken->getSymbolName());
        GuardedCommmandList();
        break;
    case KW_FI:
    case KW_OD:
        return;
    default:
        Error();
        //return;
    }
}

//first set : - ( ~ false true number letter
//follow set : , ) ] ;
void Parser::Expression()
{
    cout << "Expression \n";

    switch(laToken->getSymbolName())
    {
    case SYM_MINUS:
    case SYM_LEFTPAREN:
    case SYM_NOT:
    case KW_TRUE:
    case KW_FALSE:
    case ID:
    case NUMERAL:
        PrimaryExpression();
        ExpressionA();
        break;
    default:
        Error();
        //return;
        break;
    }
}

//first set : and or
//follow set : , -> ) ] ;
void Parser::ExpressionA()
{
    cout << "ExpressionA \n";

    switch(laToken->getSymbolName())
    {
    case SYM_AND:
    case SYM_OR:
        PrimaryOperator();
        PrimaryExpression();
        break;
    case SYM_COMMA:
    case SYM_RIGHTPAREN:
    case SYM_RIGHTARROW:
    case SYM_RIGHTSQUARE:
    case SYM_SEMICOLON:
        return;
    default:
        Error();
        //return;
    }
}

//first set : and or
//follow set : - ( ~ false true number letter
void Parser::PrimaryOperator()
{
    cout << "PrimaryOperator \n";
    switch(laToken->getSymbolName())
    {
    case SYM_AND:
    case SYM_OR:
        match(laToken->getSymbolName());
        break;
    default:
        Error();
        //return;
    }
}

//first set : - ( ~ false true number letter
//follow set : ^ | , ) ] ;
void Parser::PrimaryExpression()
{
    cout << "PrimaryExpression \n";

    switch(laToken->getSymbolName())
    {
    case SYM_MINUS:
    case SYM_LEFTPAREN:
    case SYM_NOT:
    case KW_TRUE:
    case KW_FALSE:
    case ID:
    case NUMERAL:
        SimpleExpression();
        PrimaryExpressionA();
        break;
    default:
        Error();
        //return;
    }
}

//first set : < > =
//follow set : ^ | , ) ] ; ->
void Parser::PrimaryExpressionA()
{
    cout << "PrimaryExpressionA \n";

    switch(laToken->getSymbolName())
    {
    case SYM_LESSTHAN:
    case SYM_GREATERTHAN:
    case SYM_EQUAL:
        RelationalOperator();
        SimpleExpression();
        break;
    case SYM_AND:
    case SYM_OR:
    case SYM_COMMA:
    case SYM_RIGHTPAREN:
    case SYM_RIGHTSQUARE:
    case SYM_SEMICOLON:
	case SYM_RIGHTARROW:
        return;
    default:
        Error();
        //return;
        break;
    }
}

//first set : < > =
//follow set : - ( ~ false true number letter
void Parser::RelationalOperator()
{
    cout << "RelationalOperator \n";

    switch(laToken->getSymbolName())
    {
    case SYM_LESSTHAN:
    case SYM_GREATERTHAN:
    case SYM_EQUAL:
        match(laToken->getSymbolName());
        break;
    default:
        Error();
        //return;
        break;
    }
}

//first set : - ( ~ false true number letter
//follow set : < > = ^ | , ) ] ;
void Parser::SimpleExpression()
{
    cout << "SimpleExpression \n";

    if(laToken->getSymbolName() == SYM_MINUS)
    {
        match(laToken->getSymbolName());
    }
    SimpleExpressionA();

}

//first set : ( ~ false true number letter
//follow set : < > = ^ | , ) ] ; ->
void Parser::SimpleExpressionA()
{
    cout << "SimpleExpressionA \n";

    switch(laToken->getSymbolName())
    {
    case SYM_LEFTPAREN:
    case SYM_NOT:
    case KW_FALSE:
    case KW_TRUE:
    case NUMERAL:
    case ID:
        Term();
        SimpleExpressionB();
        break;
	case SYM_LESSTHAN:
	case SYM_GREATERTHAN:
	case SYM_EQUAL:
	case SYM_AND:
	case SYM_OR:
	case SYM_COMMA:
	case SYM_RIGHTPAREN:
	case SYM_RIGHTSQUARE:
	case SYM_SEMICOLON:
	case SYM_RIGHTARROW:
		return;
    default:
        Error();
        //return;
    }
}

//first set : + -
//follow set : < > = ^ | , ) ] ; ->
void Parser::SimpleExpressionB()
{
    cout << "SimpleExpressionB \n";

    switch(laToken->getSymbolName())
    {
    case SYM_PLUS:
    case SYM_MINUS:
        AddingOperator();
        SimpleExpressionA();
        break;
    case SYM_LESSTHAN:
    case SYM_GREATERTHAN:
    case SYM_EQUAL:
    case SYM_AND:
    case SYM_OR:
    case SYM_COMMA:
    case SYM_RIGHTPAREN:
	case SYM_RIGHTARROW:
	case SYM_RIGHTSQUARE:
    case SYM_LEFTPAREN:
    case SYM_SEMICOLON:
        return;
    default:
        Error();
        //return;
        break;
    }
}

//first set : + -
//follow set : + - < > = ^ | , ) ] ;
void Parser::AddingOperator()
{
    cout << "AddingOperator \n";

    switch(laToken->getSymbolName())
    {
    case SYM_PLUS:
    case SYM_MINUS:
        match(laToken->getSymbolName());
        break;
    default:
        Error();
        //return;
    }
}

//first set : ( ~ false true number letter
//follow set : + - < > = ^ | , ) ] ;
void Parser::Term()
{
    cout << "Term \n";

    switch(laToken->getSymbolName())
    {
    case SYM_LEFTPAREN:
    case SYM_NOT:
    case KW_FALSE:
    case KW_TRUE:
    case NUMERAL:
    case ID:
        Factor();
        TermA();
        break;
    default:
        Error();
        //return;
    }
}

//first set : * / \
//follow set : + - < > = ^ | , ) ] ;
void Parser::TermA()
{
    cout << "TermA \n";

    switch(laToken->getSymbolName())
    {
    case SYM_MULTIPLY:
    case SYM_DIVIDE:
    case SYM_MODULO:
        MultiplyingOperator();
        Term();
        break;
    case SYM_PLUS:
    case SYM_MINUS:
    case SYM_LESSTHAN:
    case SYM_GREATERTHAN:
    case SYM_EQUAL:
    case SYM_AND:
    case SYM_OR:
    case SYM_COMMA:
	case SYM_RIGHTARROW:
    case SYM_RIGHTPAREN:
    case SYM_RIGHTSQUARE:
    case SYM_SEMICOLON:
        return;
    default:
        Error();
        //return;
    }
}

//first set : ( ^ false true number letter
//follow set : * / \ + - < > = ^ | , ) ] ;
void Parser::Factor()
{
    cout << "Factor \n";

    switch(laToken->getSymbolName())
    {
    case NUMERAL:
    case KW_TRUE:
    case KW_FALSE:
        ///case ID: ///AMBIGUITY ALERT !!!! For now we will send it down the variable access path
        Constant();
        break;
    case ID:
        VariableAccess();
        break;
    case SYM_LEFTPAREN:
        match(laToken->getSymbolName());
        Expression();
        if(laToken->getSymbolName() == SYM_RIGHTPAREN)
            match(laToken->getSymbolName());
        else
        {
            Error();
            //return;
        }
        break;
    case SYM_NOT:
        match(laToken->getSymbolName());
        Factor();
        break;

    }
}

//first set : * / \
//follow set : ( ~ false true number letter
void Parser::MultiplyingOperator()
{
    cout << "MultiplyingOperator \n";

    switch(laToken->getSymbolName())
    {
    case SYM_MULTIPLY:
    case SYM_DIVIDE:
    case SYM_MODULO:
        match(laToken->getSymbolName());
        break;
    default:
        Error();
        //return;
    }
}

//first set : [
//follow set : * / \ + - < > = ^ | := -> ) ] , ;
void Parser::IndexedSelector()
{
    cout << "IndexedSelector \n";

    switch(laToken->getSymbolName())
    {
    case SYM_LEFTSQUARE:
        match(laToken->getSymbolName());
        Expression();
        if(laToken->getSymbolName() == SYM_RIGHTSQUARE)
        {
            match(laToken->getSymbolName());
        }
        else
        {
            Error();
            //return;
        }
        break;
    case SYM_MULTIPLY:
    case SYM_MODULO:
    case SYM_DIVIDE:
    case SYM_PLUS:
    case SYM_MINUS:
    case SYM_LESSTHAN:
    case SYM_GREATERTHAN:
    case SYM_EQUAL:
    case SYM_AND:
    case SYM_OR:
    case SYM_RIGHTARROW:
    case SYM_ASSIGNMENT:
    case SYM_RIGHTPAREN:
    case SYM_RIGHTSQUARE:
    case SYM_COMMA:
    case SYM_SEMICOLON:
        return;
    default:
        Error();
        //return;
        break;
    }
}

//first set : false true number letter
//follow set : * / \ + - < > = ^ | , ) ] ;
void Parser::Constant()
{
    cout << "Constant\n";
    switch(laToken->getSymbolName())
    {
    case NUMERAL:
        Numeral();
        break;
    case KW_TRUE:
    case KW_FALSE:
        BooleanSymbol();
        break;
    case ID:
        ConstantName();
        break;
    default:
        Error();
        //return;
        break;
    }
}

//first set : false true
//follow set : * / \ + - < > = ^ | , ) ] ;
void Parser::BooleanSymbol()
{
    cout << "BooleanSymbol \n";

    switch(laToken->getSymbolName())
    {
    case KW_TRUE:
    case KW_FALSE:
        match(laToken->getSymbolName());
        break;
    default:
        Error();
        //return;
    }
}

//first set : number
//follow set : * / \ + - < > = ^ | , ) ] ;
void Parser::Numeral()
{
    cout << "Numeral \n";
    if(laToken->getSymbolName() == NUMERAL)
        match(laToken->getSymbolName());
    else
    {
        Error();
        //return;
    }
}

//first set : letter
//follow set : * / \ + - < > = ^ | :=  , ) ] ;
void Parser::VariableName()
{
    cout << "VariableName \n";
    if(laToken->getSymbolName() == ID)
    {
        match(laToken->getSymbolName());
        //Name();
    }

}

//first set : letter
//follow set : * / \ + - < > = ^ | , ) ] = ;
void Parser::ConstantName()
{
    cout << "ConstantName \n";
    if(laToken->getSymbolName() == ID)
    {
        match(laToken->getSymbolName());
        //Name();
    }
}

//first set : letter
//follow set : ; begin
void Parser::ProcedureName()
{
    cout << "ProcedureName \n";
    if(laToken->getSymbolName() == ID)
    {
        match(laToken->getSymbolName());
        //Name();
    }
}

//first set : letter
//follow set : * / \ + - < > = ^ | :=  , ) ] ;
void Parser::Name()
{
    cout << "Name \n";
    if(laToken->getSymbolName() == ID)
    {
        match(laToken->getSymbolName());
        //Name();
    }
}


void Parser::Error()
{
    cout << "\nError!!!" << endl;
    laToken = scptr->getToken();
    cout << "Got new token : " << SymbolTypeString[laToken->getSymbolName() - 256] << endl;
}

void Parser::Error(Symbol seen, Symbol expected)
{

}

void Parser::match(Symbol sym)
{
    cout << "match terminal : " << SymbolTypeString[sym - 256] << endl;
    do
    {
        laToken = scptr->getToken();
    }
    while(laToken == nullptr);
    cout << "Got new token : " << SymbolTypeString[laToken->getSymbolName() - 256] << endl;
}

//bool Parser::isMember(){
//
//}