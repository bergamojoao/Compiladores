#ifndef Command_H
#define Command_H
#include"Expression.h"

typedef void * Command;

enum CmdType {WHILE_CMD, IF_CMD, EXPRESSAO, FOR_CMD};

Command createCommand(int cmdType, Expression exp, Command thenCmd, Command elseCmd, Command commands, Command next);

Command createCmdFor(Expression exp1, Command bloco);

void setCmdExp2(Command c, Expression exp2);

void setCmdExp1(Command c, Expression exp1);

void setNextCommand(Command c, Command next);

int getCmdType(Command c);

Expression getExp(Command c);

Command getThenCmd(Command c);

Command getElseCmd(Command c);

Command getCommands(Command c);

Command getNextCommand(Command c);

#endif