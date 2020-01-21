#ifndef VARIABLE_H
#define VARIABLE_H

#include "Identifier.h"
#include <vector>
#include <iostream>

class Variable : public Identifier {
    private:
      int* values;
      int numValues;
      void setSize(int size);

    public:
      Variable(std::string idName, int numVal=1);
      virtual ~Variable();
      int getValue(int index=0);
      int getNumValues();
      void setValue(int val, int index=0);
      void reallocateArrSize(int size);
};

#endif
