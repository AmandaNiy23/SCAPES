#include "Program.h"
#include <QTextStream>
#include <runcontrol.h>

Program::Program(string source) : lastCmpInstr(-1) {
    stringstream ss(source);

    // add all instructions to instructions map
    addInstructions(instructions);

    // trim leading and trailing spaces of each instruction and add to vector rawText
    while (getline(ss, source, '\n')) {
      if (source != "" && source.find_first_not_of(' ') != string::npos) {
        trim(source);
        rawText.push_back(source);
        cout << "Rawtext: " << source << endl;
      }
      else {
        rawText.push_back("");
      }
    }
}

Program::Program(string name, string dir, RunControl* const run){
    fileName = name;
    directory = dir;
    runPgmControl = run;
    connect(this, SIGNAL(printTerminal(std::string)), runPgmControl, SLOT(printStmtResp(std::string)));
    connect(this, SIGNAL(getUserInputsignal(std::string)), runPgmControl, SLOT(getUserInput(std::string)));
    connect(runPgmControl, SIGNAL(sendUserInputResp(std::string)), this, SLOT(getUserInputResp(std::string)));

}

Program::~Program() {
    map<string, Variable*>::iterator varIt;
    map<string, Label*>::iterator labelIt;

    // delete Variable objects
    for (varIt = variables.begin(); varIt != variables.end(); varIt++) {
      delete varIt->second;
    }
    // delete Label objects
    for (labelIt = labels.begin(); labelIt != labels.end(); labelIt++) {
      delete labelIt->second;
    }
    // delete Statement objects
    for (int i = 0; i < statements.size(); i++) {
      delete statements.at(i);
  }
}

/*
  checkSyntax
  Purpose: ensure correct syntax and logic is used for a line from the SCAPES program, throw an error otherwise
  in:
    string: line        - line being evaluated
    int:    index       - line number associated with line being evaluated
  inout:
    bool:   isLabelSpec - if a line contains a label specification (ex: L1: ...)
*/
void Program::checkSyntax(string& line, int index, bool& isLabelSpec) {
  stringstream   ss(line);
  string         arg;
  char           delim = ' ';
  vector<string> args;
  bool           isStringLiteral = false;
  string         strLiteral = "";
  int            numArgs;
  ostringstream  error;
  bool           isLabel = false;
  int            numOperands;
  string         instruction;
  vector<string> operands;
  string         varName;
  bool           isArray = false;
  int            pos;
  set<string>    nonArrayInstrs;
  set<string>    declarationInstrs;
  set<string>    literalInstrs;
  set<string>    condJumpInstrs;
  int            labelCount = 0;
  string         label = "";
  bool           validLiteral = false;

  // parse line
  while(getline(ss, arg, delim)) {

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

  // number of arguments in line
  numArgs = args.size();

  // if first argument is not a valid instruction
  if (instructions.find(args.at(0)) == instructions.end()) {

    // if not valid label syntax
    if (!regex_match(args.at(0), regex("\\b(L\\d*:)\\B"))) {
      error << "ERROR, line "<< index << ": Invalid instruction or label, " << args.at(0) << endl;
      throw SyntaxException(error.str());
    }

    // valid label
    isLabel = true;
    isLabelSpec = true;
  }

  // initialize instruction
  if (isLabel)
    instruction = args.at(1);
  else
    instruction = args.at(0);

  // verify valid instruction
  if (isLabel) {
    if (instructions.find(instruction) == instructions.end()) {
      error << "ERROR, line "<< index << ": Invalid instruction, " << instruction << endl;
      throw SyntaxException(error.str());
    }
  }

  // check if number of operands matches corresponding instruction's required number of operands
  numOperands = instructions[instruction];
  if (isLabel) {
    if (numArgs-2 != numOperands) {
      error << "ERROR, line "<< index << ": Invalid number of operands. Number of operands should be " << numOperands << " for " << instruction << endl;
      throw SyntaxException(error.str());
    }
  }
  else {
    if (numArgs-1 != numOperands) {
      error << "ERROR, line "<< index << ": Invalid number of operands. Number of operands should be " << numOperands << " for " << instruction << endl;
      throw SyntaxException(error.str());
    }
  }

  // initialize operands
  operands.push_back("");
  operands.push_back("");
  if (isLabel) {
    if (numArgs >= 3)
      operands[0] = args.at(2);
    if (numArgs >= 4)
      operands[1] = args.at(3);
  }
  else {
    if (numArgs >= 2)
      operands[0] = args.at(1);
    if (numArgs >= 3)
      operands[1] = args.at(2);
  }

  // add all non-array instructions to set
  nonArrayInstrs.insert("dci");
  nonArrayInstrs.insert("dca");
  nonArrayInstrs.insert("jls");
  nonArrayInstrs.insert("jmr");
  nonArrayInstrs.insert("jeq");
  nonArrayInstrs.insert("jmp");

  // add all declaration instructions to set
  declarationInstrs.insert("dci");
  declarationInstrs.insert("dca");

  // add all instructions that accept literals
  literalInstrs.insert("prt");
  literalInstrs.insert("mov");
  literalInstrs.insert("add");
  literalInstrs.insert("cmp");

  // add all conditional jump instructions
  condJumpInstrs.insert("jls");
  condJumpInstrs.insert("jmr");
  condJumpInstrs.insert("jeq");

  for (int i = 0; i < operands.size(); ++i) {
    if (operands.at(i) == "")
      continue;

    // check if operand is an array
    if (operands.at(i).at(0) == '$') {
      isArray = true;

      // validate array syntax
      if (!regex_match(operands.at(i), regex("(\\$).*(\\+).*(\\d|\\w)"))) { //(\\$).*(\\+).*\\d
        error << "ERROR, line "<< index << ": Invalid array syntax for operand: " << operands.at(i) << endl;
        throw SyntaxException(error.str());
      }

      // parse variable name
      pos = operands.at(i).find("+");
      varName = operands.at(i).substr(1, pos-1);
    }
    else
      varName = operands.at(i);

    // check if instruction shouldn't take an array as an argument
    if (nonArrayInstrs.find(instruction) != nonArrayInstrs.end()) {
      if (isArray) {
        error << "ERROR, line "<< index << ": Instruction, " << instruction << ", does not take an array as an argument." << endl;
        throw SyntaxException(error.str());
      }
    }

    // if instruction is not in declarationInstrs set
    if (declarationInstrs.find(instruction) == declarationInstrs.end()) {

      // if variable is not in variables map
      if (variables.find(varName) == variables.end()) {

        // if instruction is in literalInstrs set
        if (literalInstrs.find(instruction) != literalInstrs.end()) {

          if (instruction == "prt") {

            // check if improper string literal
            if (!regex_match(operands.at(i), regex("\\B(\"\\w.*\")\\B"))) {

              // if improper int literal format
              if (!regex_match(operands.at(i), regex("\\b([1-9]\\d*|0|0[oO][0-7]+|0[xX][\\da-fA-F]+|0[bB][01]+)\\b"))) {
                error << "ERROR, line " << index << ": Undeclared variable, or invalid string literal syntax, or invalid int literal syntax for, " << operands.at(i) << endl;
                throw SyntaxException(error.str());
              }

              // valid int literal
              else
                validLiteral = true;

              // if not valid int literal
              if (!validLiteral) {
                error << "ERROR, line " << index << ": Undeclared variable or invalid string syntax, " << operands.at(i) << endl;
                throw SyntaxException(error.str());
              }
            }
            continue;
          }

          else if (instruction == "cmp") {

            // if improper int literal format
            if (!regex_match(operands.at(i), regex("\\b([1-9]\\d*|0|0[oO][0-7]+|0[xX][\\da-fA-F]+|0[bB][01]+)\\b"))) {
              error << "ERROR, line " << index << ": Undeclared variable or invalid int literal syntax for, " << operands.at(i) << endl;
              throw SyntaxException(error.str());
            }
            continue;
          }

          // instruction is not prt
          else {

            // if first operand
            if (i==0) {

              // if improper int literal format
              if (!regex_match(operands.at(i), regex("\\b([1-9]\\d*|0|0[oO][0-7]+|0[xX][\\da-fA-F]+|0[bB][01]+)\\b"))) {
                error << "ERROR, line " << index << ": Undeclared variable or invalid int literal syntax for, " << operands.at(i) << endl;
                throw SyntaxException(error.str());
              }
              continue;
            }
          }
        }
        // if instruction is a conditional jump
        if (condJumpInstrs.find(instruction) != condJumpInstrs.end()) {

          // if no cmp statement has occured before this conditional jump
          if ((lastCmpInstr == -1) || (index < lastCmpInstr) ) {
            error << "ERROR, line " << index << ": Invalid conditional jump, " << instruction << endl << "Conditional jumps must come after a cmp instruction" << endl;
            throw SyntaxException(error.str());
          }
        }

        // count number of label specifications before current line
        for (int j = 0; j < index-1; ++j) {
          if (labelCount > 1) {
            error << "ERROR, line " << index << ": Invalid count of label specification" << endl << "Example of proper syntax, L1: prt a, where the label specification can only occur once" << endl;
            throw SyntaxException(error.str());
          }

          // get label without ':'
          label = "";
          if (!rawText.empty())
            extractLabel(rawText.at(j), label);

          // if line contains a valid label specification and the label specification is the label being looked for
          if (!rawText.empty()) {
            if ((regex_match(rawText.at(j), regex("\\b(L.*:).*"))) && (varName == label))
              ++labelCount;
          }
        }

        // count number of label specifications after current line
        for (int j = index; j < rawText.size(); ++j) {
          if (labelCount > 1) {
            error << "ERROR, line " << index << ": Invalid count of label specification" << endl << "Example of proper syntax, L1: prt a, where the label specification can only occur once" << endl;
            throw SyntaxException(error.str());
          }

          // get label without ':'
          label = "";
          if (!rawText.empty())
            extractLabel(rawText.at(j), label);

          // if line contains a valid label specification and the label specification is the label being looked for
          if (!rawText.empty()) {
            if ((regex_match(rawText.at(j), regex("\\b(L.*:).*"))) && (varName == label))
              ++labelCount;
          }
        }

        // incorrect number of jump specifications
        if (labelCount != 1) {
            error << "ERROR, line " << index << ": Variable not declared or unknown label, " << varName << endl;
            throw SyntaxException(error.str());
        }
      }
    }

    // instruction is in declarationInstrs set
    else {

      // validate that variable being declared is alphanumeric
      if (!regex_match(varName, regex("^[a-zA-Z0-9_]*$"))) {
        error << "ERROR, line "<< index << ": Variable declaration must be alphanumeric" << endl;
        throw SyntaxException(error.str());
      }
    }

    isArray = false;
    labelCount = 0;
    validLiteral = false;
  }

  // if instruction is cmp, set lastCmpInstr to current index
    if (instruction == "cmp")
      lastCmpInstr = statements.size();
}
/*
compile
    purpose: translate all statements from raw text to statement objects
             and corresponding operands contatining appropriate identifiers
*/
void Program::compile() {
    bool hasLabel;
    Factory fac;

    // iterate through each line of raw text
    for (int i = 0; i < rawText.size(); i++) {
      hasLabel = false;
      int index = i+1;
      string rawLine = rawText.at(i);

      // terminate current iteration if comment
      if (regex_match(rawLine, regex(".*(#).*")) || rawLine == "") {
        continue;
      }
      // verify syntax of statement
      try{
        checkSyntax(rawLine, index, hasLabel);
      }
      catch(SyntaxException& e) {
        cout << *e.explain();
        throw *e.explain();
      }

      vector<string> line;
      splitInstr(rawLine, line);
      Statement* stmt;
      Label* label = NULL;

      // statement contains associated label
      if (hasLabel) {
        string labelName = line.at(0).substr(0, line.at(0).find(":"));

        // first time encounter with label, label has not been created before
        if (labels.find(labelName) == labels.end()) {
          label = new Label(labelName, statements.size());
          labels.insert(map<string, Label*>::value_type(labelName, label));
        }
        // label already created
        else {
          label = getLabel(labelName);
        }
        line.erase(line.begin());
      }

      // compile each statement and store in vector in sequential order
      stmt = fac.createStmt(line.at(0), this, label, index);
      stmt->compile(rawLine);
      statements.push_back(stmt);
    }
    print();
}

/*
run
    purpose: execute all instructions stored in current statement vector in correct order
*/
void Program::run() {
    nextStmt = 0;

    while (nextStmt < statements.size()) {
      statements.at(nextStmt)->run();
      nextStmt += 1;
    }
}

/*
checkLabelMembership
    purpose: check whether label with string name has already been created
    in:
      string: name - name of label
*/
int Program::checkLabelMembership(string name) {
    return labels.count(name);
}

/*
locateLabel
    purpose: locate line number of statement associated with labelName
    in:
      string: labelName - name of label
    out:
      int: dest - line number of statement associated with label
*/
void Program::locateLabel(string labelName, int* dest) { //TODO: JIM CHANGED (whole function)
    int line = 0;

    // iterate through rawText file until label of interest is found
    for (int i = 0; i < rawText.size(); i++) {
        if (rawText.at(i) != "" && rawText.at(i).at(0) != '#') {
          line +=1;
        }
        if (rawText.at(i).substr(0, rawText.at(i).find(":")) == labelName) {
          *dest = line;
          return;
        }
    }
}

int Program::getLastCmpLineNum(){
    return lastCmpInstr;
}

CmpStmt* Program::getLastCmpStmt() {
    return dynamic_cast<CmpStmt*>(statements.at(lastCmpInstr));
}
CmpStmt* Program::getCmpStmt(int lineNum) {
    return dynamic_cast<CmpStmt*>(statements.at(lineNum));
}

Statement* Program::getLastStmt() {
    return statements.back();
}

Variable* Program::getVariable(string name) {
    return variables.find(name)->second;
}

Label* Program::getLabel(string name) {
    map<string, Label*>::iterator it = labels.find(name);
    return it->second;
}

void Program::addVariable(Variable* var, string name) {
    variables.insert(map<string, Variable*>::value_type(name, var));
}

void Program::addLabel(Label* label, string name) {
    labels.insert(map<string, Label*>::value_type(name, label));
}

void Program::setFileName(string name) {
    fileName = name;
}

// add all instructions to instructions map (instruction name, number of operands)
void Program::addInstructions(map<string, int>& instrs) {
  instrs.insert(pair<string, int>("dci", 1));
  instrs.insert(pair<string, int>("dca", 2));
  instrs.insert(pair<string, int>("rdi", 1));
  instrs.insert(pair<string, int>("prt", 1));
  instrs.insert(pair<string, int>("mov", 2));
  instrs.insert(pair<string, int>("add", 2));
  instrs.insert(pair<string, int>("cmp", 2));
  instrs.insert(pair<string, int>("jls", 1));
  instrs.insert(pair<string, int>("jmr", 1));
  instrs.insert(pair<string, int>("jeq", 1));
  instrs.insert(pair<string, int>("jmp", 1));
  instrs.insert(pair<string, int>("end", 0));
}

// get label without ':'
void Program::extractLabel(string& rawText, string& label) {
  for (int i = 0; i <rawText.length(); ++i) {
    if (rawText.at(i) == ':')
      break;
    label += rawText.at(i);
  }
}

/*
trim
    purpose: trim all extra spaces in a raw statement
    in:
      string: instr
    out:
      string: instr
*/
void Program::trim(string& instr, char delim) { //TODO: JIM CHANGED (whole function)
  int first = instr.find_first_not_of(delim);
  int last = instr.find_last_not_of(delim);

  // trim all leading and trailing spaces
  instr = instr.substr(first, (last-first+1));
  stringstream ss(instr);
  string parsedInstr = "";

  // remove all extra spaces between arguments
  while (getline(ss, instr, ' ')) {
    if (instr.find_first_not_of(' ') != string::npos) {
      // account for extra space between label name and colon
      if (instr == ":") {
        parsedInstr = parsedInstr.substr(0, parsedInstr.length() - 1) + ": ";
      }
      else if (instr.find(":") != string::npos) {
        parsedInstr.append(instr.substr(0, instr.find(":") + 1));

        if (instr.at(instr.length() - 1) != ':') {
          parsedInstr.append(" " + instr.substr(instr.find(":") + 1));
        }
      }
      else {
        parsedInstr.append(" " + instr);
      }
    }
  }
  first = parsedInstr.find_first_not_of(delim);
  last = parsedInstr.find_last_not_of(delim);

  // trim all leading and trailing spaces
  instr = parsedInstr.substr(first, (last-first+1));
}

/*
splitInstr
    purpose: split a line of statement into instructions and operands
    in:
      string: rawLine - statement in raw text format
    out:
      vector<string>: line - vector containin instruction, and operands
*/
void Program::splitInstr(string rawLine, vector<string>& line) {
    stringstream ss(rawLine);
    istream_iterator<string> begin(ss);
    istream_iterator<string> end;

    vector<string> vec(begin, end);
    line = vec;
}

void Program::setNextStmt(int dest) {
    nextStmt = dest;
}

void Program::deserialize(){
    ostringstream  error;

    if(directory.back() != '/'){
        directory += '/';
    }


    QFile file_obj(QString::fromStdString(directory+fileName+".json"));
    if (!file_obj.open(QIODevice::ReadOnly)) {
        error  << "Failed to open " << directory  <<fileName << ".json" << std::endl;
        throw SyntaxException(error.str());
    }else{
        cout << "************ " << fileName << " " << directory << " ************" << endl;
    }


    //read contents of file & convert it to a json object
    QTextStream file_text(&file_obj);
    QString json_string;
    json_string = file_text.readAll();
    file_obj.close();
    QByteArray json_bytes = json_string.toLocal8Bit();

    // Error Checking
    auto json_doc = QJsonDocument::fromJson(json_bytes);
    if (json_doc.isNull()) {
        exit(1);
    }

    QJsonObject json_obj = json_doc.object();
    QVariantMap test = json_obj.toVariantMap();
    QJsonObject::iterator it;

    //Iterate through the jSon object to retrieve the Labels, statements, and variables
    for(it=json_obj.begin();it!=json_obj.end();it++){

        if(it.key() == "Labels"){
            deserializeLabels(it.value().toArray());

        }else if(it.key() == "Statements"){
            deserializeStatements(it.value().toArray());
        }else if(it.key() == "Variables"){
            deserializeVariables(it.value().toArray());
        }

    }
    print();

}

void Program::deserializeLabels(QJsonArray labelsArray){

    QJsonObject labelObj;
    for (int i = 0; i<labelsArray.size();i++) {
        Label *label= nullptr;
        labelObj = labelsArray.at(i).toObject();

        QString labelName = labelObj.begin().value().toString();

        label = new Label(labelName.toUtf8().constData(), statements.size());
        labels.insert(map<string, Label*>::value_type(labelName.toUtf8().constData(), label));

    }
}

void Program::deserializeVariables(QJsonArray variablesArray){

    QJsonObject variableObj;
    //QJsonObject operandObj;
    for (int i = 0; i<variablesArray.size();i++) {
        variableObj = variablesArray.at(i).toObject();

        QJsonArray valuesArray;
        string varName;
        int numValues = -1;
        QJsonObject::iterator it;
        //Iterate through the jSon object to retrieve the Labels, statements, and variables
        for(it=variableObj.begin();it!=variableObj.end();it++){

            if(it.key() == "Name"){
                varName = it.value().toString().toUtf8().constData();
            }else if(it.key() =="Value(s)"){
                valuesArray = it.value().toArray();
            }else if(it.key() == "numValues"){
                numValues = std::stoi(it.value().toString().toUtf8().constData());
            }
        }
        Variable* variable = new Variable(varName, numValues);
        for(int index = 0; index<numValues; index++){
            variable->setValue(std::stoi(valuesArray[index].toString().toUtf8().constData()), index);

        }

        variables.insert(map<string, Variable*>::value_type(varName, variable));


    }


}

void Program::deserializeStatements(QJsonArray statementsArray){
    Factory fac;
    Statement* stmt;


    QJsonObject stmtObj;
    QJsonObject operandObj;
    for (int i = 0; i<statementsArray.size();i++) {
        stmtObj = statementsArray.at(i).toObject();

        QJsonArray operandArray;
        string statementType;
        Label* label =nullptr;
        int numOperands=-1;
        int dest = -1;
        int cmpLineNumber = -1;
        int lineNumber = -1;

        QJsonObject::iterator it;
        //Iterate through the jSon object to retrieve the Labels, statements, and variables
        for(it=stmtObj.begin();it!=stmtObj.end();it++){
            if(it.key() == "Operands"){
                operandArray = it.value().toArray();
            }else if(it.key() == "Statement Type"){
                statementType = it.value().toString().toUtf8().constData();
            }else if(it.key() == "Line Number"){
                lineNumber = std::stoi(it.value().toString().toUtf8().constData());
            }else if(it.key() == "label" and it.value().toString() != "null" ){
                label = new Label(it.value().toString().toUtf8().constData(), statementsArray.size());
            }else if(it.key() == "numOperands"){
                numOperands = std::stoi(it.value().toString().toUtf8().constData());
            }else if(it.key() == "Dest"){
                dest = std::stoi(it.value().toString().toUtf8().constData());
            }else if(it.key() == "Prev Cmp line number"){
                cmpLineNumber = std::stoi(it.value().toString().toUtf8().constData());
            }

        }

        stmt = fac.createStmt(statementType, this, label, -1);
        stmt->setLineNumber(lineNumber);
        if(dest>-1){
            stmt->setDest(dest);
        }
        if(statementType == "jeq" or statementType == "jls" or statementType == "jmr"){
            stmt->setPrevCmp(getCmpStmt(cmpLineNumber));
        }

        for (int i = 0; i<numOperands;i++) {

            string operand;
            int index = -1;
            string literal = "";

            operandObj = operandArray.at(i).toObject();

            for(it=operandObj.begin();it!=operandObj.end();it++){
                if(it.key() == "Operand"){
                    operand = it.value().toString().toUtf8().constData();
                }else if(it.key() == "index"){
                    index = std::stoi(it.value().toString().toUtf8().constData());
                }else if(it.key() == "literal"){
                    literal = it.value().toString().toUtf8().constData();
                }
            }

            if(literal == ""){
                Identifier* id = new Identifier(operand);
                stmt->setOperands(id, i);
            }else{
                stmt->setOperands(literal, i);
            }
        }
        statements.push_back(stmt);
    }
}

void Program::serialize(string name, string directory){

    QJsonObject jsonProgram;
    //jsonProgram["filename"] = QString::fromStdString(this->fileName);
    jsonProgram["filename"] = QString::fromStdString(name);
    QJsonArray jStatementsArray;
    for(Statement* st :statements)
    {
        QJsonObject jsonStatement;
        jsonStatement["Statement Type"] = QString::fromStdString(st->getType());
        jsonStatement["Line Number"] = QString::fromStdString(std::to_string(st->getLineNumber()));

        //if statement type is a jump, we need to add the return dest
        if(QString::fromStdString(st->getType()) == "jeq" or QString::fromStdString(st->getType()) == "jls" or QString::fromStdString(st->getType()) == "jmr" or QString::fromStdString(st->getType())== "jmp"){
            jsonStatement["Dest"] = QString::fromStdString(std::to_string(st->getDest()));

            if(QString::fromStdString(st->getType()) == "jeq" or QString::fromStdString(st->getType()) == "jls" or QString::fromStdString(st->getType()) == "jmr"){
                jsonStatement["Prev Cmp line number"] = QString::fromStdString(std::to_string(st->getPrevCmpLine()));
            }

        }
        QJsonArray jOperandArray;

        for(int i=0; i<st->getNumOperands(); i++){
            QJsonObject jsonOperand;
            jsonOperand["Operand"] = st->getOperand(i).getIdentifier() == NULL ? "NULL" : QString::fromStdString(st->getOperand(i).getIdentifier()->getName());
            //jsonOperand["Operand"] = QString::fromStdString(st->getOperand(i).getIdentifier()->getName());
            jsonOperand["literal"] = QString::fromStdString(st->getOperand(i).getLiteral());
            jsonOperand["index"] = QString::fromStdString(std::to_string(st->getOperand(i).getIndex()));
            jOperandArray.push_back(jsonOperand);

        }
        jsonStatement["Operands"] = jOperandArray;
        if(st->hasLabel()){
            jsonStatement["label"] = QString::fromStdString(st->getLabel()->getName());
        }else{
            jsonStatement["label"] = "null";
        }

        jsonStatement["numOperands"] = QString::fromStdString(std::to_string(st->getNumOperands()));

        jStatementsArray.push_back(jsonStatement);


    }
    jsonProgram["Statements"] =jStatementsArray;

    QJsonArray jVariableArray;
    map<string, Variable*>::iterator it;
    for (it = variables.begin(); it != variables.end(); it++) {
        QJsonObject jsonVariable;
        QJsonArray jValueArray;
        jsonVariable["Name"] = QString::fromStdString(it->first);

        for(int i=0; i<it->second->getNumValues(); i++){
            jValueArray.push_back(QString::fromStdString(std::to_string(it->second->getValue(i))));
        }
        jsonVariable["Value(s)"] = jValueArray;

        jsonVariable["numValues"] = QString::fromStdString(std::to_string(it->second->getNumValues()));

        jVariableArray.push_back(jsonVariable);
    }

    jsonProgram["Variables"] =  jVariableArray;


    QJsonArray jLabelArray;

    map<string, Label*>::iterator iterator;
    for (iterator = labels.begin(); iterator != labels.end(); iterator++) {
        QJsonObject jsonLabel;
        jsonLabel["name"] = QString::fromStdString(iterator->first);
        jLabelArray.push_back(jsonLabel);
    }
    jsonProgram["Labels"] = jLabelArray;

    QJsonDocument doc(jsonProgram);
    string jsonFilename = directory + "/" + name + ".json";

    QFile jsonFile(QString::fromStdString(jsonFilename));
    jsonFile.open(QIODevice::WriteOnly);
    jsonFile.write(doc.toJson());
    jsonFile.close();
}


void Program::printStmtResp(std::string text){
    printTerminal(text);
}

void Program::getUserInput(std::string text){
    getUserInputsignal(text);
}

void Program::getUserInputResp(std::string text){
    sendUserInputResp(text);
}

int Program::getStmtSize() {
    return statements.size();
}

//FIXME: REMOVE AFTER TESTING
void Program::print() {
    cout << "************" << endl;
    for (int i = 0; i < statements.size(); i++) {
      statements[i]->print();
    }

    cout << "************" << endl;
    map<string, Label*>::iterator it;
    for (it = labels.begin(); it != labels.end(); it++) {
      it->second->print();
    }

}
