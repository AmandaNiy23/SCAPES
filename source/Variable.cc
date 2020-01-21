#include "Variable.h"

using namespace std;

Variable::Variable(string idName, int numVal) : Identifier(idName), numValues(numVal) {
    setSize(numVal);

    values = new int[numVal];
    for(int i = 0; i<numVal; i++){
            values[i] = -1;
        }
}

Variable::~Variable() {
    delete [] values;
};

int Variable::getValue(int index) {
    return values[index];
}

int Variable::getNumValues() {
    return numValues;
}

void Variable::setValue(int val, int index){
    values[index] = val;
}

void Variable::setSize(int size) { //TODO: added
    values = new int[size];

    for(int i = 0; i<size; i++){
      values[i] = -1;
    }
}

void Variable::reallocateArrSize(int size) { //TODO: added
    delete [] values;
    numValues = size;
    setSize(size);
}
