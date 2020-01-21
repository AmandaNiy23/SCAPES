#include "CmpStmt.h"

using namespace std;

CmpStmt::CmpStmt(Program* pgm, Label* label, int numIds, int line) : Statement(pgm, label, numIds, line, "cmp") {}

CmpStmt::~CmpStmt() {}

int CmpStmt::getResult() {
  return result;
}

/*
compile
    purpose: generate an object representation of an cmp statement instruction
    in:
      string: instr
*/
void CmpStmt::compile(string instr) {
  // split instruction into arguments
  vector<string> args = parseInstr(instr);

  // set operand index based on presence of label
  int opIndex = args.at(0).find(":") == string::npos ? 1 : 2;

  string opOne = args.at(opIndex);
  string opTwo = args.at(opIndex + 1);
  cout<<"compile -- op2: "<<opTwo<<endl;

  // set operands in current object
  initOperands(opOne, 0);
  initOperands(opTwo, 1);
}

/*
run
    purpose: execute instructions stored in current statement object
*/
void CmpStmt::run() {
  int n1;
  int n2;
  int index1;
  int index2;

  // get 1st operand's value
  // 1st operand is a literal
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
  // 2nd operand is a literal
  try {
    n2 = stoi(getOperand(1).getLiteral());
  }
  // operand is a variable or array
  catch(...) {
    Identifier* id2 = getOperand(1).getIdentifier();
    Variable* var2 = getPgm()->getVariable(id2->getName());
    index2 = getOperand(1).getIndex();
    n2 = var2->getValue(index2);
  }

  // compare n1 and n2
  if (n1 > n2)
    result = 0;
  else if (n1 == n2)
    result = 1;
  else
    result = 2;
}

int CmpStmt::getDest(){
    return -1;
}

void CmpStmt::setDest(int d){}

void CmpStmt::print() {
    cout << "Cmp Stmt" << endl;
    Statement::print();
}
