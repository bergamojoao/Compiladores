#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include"Expression.h"

typedef struct exp{
    int expType;
    struct exp* leftChild;
    struct exp* rightChild;
}ExpressionImpl;

Expression createExpression(int expType, Expression leftChild, Expression rightChild){
    
    ExpressionImpl* expression = malloc(sizeof(ExpressionImpl));

    expression->expType=expType;
    expression->leftChild=leftChild;
    expression->rightChild=rightChild;
    
    return expression;
}

int getExpType(Expression e){
    ExpressionImpl *exp = e;
    return exp->expType;
}

void setLeftChild(Expression e, Expression leftChild){
    ExpressionImpl *exp = e;
    exp->leftChild=leftChild;
}

void setRightChild(Expression e, Expression rightChild){
    ExpressionImpl *exp = e;
    exp->rightChild=rightChild;
}

Expression getLeftChild(Expression e){
    ExpressionImpl *exp = e;
    return exp->leftChild;
}

Expression getRightChild(Expression e){
    ExpressionImpl *exp = e;
    return exp->rightChild;
}