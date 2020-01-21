#ifndef MOVSTMT_H
#define MOVSTMT_H

#include "Statement.h"
#include "Variable.h"
#include "Program.h"

class MovStmt : public Statement {
    public:
      MovStmt(Program* pgm, Label* label=NULL, int numIds=2, int line=-1);
      virtual ~MovStmt();
      virtual int getDest();
      virtual void setDest(int d);
      virtual void compile(std::string instr);
      virtual void print();
      virtual void run();
};

#endif
