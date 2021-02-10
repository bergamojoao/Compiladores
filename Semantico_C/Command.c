#include <string.h>
#include <stdlib.h>
#include"Command.h"
#include"Expression.h"

typedef struct cmd{
    int cmdType;
    int coluna;
    int linha;
    char texto[180];
    Expression exp;
    Expression exp2;
    Expression exp3;

    //if
    struct cmd* thenCmd;
    struct cmd* elseCmd;

    //while
    struct cmd* commands;

    struct cmd* next;
}CommandImpl;

Command createCommand(int cmdType, Expression exp, Command thenCmd, Command elseCmd, Command commands, Command next){

    CommandImpl* command = malloc(sizeof(CommandImpl));

    command->cmdType=cmdType;
    command->exp=exp;
    command->exp2=NULL;
    command->exp3=NULL;
    command->thenCmd=thenCmd;
    command->elseCmd=elseCmd;
    command->commands=commands;
    command->next=next;
    
    return command;
}

Command createReturn(Expression exp, int linha, int coluna, char* text){

    CommandImpl* command = malloc(sizeof(CommandImpl));

    command->cmdType=RETURN_CMD;
    command->exp=exp;
    command->exp2=NULL;
    command->exp3=NULL;
    command->thenCmd=NULL;
    command->elseCmd=NULL;
    command->commands=NULL;
    command->next=NULL;
    command->coluna=coluna;
    command->linha=linha;
    strcpy(command->texto, text);
    
    return command;
}

Command createCmdFor(Expression exp3, Command bloco){
    CommandImpl* command = malloc(sizeof(CommandImpl));

    command->cmdType=FOR_CMD;
    command->exp=NULL;
    command->exp2=NULL;
    command->exp3=exp3;
    command->commands=bloco;
    command->thenCmd=NULL;
    command->elseCmd=NULL;
    command->next=NULL;
}

void setCmdExp2(Command c, Expression exp2){
    CommandImpl *cmd = c;
    cmd->exp2=exp2;
}

void setCmdExp1(Command c, Expression exp1){
    CommandImpl *cmd = c;
    cmd->exp=exp1;
}

void setNextCommand(Command c, Command next){
    CommandImpl *cmd = c;
    cmd->next=next;
}

int getCmdType(Command c){
    CommandImpl *cmd = c;
    return cmd->cmdType;
}

Expression getExp(Command c){
    CommandImpl *cmd = c;
    return cmd->exp;
}

Command getThenCmd(Command c){
    CommandImpl *cmd = c;
    return cmd->thenCmd;
}

Command getElseCmd(Command c){
    CommandImpl *cmd = c;
    return cmd->elseCmd;
}

Command getCommands(Command c){
    CommandImpl *cmd = c;
    return cmd->commands;
}

Command getNextCommand(Command c){
    CommandImpl *cmd = c;
    return cmd->next;
}

int getCmdLinha(Command c){
    CommandImpl *cmd = c;
    return cmd->linha;
}

int getCmdColuna(Command c){
    CommandImpl *cmd = c;
    return cmd->coluna;
}

char* getCmdText(Command c){
    CommandImpl *cmd = c;
    return cmd->texto;
}