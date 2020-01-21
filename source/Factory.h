class Program;

#ifndef FACTORY_H
#define FACTORY_H

#include "Label.h"
#include "Statement.h"
#include "ReadStmt.h"
#include "DeclIntStmt.h"
#include "DeclArrStmt.h"
#include "PrintStmt.h"
#include "MovStmt.h"
#include "AddStmt.h"
#include "CmpStmt.h"
#include "EndStmt.h"
#include "JmpStmt.h"
#include "JMoreStmt.h"
#include "JLessStmt.h"
#include "JEqStmt.h"


class Factory {
    public:
      Statement* createStmt(std::string instr, Program* pgm, Label* label, int line);
    private:
      enum validInstr { //enumerator for all valid instructions
        dci, dca, rdi, prt, mov, add, cmp, jls, jmr, jeq, jmp, fin, invalid
      };
      validInstr resolveEnum(std::string input);
};

#endif
