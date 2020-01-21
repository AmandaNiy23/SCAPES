#include "ReadStmt.h"
#include "Variable.h"
#include <vector>
#include <iostream>

using namespace std;

ReadStmt::ReadStmt(Program* pgm, Label* label, int numIds, int line) : Statement(pgm, label, numIds, line, "rdi") {


}

ReadStmt::~ReadStmt() {}

/*
compile
  purpose:
      read in a single instruction and translate contents into ReadStmt

    in:
      string: instr - single line of instruction
*/
void ReadStmt::compile(string instr) {
    vector<string> args = parseInstr(instr);
    string operand = args.at(0).find(":") == string::npos ? args.at(1) : args.at(2);
    string varName;
    int indexVal;

    // check if operand is provided as an array
    parseArray(operand, varName, indexVal);
    Variable* var = getPgm()->getVariable(varName);
    setOperands(var);

    // set index attribute of operand to index of variable
    setOperandIndex(0, indexVal);
}

/*
run
    purpose: execute instructions stored in current statement object
*/
void ReadStmt::run(){
    Program* pgm;

    string name = getOperand(0).getIdentifier()->getName();
    string mssg;
    if(getNumOperands() == 1){
        mssg = "Please enter a value for the variable " + name +":";
    }else{
        mssg = "Please enter a value for the array " + name + " at index " + to_string(getOperand(0).getIndex()) +  ": ";
    }
    getUserInput(mssg);
    std::string userinput = getUserInputValue();

    try {
      cout << "jERE" << endl;
      if(std::all_of(userinput.begin(), userinput.end(), ::isdigit)){
              int val = stoi(userinput);
              getPgm()->getVariable(name)->setValue(val);
      }
    }
    catch(...) {
      printToTerminal("ERROR: invalid input");

      pgm = getPgm();
      pgm->setNextStmt(pgm->getStmtSize());
    }
}

int ReadStmt::getDest(){
    return -1;
}

void ReadStmt::setDest(int d){}


void ReadStmt::print() {
    cout << "Read Stmt" << endl;
    Statement::print();
}
