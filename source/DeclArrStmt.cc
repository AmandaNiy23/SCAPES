#include "DeclArrStmt.h"

using namespace std;

DeclArrStmt::DeclArrStmt(Program* pgm, Label* label, int numIds, int line) : Statement(pgm, label, numIds, line, "dca") {}

DeclArrStmt::~DeclArrStmt() {}

/*
compile
    purpose: generate an object representation of an dca statement instruction
    in:
      string: instr
*/
void DeclArrStmt::compile(string instr) {
    string content;
    int indexVal;

    // split statement into arguments
    vector<string> args = parseInstr(instr);

    //set operand index based on presence of label
    int opIndex = args.at(0).find(":") == string::npos ? 1 : 2;
    Variable* var;

    string opOne = args.at(opIndex);
    string opTwo = args.at(opIndex + 1);

    // check if second operand contains numeric literal
    try {
      // create array with size of numeric literal
      var = new Variable(opOne, stoi(opTwo));
      setOperands(opTwo, 1);
    }
    // check if second operand contains variables / array
    catch(...) {
      parseArray(opTwo, content, indexVal);

      // create array with size 0
      var = new Variable(opOne, 0);

      // get opTwo value from variables map
      Variable* sizeVar = getPgm()->getVariable(opTwo);

      // set sizeVar to 2nd position in operands array
      setOperands(sizeVar, 1);

      // set index value for Operand if it is an array or 0 for variable
      setOperandIndex(1, indexVal);
    }

    // create a new array variable with opOne's name
    getPgm()->addVariable(var, opOne);

    // set new array variable name to 1st position in operand array
    setOperands(var);
}

/*
run
    purpose: execute instructions stored in current statement object
*/
void DeclArrStmt::run() {
  int arrSize;
  ostringstream  error;

  Identifier* id1 = getOperand(0).getIdentifier();
  Variable* var1 = getPgm()->getVariable(id1->getName());

  // try to get literal value from operand
  try {
    arrSize = stoi(getOperand(1).getLiteral());
  }

  // get value from variable or array
  catch(...) {
    Identifier* id2 = getOperand(1).getIdentifier();
    Variable* var2 = getPgm()->getVariable(id2->getName());
    arrSize = var2->getValue(getOperand(1).getIndex());
  }
  var1->reallocateArrSize(arrSize);
}

void DeclArrStmt::print() {
    cout << "DeclArr Stmt" << endl;
    Statement::print();
}

int DeclArrStmt::getDest(){
    return -1;
}

void DeclArrStmt::setDest(int d){}
