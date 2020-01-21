#ifndef JMORESTMT_H
#define JMORESTMT_H

#include "JmpStmt.h"
#include "Program.h"
#include "Variable.h"

using namespace std;

class JMoreStmt : public Statement {
    private:
      CmpStmt* prev;
      int dest;
      int prevLineNum;

    public:
        JMoreStmt(Program* pgm, Label* label=NULL, int numIds=1, int line=-1);
        int getDest();
        void setDest(int d);
        virtual ~JMoreStmt();
        virtual void compile(string instr);
        virtual void run();
        virtual void print();
        void setPrevCmpLine(int);
        int getPrevCmpLine();
        void setPrevCmp(CmpStmt* cmp);
        CmpStmt* getPrevCmp();
};
#endif
