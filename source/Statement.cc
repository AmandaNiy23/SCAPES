#include "Statement.h"
#include "Program.h"


using namespace std;

Statement::Statement(Program* program, Label* stmtLabel, int numIds, int line, std::string type_name) : pgm(program), numOperands(numIds), label(stmtLabel), lineNumber(line) {
    type = type_name;
    connect(this, SIGNAL(printTerminal(std::string)), pgm, SLOT(printStmtResp(std::string)));
    connect(this, SIGNAL(getUserInputsignal(std::string)), pgm, SLOT(getUserInput(std::string)));
    connect(pgm, SIGNAL(sendUserInputResp(std::string)), this, SLOT(getUserInputResp(std::string)));
}

Statement::~Statement() {}

Program* Statement::getPgm() {
    return pgm;
}

Operand Statement::getOperand(int index) {
    return operands[index];
}

void Statement::setOperands(Identifier* id, int operandIndex) {
    operands[operandIndex].setIdentifier(id);
}

void Statement::setOperands(string literalValue, int operandIndex) {
    operands[operandIndex].setLiteral(literalValue);
}

void Statement::setOperandIndex(int index, int value) {
    operands[index].setIndex(value);
}

void Statement::setLabel(Label* labelName) {
    label = labelName;
}

Label* Statement::getLabel() {
    return label;
}

int Statement::getNumOperands() {
    return numOperands;
}

string Statement::getType() {
    return type;
}

bool Statement::hasLabel() {
    return label == nullptr ? false : true;
}

int Statement::getLineNumber() {
    return lineNumber;
}

void Statement::setLineNumber(int num) {
   lineNumber = num;
}


/*
parseInstr
    purpose:
      read in one line of instructions and separate line by spaces

    in:
      string: instr - single instruction in raw text format
    out:
      vector<string> - vector of strings containing decomposed instruction in sequential order
*/
vector<string> Statement::parseInstr(string instr) {
  vector<string> args;
  stringstream ss(instr);
  char delim = ' ';
  string arg;
  bool isStringLiteral = false;
  string strLiteral = "";

  while(getline(ss, arg, delim)) {
    cout<<"arg: "<<arg<<endl;
    cout<<"strLiteral: "<<strLiteral<<endl;
    // argument is a part of a string literal
    if (isStringLiteral) {
      strLiteral.append(" ");
      strLiteral.append(arg);
      continue;
    }

    // argument is the start of a string literal
    else if (arg.at(0) == '\"') {
      isStringLiteral = true;
      strLiteral.append(arg);
      continue;
    }

    args.push_back(arg);
  }

  // push string literal to vector
  if (strLiteral != "")
    args.push_back(strLiteral);

  return args;
}

/*
parseArray
    purpose:
      read in argument and extract variable name, index in array (0 if single value)

    in:
      string: arg - argument containing operand of interest

    out:
      string: varName - name of variable of interest (single value or array)
      int: arrIndex - index of array if arg contains array access
                      otherwise 0 for single values
*/
void Statement::parseArray(string arg, string& varName, int& arrIndex) {
    int arrSymbolPos = arg.find('$');
    arrIndex = 0;
    varName = arg;

    // argument contains access to array
    if (arrSymbolPos != string::npos) {
        // extract variable name and index of array
        varName = arg.substr(arrSymbolPos + 1, arg.find('+') - (arrSymbolPos + 1));
        string indexOffset = arg.substr(arg.find('+') + 1);

        // index given as literal numeric value
        try {
          arrIndex = stoi(indexOffset);
        }
        //index given as another variable
        catch(...) {
          arrIndex = getPgm()->getVariable(indexOffset)->getValue();
        }
    }
}


/*
literalCheck
    purpose:
      read in argument to check if argument contains string literals
      and extract literal content

    in:
      string: arg - argument containing operand of interest

    out:
      string: literal - contents of string literal with quotation marks removed
      bool: true if argument contains string literal, false otherwise
*/
bool Statement::literalCheck(string arg, string& literal) {
    int quotePos = arg.find('\"');
    literal = "";

    // argument contains string literal
    if (quotePos != string::npos) {
        literal = arg.substr(quotePos + 1, arg.length() - 2);
        return true;
    }
    return false;
}

void Statement::initOperands(string operand,int index) {
  Variable* var;
  string content;
  int indexVal;

  // check if first operand contains numeric literal
  try {
    int literal = stoi(operand);
    setOperands(operand, index);
  }
  // check if first operand contains an array or a variable
  catch(...) {
    parseArray(operand, content, indexVal);
    var = getPgm()->getVariable(content);
    setOperands(var, index);
    setOperandIndex(index, indexVal);
  }
}

//int Statement::getDest(){}

//void Statement::setDest(int d){}

void Statement::initNumericOperands(string operand, int index) {
  Variable* var;
  string content;
  int indexVal;

  parseArray(operand, content, indexVal);
  var = getPgm()->getVariable(content);
  setOperands(var, index);
  setOperandIndex(index, indexVal);
}

void Statement::printToTerminal(std::string text){
    printTerminal(text);
}

void Statement::getUserInput(std::string text){
    getUserInputsignal(text);
}
//TODO: remove after testing, before submission
void Statement::print() {
    cout << "OPERANDS: " << endl;
    for (int i=0; i<numOperands; i++) {
      if (operands[i].getIdentifier() != NULL) {
        operands[i].getIdentifier()->print();
      }
      cout << "Operand index: " << operands[i].getIndex() << endl;
      cout << "Operand literal: " << operands[i].getLiteral() << endl;

    }
    if (label != NULL) {
      cout << "Label: " << endl;
      label->print();
    }
}

void Statement::getUserInputResp(std::string userinput){
    //stripping any leading and trailing whitespace

    userinputval =std::regex_replace(userinput, std::regex("^ +| +$|( ) +"), "$1");
    inputReceived();
}

std::string Statement::getUserInputValue(){
    return userinputval;

}
