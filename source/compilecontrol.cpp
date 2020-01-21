#include "compilecontrol.h"
#include <inputmanager.h>
#include <string>
#include <QString>


CompileControl::CompileControl(InputManager* const inputmanager, QString name, QString text)
{

    manager = inputmanager;
    connect(this, SIGNAL(compilationSucceeds()), inputmanager, SLOT(compilationSuccessResponse()));
    program = new Program(text.toStdString());
    program->setFileName(name.toStdString());

}

CompileControl::~CompileControl(){
    delete program;
}

/*
compile
    purpose: try compiling the program and serialize if sucessful
*/
void CompileControl::compile(){
    try {
        program->compile();
    } catch (string& e) {
        throw e;
    }
    compilationSucceeds();
    program->serialize(manager->getFileName().toUtf8().constData(), manager->getFileDirectory().toUtf8().constData());
}


QString CompileControl::getCompilationOutput(){
    QString output = "compilationOutput";
    return output;
}
