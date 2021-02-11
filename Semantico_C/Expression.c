#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include"Expression.h"

typedef struct exp{
    int expType;
    char varName[150];
    char text[180];
    int linha;
    int coluna;
    int value;
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

void setExpVarName(Expression e, char* varName){
    ExpressionImpl *exp = e;
    strcpy(exp->varName,varName);
}

char* getExpVarName(Expression e){
    ExpressionImpl *exp = e;
    return exp->varName;
}

void setExpValue(Expression e, int value){
    ExpressionImpl *exp = e;
    exp->value=value;
}

int getExpValue(Expression e){
    ExpressionImpl *exp = e;
    return exp->value;
}

Expression getLeftChild(Expression e){
    ExpressionImpl *exp = e;
    return exp->leftChild;
}

Expression getRightChild(Expression e){
    ExpressionImpl *exp = e;
    return exp->rightChild;
}

void setExpLinha(Expression e, int value){
    ExpressionImpl *exp = e;
    exp->linha=value;
}

void setExpColuna(Expression e, int value){
    ExpressionImpl *exp = e;
    exp->coluna=value;
}

int getExpLinha(Expression e){
    ExpressionImpl *exp = e;
    return exp->linha;
}

int getExpColuna(Expression e){
    ExpressionImpl *exp = e;
    return exp->coluna;
}

void setExpText(Expression e, char* varName){
    ExpressionImpl *exp = e;
    strcpy(exp->text,varName);
}

char* getExpText(Expression e){
    ExpressionImpl *exp = e;
    return exp->text;
}