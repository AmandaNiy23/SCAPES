#ifndef JLESSSTMT_H
#define JLESSSTMT_H

#include "JmpStmt.h"
#include "Program.h"
#include "Variable.h"

class JLessStmt : public Statement {
    private:
    CmpStmt* prev;
    int dest;
    int prevLineNum;

    public:
        JLessStmt(Program* pgm, Label* label=NULL, int numIds=1, int line=-1);
        int getDest();
        void setDest(int d);
        virtual ~JLessStmt();
        virtual void compile(string instr);
        virtual void run();
        void setPrevCmpLine(int);
        int getPrevCmpLine();
        void setPrevCmp(CmpStmt* cmp);
        CmpStmt* getPrevCmp();


};
#endif
