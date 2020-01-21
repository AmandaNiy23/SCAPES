#include "JLessStmt.h"

using namespace std;

JLessStmt::JLessStmt(Program* pgm, Label* label, int numIds, int line) : Statement(pgm, label, numIds, line, "jls"),  prev(NULL), dest(-1), prevLineNum(-1) {}

JLessStmt::~JLessStmt() {}

/*
compile
    purpose: generate an object representation of an jls statement instruction
    in:
      string: instr
*/
void JLessStmt::compile(string instr) {
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
void JLessStmt::run() {
  int result = prev->getResult();

  if (result == 2) {
    getPgm()->setNextStmt(dest - 2);
  }
}

int JLessStmt::getDest(){
    return dest;
}

void JLessStmt::setDest(int d){
    dest = d;
}

void JLessStmt::setPrevCmp(CmpStmt* cmp){
    prev = cmp;
}

CmpStmt* JLessStmt::getPrevCmp(){
    return prev;
}

void JLessStmt::setPrevCmpLine(int lineNum){
    prevLineNum = lineNum;
}

int JLessStmt::getPrevCmpLine(){
    return prevLineNum;
}
