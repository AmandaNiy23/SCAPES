#include "EndStmt.h"
#include "Program.h"

using namespace std;

EndStmt::EndStmt(Program* pgm, Label* label, int numIds, int line) : Statement(pgm, label, numIds, line, "end") {}

EndStmt::~EndStmt() {}

void EndStmt::compile(string instr) {}

/*
run
    purpose: execute instructions stored in current statement object
*/
void EndStmt::run(){
    Program* pgm = getPgm();
    pgm->setNextStmt(pgm->getStmtSize());
    printToTerminal("-- End of Program --");
}

int EndStmt::getDest(){
    return -1;
}

void EndStmt::setDest(int d){}

void EndStmt::print() {
    cout << "End Stmt" << endl;
    Statement::print();
}
