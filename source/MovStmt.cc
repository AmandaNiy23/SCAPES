#include "MovStmt.h"

using namespace std;

MovStmt::MovStmt(Program* pgm, Label* label, int numIds, int line) : Statement(pgm, label, numIds, line, "mov") {}

MovStmt::~MovStmt() {}

/*
compile
    purpose: generate an object representation of an mov statement instruction
    in:
      string: instr
*/
void MovStmt::compile(string instr) {
    // split instruction into arguments
    vector<string> args = parseInstr(instr);

    // set operand index based on presence of label
    int opIndex = args.at(0).find(":") == string::npos ? 1 : 2;
    string opOne = args.at(opIndex);
    string opTwo = args.at(opIndex + 1);

    initOperands(opOne, 0);
    initNumericOperands(opTwo, 1);
  }

  /*
  run
      purpose: execute instructions stored in current statement object
  */
void MovStmt::run() {
  int value;
  int index1;

  Identifier* id2 = getOperand(1).getIdentifier();
  Variable* var2 = getPgm()->getVariable(id2->getName());

  // get value of 1st operand
  // 1st operand is a literal
  try {
    value = stoi(getOperand(0).getLiteral());
  }

  // 1st operand is a variable or array
  catch(...) {
    Identifier* id1 = getOperand(0).getIdentifier();
    Variable* var1 = getPgm()->getVariable(id1->getName());
    index1 = getOperand(0).getIndex();
    value = var1->getValue(index1);
  }
  // set variable 2's value to new value
  var2->setValue(value, getOperand(1).getIndex());
}

int MovStmt::getDest(){
    return -1;
}

void MovStmt::setDest(int d){}

  void MovStmt::print() {
      cout << "Mov Stmt" << endl;
      Statement::print();
  }
