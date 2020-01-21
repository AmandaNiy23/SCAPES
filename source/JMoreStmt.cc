#include "JMoreStmt.h"

using namespace std;

JMoreStmt::JMoreStmt(Program* pgm, Label* label, int numIds, int line) : Statement(pgm, label, numIds, line, "jmr"),  prev(NULL), dest(-1), prevLineNum(-1) {}

JMoreStmt::~JMoreStmt() {}

/*
compile
    purpose: generate an object representation of an jmr statement instruction
    in:
      string: instr
*/
void JMoreStmt::compile(string instr) {
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
void JMoreStmt::run() {
  int result = prev->getResult();

  if (result == 0) {
    getPgm()->setNextStmt(dest - 2);
  }
}

void JMoreStmt::print() {
    cout << "JMore Stmt" << endl;
    Statement::print();
    if (dest != -1) {
      cout << "DEST: " << dest << endl;
    }
}

int JMoreStmt::getDest(){
    return dest;
}

void JMoreStmt::setDest(int d){
    dest = d;
}

void JMoreStmt::setPrevCmp(CmpStmt* cmp){
    prev = cmp;
}

CmpStmt* JMoreStmt::getPrevCmp(){
    return prev;
}

void JMoreStmt::setPrevCmpLine(int lineNum){
    prevLineNum = lineNum;
}

int JMoreStmt::getPrevCmpLine(){
    return prevLineNum;
}
