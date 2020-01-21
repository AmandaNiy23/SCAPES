#include "Identifier.h"

using namespace std;

Identifier::Identifier(string idName) : name(idName) {}

Identifier::~Identifier() {};

string Identifier::getName() {
    return name;
}

void Identifier::print() {
    cout << "Name: " << name << endl;
}
