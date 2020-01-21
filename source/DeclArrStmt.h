#ifndef DECLARRSTMT_H
#define DECLARRSTMT_H

#include "Statement.h"
#include "Variable.h"
#include "Program.h"

class DeclArrStmt : public Statement {
    public:
      DeclArrStmt(Program* pgm, Label* label=NULL, int numIds=2, int line=-1);
      virtual int getDest();
      virtual void setDest(int d);
      virtual ~DeclArrStmt();
      virtual void compile(std::string instr);
      virtual void print();
      virtual void run();
};

#endif
