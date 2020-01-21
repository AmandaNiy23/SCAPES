#include "AddStmt.h"

using namespace std;

AddStmt::AddStmt(Program* pgm, Label* label, int numIds, int line) : Statement(pgm, label, numIds, line, "add") {}

AddStmt::~AddStmt() {}
/*
compile
    purpose: generate an object representation of an add statement instruction
    in:
      string: instr
*/
void AddStmt::compile(string instr) {
  // split statement into arguments
  vector<string> args = parseInstr(instr);

  //set operand index based on presence of label
  int opIndex = args.at(0).find(":") == string::npos ? 1 : 2;

  string opOne = args.at(opIndex);
  string opTwo = args.at(opIndex + 1);

  // set operands in current object
  initOperands(opOne, 0);
  initNumericOperands(opTwo, 1);
}

/*
run
    purpose: execute instructions stored in current statement object
*/
void AddStmt::run() {
  int n1;
  int n2;
  int index1;
  int index2;
  int result;

  Identifier* id2 = getOperand(1).getIdentifier();
  Variable* var2 = getPgm()->getVariable(id2->getName());

  // get 1st operand's value
  // operand is a literal
  try {
    n1 = stoi(getOperand(0).getLiteral());
  }

  // operand is a variable or array
  catch(...) {
    Identifier* id1 = getOperand(0).getIdentifier();
    Variable* var1 = getPgm()->getVariable(id1->getName());
    index1 = getOperand(0).getIndex();

    n1 = var1->getValue(index1);
  }
  // get 2nd operand's value
  index2 = getOperand(1).getIndex();
  n2 = var2->getValue(index2);

  // add values
  result = n1 + n2;

  // set variable 2's value to new value
  var2->setValue(result, index2);
}

int AddStmt::getDest(){
    return -1;
}

void AddStmt::setDest(int d){}

void AddStmt::print() {
    cout << "Add Stmt" << endl;
    Statement::print();
}
