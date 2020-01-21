#ifndef OPERAND_H
#define OPERAND_H

#include "Identifier.h"

class Operand {
    private:
      Identifier* operand;
      std::string literal; // for operands that only contain literals
      int index; // for operands that deal with arrays

    public:
      Operand();
      Operand(Identifier *id);
      ~Operand();
      void setIdentifier(Identifier* id);
      void setLiteral(std::string literalValue);
      void setIndex(int val);
      Identifier* getIdentifier();
      int getIndex();
      std::string getLiteral();
};

#endif
