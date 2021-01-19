#include <string.h>
#include <stdlib.h>
#include"Command.h"
#include"Expression.h"

typedef struct{
    int cmdType;
    Expression exp;

    //if
    CommandImpl* thenCmd;
    CommandImpl* elseCmd;

    //while
    CommandImpl* commands;

    CommandImpl* next;
}CommandImpl;

Command createCommand(int cmdType, Expression exp, Command thenCmd, Command elseCmd, Command commands, Command next){

    CommandImpl* command = malloc(sizeof(CommandImpl));

    command->cmdType=cmdType;
    command->exp=exp;
    command->thenCmd=thenCmd;
    command->elseCmd=elseCmd;
    command->commands=commands;
    command->next=next;
    
    return command;
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