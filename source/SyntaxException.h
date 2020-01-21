#ifndef SYNTAXEXCEPTION_H
#define SYNTAXEXCEPTION_H

#include <exception>
#include <string>

class SyntaxException : public std::exception {
  public:
    SyntaxException(const std::string&);
    SyntaxException(const char*);
    ~SyntaxException() throw() ;
    const std::string* explain() const throw();

  private:
    std::string* ex;
};

#endif
