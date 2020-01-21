#include "Label.h"

using namespace std;

Label::Label(string idName, int num) : Identifier(idName), lineNum(num) {}

Label::~Label() {}

int Label::getLineNum(){
    return  lineNum;
}

void Label::setLineNum(int num){
    lineNum = num;
}
