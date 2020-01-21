#ifndef ADDSTMT_H
#define ADDSTMT_H

#include "Statement.h"
#include "Program.h"
#include "Variable.h"

class AddStmt : public Statement {
    public:
      AddStmt(Program* pgm, Label* label=NULL, int numIds=2, int line=-1);
      virtual ~AddStmt();
      virtual int getDest();
      virtual void setDest(int d);
      virtual void compile(std::string instr);
      virtual void print();
      virtual void run();
};
#endif
