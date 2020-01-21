#ifndef DECLINTSTMT_H
#define DECLINTSTMT_H

#include "Statement.h"
#include "Variable.h"
#include "Program.h"

class DeclIntStmt : public Statement {
    public:
      DeclIntStmt(Program* pgm, Label* label=NULL, int numIds=1, int line=-1);
      virtual int getDest();
      virtual void setDest(int d);
      virtual ~DeclIntStmt();
      virtual void compile(std::string instr);
      virtual void print();
      virtual void run();
};
#endif
