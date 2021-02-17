#ifndef Expression_H
#define Expression_H
#include"ListaDinamica.h"

typedef void * Expression;

enum ExpTypes {OPERANDO, OPERADOR, EXP_VARIAVEL, EXP_NUMBER, OPERADOR_PLUS, OPERADOR_SUB, OPERADOR_MULT, OPERADOR_DIV, EXP_STRING, EXP_INC, EXP_DEC, EXP_ASSIGN,
    EXP_LSHIFT, EXP_RSHIFT, EXP_FUNC, OPERADOR_BITWISE};

Expression createExpression(int expType, Expression leftChild, Expression rightChild);

void setExpType(Expression e, int type);

int getExpType(Expression e);

void setLeftChild(Expression e, Expression leftChild);

void setRightChild(Expression e, Expression rightChild);

void setExpVarName(Expression e, char* varName);

void setExpValue(Expression e, int value);

int getExpValue(Expression e);

char* getExpVarName(Expression e);

Expression getLeftChild(Expression e);

Expression getRightChild(Expression e);

void setExpLinha(Expression e, int value);

void setExpColuna(Expression e, int value);

int getExpLinha(Expression e);

int getExpColuna(Expression e);

void setExpText(Expression e, char* varName);

char* getExpText(Expression e);

void setExpParametros(Expression e, Lista parametros);

Lista getExpParametros(Expression e);

int getExpPonteiro(Expression e);

void setExpPonteiro(Expression e, int ponteiro);

#endif