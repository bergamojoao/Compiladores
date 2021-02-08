#ifndef Expression_H
#define Expression_H

typedef void * Expression;

enum ExpTypes {OPERANDO, OPERADOR, EXP_VARIAVEL, EXP_NUMBER, OPERADOR_PLUS, OPERADOR_SUB, OPERADOR_MULT, OPERADOR_DIV};

Expression createExpression(int expType, Expression leftChild, Expression rightChild);

int getExpType(Expression e);

void setLeftChild(Expression e, Expression leftChild);

void setRightChild(Expression e, Expression rightChild);

void setExpVarName(Expression e, char* varName);

void setExpValue(Expression e, int value);

int getExpValue(Expression e);

char* getExpVarName(Expression e);

Expression getLeftChild(Expression e);

Expression getRightChild(Expression e);

#endif