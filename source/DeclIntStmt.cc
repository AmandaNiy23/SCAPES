#include "DeclIntStmt.h"

using namespace std;

DeclIntStmt::DeclIntStmt(Program* pgm, Label* label, int numIds, int line) : Statement(pgm, label, numIds, line, "dci") {}

DeclIntStmt::~DeclIntStmt() {}

/*
compile
    purpose: generate an object representation of an dci statement instruction
    in:
      string: instr
*/
void DeclIntStmt::compile(string instr)
{
    // split statement into arguments
    vector<string> args = parseInstr(instr);

    //set operand index based on presence of label
    int opOne = args.at(0).find(":") == string::npos ? 1 : 2;
    Variable* var = new Variable(args.at(opOne));
    var->setValue(-1);

    getPgm()->addVariable(var, args.at(opOne));
    setOperands(var);
}

/*
run
    purpose: execute instructions stored in current statement object
*/
void DeclIntStmt::run() {
    string name = getOperand(0).getIdentifier()->getName();
    Variable* variable = new Variable(name);
    getPgm()->addVariable(variable, name);
}

void DeclIntStmt::print() {
    cout << "DeclInt Stmt" << endl;
    Statement::print();
}
int DeclIntStmt::getDest(){
    return -1;
}

void DeclIntStmt::setDest(int d){}
