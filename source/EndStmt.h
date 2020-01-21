#ifndef ENDSTMT_H
#define ENDSTMT_H

#include "Statement.h"

class EndStmt : public Statement {
    public:
      EndStmt(Program* pgm, Label* label=NULL, int numIds=0, int line=-1);
      virtual int getDest();
      virtual void setDest(int d);
      virtual ~EndStmt();
      virtual void compile(std::string instr);
      virtual void run();
      virtual void print();
      //virtual void run();
};
#endif
