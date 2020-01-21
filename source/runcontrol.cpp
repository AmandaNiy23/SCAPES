#include "runcontrol.h"
#include <inputmanager.h>
#include <string>
#include <QString>

RunControl::RunControl(InputManager* const inputmanager, QString name)
{
    manager = inputmanager;
    program = new Program(name.toStdString(), manager->getFileDirectory().toUtf8().constData(), this);
    program->setFileName(name.toStdString());

}


RunControl::~RunControl(){
    delete program;
}

void RunControl::printStmtResp(std::string text){
    print(QString::fromStdString(text));
}

void RunControl::getUserInput(std::string text){
    QString userinput = manager->getUserInput(QString::fromStdString(text));
    sendUserInputResp(userinput.toUtf8().constData());
}

void RunControl::print(QString text){
    manager->print(text);
}


void RunControl::run(){

     program->deserialize();

     try {
         program->run();
     } catch (string& e) {
         throw e;
     }

}


