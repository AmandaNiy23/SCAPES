#ifndef IDENTIFIER_H
#define IDENTIFIER_H

#include <string>
#include <iostream>

class Identifier {
    private:
      std::string name;

    public:
      Identifier(std::string idName = "");
      std::string getName();
      virtual ~Identifier();
      void print();
};

#endif
