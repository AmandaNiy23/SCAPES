#ifndef JEQSTMT_H
#define JEQSTMT_H

#include "JmpStmt.h"
#include "Program.h"
#include "Label.h"

class JEqStmt : public Statement {
    private:
      CmpStmt* prev;
      int dest;
      int prevLineNum;

    public:
        JEqStmt(Program* pgm, Label* label=NULL, int numIds=1, int line=-1);
        int getDest();
        void setDest(int d);
        virtual ~JEqStmt();
        virtual void compile(string instr);
        virtual void run();
        void setPrevCmpLine(int);
        int getPrevCmpLine();
        void setPrevCmp(CmpStmt* cmp);
        CmpStmt* getPrevCmp();

};
#endif
