#include "JmpStmt.h"
#include "Program.h"

using namespace std;

JmpStmt::JmpStmt(Program* pgm, Label* label, int numIds, int line) : Statement(pgm, label, numIds, line, "jmp"),  prev(NULL), dest(-1) {}

JmpStmt::~JmpStmt() {}

/*
compile
    purpose: generate an object representation of an jmp statement instruction
    in:
      string: instr
*/
void JmpStmt::compile(string instr) {
  // split instruction into arguments
  vector<string> args = parseInstr(instr);

  // set operand index based on presence of identifying label
  int labelPos = args.at(0).find(":") == string::npos ? 1 : 2;
  string labelName = args.at(labelPos);
  Label* label;

  // check if label has already been created
  if (getPgm()->checkLabelMembership(labelName) == 1) {
    label = getPgm()->getLabel(labelName);
  }
  // create label if it does not exist
  else {
    label = new Label(labelName, getPgm()->getStmtSize());
    getPgm()->addLabel(label, labelName);
  }
  getPgm()->locateLabel(labelName, &dest);
  setOperands(label);
}

/*
run
    purpose: execute instructions stored in current statement object
*/
void JmpStmt::run() {
    getPgm()->setNextStmt(dest - 2);
}

void JmpStmt::print() {
    cout << "Jmp Stmt" << endl;
    Statement::print();
    if (dest != -1) {
      cout << "DEST: " << dest << endl;
    }
}

int JmpStmt::getDest(){
    return dest;
}

void JmpStmt::setDest(int d){
    dest = d;
}
