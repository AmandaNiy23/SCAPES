#include "Factory.h"
#include "Program.h"

using namespace std;


/*
createStmt
    purpose: create a statement using the factory design pattern
    in:
      string: instr - instruction
      Program* pgm - pointer to calling program
      Label* label - label object associated with statement
*/
Statement* Factory::createStmt(string instr, Program* pgm, Label* label, int line) {
    Statement* stmt;
    // verify instruction and create appropriate statement
    switch(resolveEnum(instr)) {
      case dci: {
        stmt = new DeclIntStmt(pgm, label, 1, line);
        break;
      }
      case dca: {
        stmt = new DeclArrStmt(pgm, label, 2, line);
        break;
      }
      case rdi: {
        stmt = new ReadStmt(pgm, label, 1, line);
        break;
      }
      case prt: {
        stmt = new PrintStmt(pgm, label, 1, line);
        break;
      }
      case mov: {
        stmt = new MovStmt(pgm, label, 2, line);
        break;
      }
      case add: {
        stmt = new AddStmt(pgm, label, 2, line);
        break;
      }
      case cmp: {
        stmt = new CmpStmt(pgm, label, 2, line);
        break;
      }
      case jmr: {
        stmt = new JMoreStmt(pgm, label, 1, line);
        break; //TODO: JIM ADDED
      }
      case jls: {
        stmt = new JLessStmt(pgm, label, 1, line);
        break;
      }
      case jeq: {
        stmt =  new JEqStmt(pgm, label, 1, line);
        break;
      }
      case jmp: {
        stmt = new JmpStmt(pgm, label, 1, line);
        break;
      }
      case fin: {
        stmt = new EndStmt(pgm, label, 0, line);
        break;
      }
    }
    return stmt;
}

/*
resolveEnum
    purpose: map string value of instruction to corresponding enum value
    in:
      string: input - instruction
    out:
      validInstr: enum value corresponding to instruction
*/
Factory::validInstr Factory::resolveEnum(string input) {
    static const map<string, validInstr> instrMap {
      {"dci", dci},
      {"dca", dca},
      {"rdi", rdi},
      {"prt", prt},
      {"mov", mov},
      {"add", add},
      {"cmp", cmp},
      {"jls", jls},
      {"jmr", jmr},
      {"jeq", jeq},
      {"jmp", jmp},
      {"end", fin}
    };
    auto it = instrMap.find(input);

    if (it != instrMap.end()) {
      return it->second;
    }
    return invalid;
}
