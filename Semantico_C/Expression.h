#ifndef Expression_H
#define Expression_H

typedef void * Expression;

enum ExpTypes {OPERANDO, OPERADOR};

Expression createExpression(int expType, Expression leftChild, Expression rightChild);

int getExpType(Expression e);

void setLeftChild(Expression e, Expression leftChild);

void setRightChild(Expression e, Expression rightChild);

Expression getLeftChild(Expression e);

Expression getRightChild(Expression e);

#endif