#include "JEqStmt.h"

using namespace std;

JEqStmt::JEqStmt(Program* pgm, Label* label, int numIds, int line) : Statement(pgm, label, numIds, line, "jeq"), prev(NULL), dest(-1), prevLineNum(-1) {}


JEqStmt::~JEqStmt() {}

/*
compile
    purpose: generate an object representation of an jeq statement instruction
    in:
      string: instr
*/
void JEqStmt::compile(string instr) {
  Program* pgm = getPgm();

  // split instruction into arguments
  vector<string> args = parseInstr(instr);

  // set operand index based on presence of identifying label
  int labelPos = args.at(0).find(":") == string::npos ? 1 : 2;
  string labelName = args.at(labelPos);
  Label* label;

  // check if label has already been created
  if (pgm->checkLabelMembership(labelName) == 1) {
    label = pgm->getLabel(labelName);
  }
  // create label if it does not exist
  else {
    label = new Label(labelName, pgm->getStmtSize());
    pgm->addLabel(label, labelName);
  }
  pgm->locateLabel(labelName, &dest);
  setOperands(label);

  // set prev cmp stmt
  prev = pgm->getLastCmpStmt();

  prevLineNum = pgm->getLastCmpLineNum();
}

/*
run
    purpose: execute instructions stored in current statement object
*/
void JEqStmt::run() {

    int result = prev->getResult();
    prev->print();

    if (result == 1) {
      getPgm()->setNextStmt(dest - 2);
    }
}

int JEqStmt::getDest(){
    return dest;
}

void JEqStmt::setDest(int d){
    dest = d;
}

void JEqStmt::setPrevCmp(CmpStmt* cmp){
    prev = cmp;
}

CmpStmt* JEqStmt::getPrevCmp(){
    return prev;
}

void JEqStmt::setPrevCmpLine(int lineNum){
    prevLineNum = lineNum;
}

int JEqStmt::getPrevCmpLine(){
    return prevLineNum;
}
