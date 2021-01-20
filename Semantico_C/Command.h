#ifndef Command_H
#define Command_H
#include"Expression.h"

typedef void * Command;

enum CmdType {WHILE, IF, EXPRESSAO};

Command createCommand(int cmdType, Expression exp, Command thenCmd, Command elseCmd, Command commands, Command next);

int getCmdType(Command c);

Expression getExp(Command c);

Command getThenCmd(Command c);

Command getElseCmd(Command c);

Command getCommands(Command c);

Command getNextCommand(Command c);

#endif