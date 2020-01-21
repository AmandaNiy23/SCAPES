#include "PrintStmt.h"

using namespace std;

PrintStmt::PrintStmt(Program* pgm, Label* label, int numIds, int line) : Statement(pgm, label, numIds, line, "prt") {}

PrintStmt::~PrintStmt() {}

/*
compile
  purpose:
      read in a single instruction and translate contents into PrintStmt

    in:
      string: instr - single line of instruction
*/
void PrintStmt::compile(string instr) {
    vector<string> args = parseInstr(instr);
    string operand = args.at(0).find(":") == string::npos ? args.at(1) : args.at(2);

    string content;
    int indexVal;

    // check if operand contains string literal
    if (literalCheck(operand, content)) {
      setOperands(content);
    }
    else {
      // check if operand is provided as an array
      parseArray(operand, content, indexVal);
      cout << "VARIABLE NAME: " << content << endl;
      Variable* var = getPgm()->getVariable(content);
      setOperands(var);

      // set index attribute of operand to index of variable
      setOperandIndex(0, indexVal);
    }
}

/*
run
    purpose: execute instructions stored in current statement object
*/
void PrintStmt::run(){
    string output;

    if(getOperand(0).getLiteral() == "") {
        output = to_string(getPgm()->getVariable(getOperand(0).getIdentifier()->getName())->getValue(0));
    }
    else {
        output = getOperand(0).getLiteral();
    }
    printToTerminal(output);
}

int PrintStmt::getDest(){
    return -1;
}

void PrintStmt::setDest(int d){}

void PrintStmt::print() {
    cout << "Print Stmt" << endl;
    Statement::print();
}
