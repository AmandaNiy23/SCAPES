#ifndef CmpStmt_H
#define CmpStmt_H

#include "Statement.h"
#include "Program.h"
#include "Variable.h"

class CmpStmt : public Statement {
    public:
      CmpStmt(Program* pgm, Label* label=NULL, int numIds=2, int line=-1);
      virtual ~CmpStmt();
      virtual int getDest();
      virtual void setDest(int d);
      int getResult();
      virtual void compile(std::string instr);
      virtual void print();
      virtual void run();

    private:
      int result;
};

#endif
