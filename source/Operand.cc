#include "Operand.h"

using namespace std;

Operand::Operand(): operand(NULL), literal(""), index(0) {}

Operand::Operand(Identifier *id) : operand(id), literal(""), index(0) {}

Operand::~Operand() {}

void Operand::setIdentifier(Identifier* id) {
    operand = id;
}

void Operand::setLiteral(string literalValue) {
    literal = literalValue;
}

void Operand::setIndex(int val) {
    index = val;
}


Identifier* Operand::getIdentifier() {
    return operand;
}

int Operand::getIndex() {
    return index;
}

string Operand::getLiteral() {
  return literal;
}
