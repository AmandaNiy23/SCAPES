#ifndef LABEL_H
#define LABEL_H

#include "Identifier.h"

class Label : public Identifier {
    public:
      Label(std::string idName, int num=-1);
      virtual ~Label();
      void setLineNum(int num);
      int getLineNum();

    private:
          int lineNum;
};

#endif
