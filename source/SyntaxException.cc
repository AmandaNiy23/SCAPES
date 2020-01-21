#include "SyntaxException.h"

using namespace std;

SyntaxException::SyntaxException(const string& e) {
  ex = new string(e);
};


SyntaxException::SyntaxException(const char* e) {
  ex = new string(e);
};


SyntaxException::~SyntaxException() throw() {
  if (ex)
    delete ex;
};

const string* SyntaxException::explain() const throw() {
  return ex;
};
