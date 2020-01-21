#include "newfilecontrol.h"
#include <inputmanager.h>
#include <QMessageBox>

NewFileControl::NewFileControl(InputManager* const inputmanager)
{
    manager = inputmanager;
    connect(this, SIGNAL(loadNewFile()), inputmanager, SLOT(newFileControlResponse()));

}

/*
newFile
    purpose: loads a new empty file
*/
void NewFileControl::newFile(){
    QMessageBox msgBox;
    msgBox.setWindowTitle("Warning");
    msgBox.setText("If this file has not been saved you will lose your work! Are you sure you want to proceed?");
    msgBox.setStandardButtons(QMessageBox::Yes);
    msgBox.addButton(QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    if(msgBox.exec() == QMessageBox::Yes){
        loadNewFile();
    }
}

NewFileControl::~NewFileControl()
{

}





