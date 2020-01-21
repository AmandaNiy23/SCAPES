#ifndef PRINTSTMT_H
#define PRINTSTMT_H

#include "Statement.h"
#include "Variable.h"
#include "Program.h"


class PrintStmt : public Statement {

    public:
      PrintStmt(Program* pgm, Label* label=NULL, int numIds=1, int line=-1);
      virtual int getDest();
      virtual void setDest(int d);
      virtual ~PrintStmt();
      virtual void compile(std::string instr);
      virtual void run();
      virtual void print();

};

#endif
