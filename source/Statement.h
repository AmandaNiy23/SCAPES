class Program;
class CmpStmt;

#ifndef STATEMENT_H
#define STATEMENT_H
#define MAX_NUM_OPS 2

#include <QObject>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

#include "Operand.h"
#include "Variable.h"
#include "Identifier.h"
#include "Label.h"
#include <map>


class Statement:public QObject
{
    Q_OBJECT
    private:
      Operand operands[MAX_NUM_OPS];
      Program* pgm;
      Label* label;
      int numOperands;
      int lineNumber;
      std::string type;
      std::string userinputval;


public slots:
      void getUserInputResp(std::string userinput);

signals:
    void printTerminal(std::string);
    void getUserInputsignal(std::string text);
    void inputReceived();

    public:
      Statement(Program* program, Label* stmtLabel, int numIds, int line, std::string type_name);
      virtual ~Statement();
      Program* getPgm();
      Label* getLabel();
      int getNumOperands();
      Operand getOperand(int index);
      std::string getType();
      bool hasLabel();
      void setOperands(Identifier* id, int operandIndex=0);
      void setOperands(std::string literalValue, int operandIndex=0);
      void setOperandIndex(int index, int value);
      void setLabel(Label* labelName);
      std::vector<std::string> parseInstr(std::string instr);
      void parseArray(std::string arg, std::string& varName, int& arrayIndex);
      void initOperands(std::string operand, int index);
      void initNumericOperands(std::string operand, int index);
      bool literalCheck(std::string arg, std::string& literal);
      virtual int getDest(){}
      virtual void setDest(int d){}
      virtual void compile(std::string instr) = 0;
      virtual void run() = 0;
      virtual void print();
      void printToTerminal(std::string text);
      void getUserInput(std::string text);
      std::string getUserInputValue();
      int getLineNumber();
      void setLineNumber(int);
      virtual void setPrevCmp(CmpStmt* cmp){}
      virtual CmpStmt* getPrevCmp(){}
      virtual void setPrevCmpLine(int){}
      virtual int getPrevCmpLine(){}
};

#endif
