#ifndef READSTMT_H
#define READSTMT_H

#include <string>
#include "Statement.h"
#include "Program.h"
#include "Label.h"

using namespace std;

class ReadStmt : public Statement {
    public:
      ReadStmt(Program* pgm, Label* label=NULL, int numIds=1, int line=-1);
      virtual ~ReadStmt();
      virtual int getDest();
      virtual void setDest(int d);
      virtual void compile(std::string instr);
      virtual void run();
      virtual void print();


};

#endif
