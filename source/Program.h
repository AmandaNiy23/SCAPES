#ifndef PROGRAM_H
#define PROGRAM_H

#include "Factory.h"
#include "Identifier.h"
#include "Variable.h"
#include "Label.h"
#include "SyntaxException.h"
#include "Statement.h"
#include "ReadStmt.h"
#include "DeclIntStmt.h"
#include "DeclArrStmt.h"
#include "PrintStmt.h"
#include "MovStmt.h"
#include "AddStmt.h"
#include "CmpStmt.h"
#include "EndStmt.h"
#include "JMoreStmt.h"
#include "JLessStmt.h"
#include "JEqStmt.h"
#include "JmpStmt.h"

#include <vector>
#include <map>
#include <set>
#include <string>
#include <sstream>
#include <iterator>
#include <regex>
#include <exception>
#include <iostream>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>

class RunControl;

class Program :public QObject
{
    Q_OBJECT
  public:
    Program(std::string, std::string, RunControl* const);
    Program(std::string);
    ~Program();
    void compile();
    void run();
    int checkLabelMembership(std::string);
    void locateLabel(std::string, int&);
    Statement* getLastStmt();
    Variable* getVariable(std::string);
    Label* getLabel(std::string);
    void addVariable(Variable*, std::string);
    void addLabel(Label*, std::string);
    void setFileName(std::string);
    void print();
    void serialize(std::string, std::string);
    void deserialize();
    void locateLabel(std::string, int*);
    int getStmtSize();
    CmpStmt* getLastCmpStmt();
    CmpStmt* getCmpStmt(int);
    int getLastCmpLineNum();
    void setNextStmt(int dest);

public slots:
    void printStmtResp(std::string text);
    void getUserInput(std::string text);
    void getUserInputResp(std::string text);

signals:
    void printTerminal(std::string text);
    void getUserInputsignal(std::string text);
    void sendUserInputResp(std::string text);

  private:
    RunControl *runPgmControl;
    std::string fileName;
    std::string directory;
    int lastCmpInstr = -1;
    vector<string> rawText;  // line number, raw statement
    vector<Statement*> statements;
    map<std::string, int> instructions; // instruction name, numOperands, ex: ("cmp", 2)
    map<std::string, Variable*> variables; //variable name, Identifier Object
    map<std::string, Label*> labels; //Label objects
    void checkSyntax(std::string&, int, bool&);
    void addInstructions(map<std::string, int>&);
    void extractLabel(std::string&, std::string&);
    void trim(std::string& instr, char delim=' ');
    void splitInstr(std::string, vector<std::string>&);
    void deserializeLabels(QJsonArray);
    void deserializeStatements(QJsonArray);
    void deserializeVariables(QJsonArray);
    int nextStmt;

};

#endif
