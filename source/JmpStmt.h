class Program;
class CmpStmt;

#ifndef JMPSTMT_H
#define JMPSTMT_H

#include "Statement.h"
#include "Variable.h"

class JmpStmt : public Statement {
    private:
        CmpStmt* prev;
        int dest;
        int prevLineNum;

    public:
        JmpStmt(Program* pgm, Label* label=NULL, int numIds=1, int line=-1);
        int getDest();
        void setDest(int d);
        virtual ~JmpStmt();
        virtual void compile(std::string instr);
        virtual void print();
        virtual void run();

};
#endif


