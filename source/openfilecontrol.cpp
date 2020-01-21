#include "openfilecontrol.h"
#include <inputmanager.h>
#include <QMessageBox>
#include <QString>
#include <QFileDialog>
#include <QTextStream>

OpenFileControl::OpenFileControl(InputManager* const inputmanager)
{
    manager = inputmanager;
    connect(this, SIGNAL(openFileControlResponse()), inputmanager, SLOT(openFileControlResponse()));


}

OpenFileControl::~OpenFileControl()
{

}

/*
openFile
    purpose: open an existing file
*/
void OpenFileControl::openFile(){
    QString fileName = QFileDialog::getOpenFileName(0, "Open File");
    QFile file(fileName);

    //Try opening the file Read Only capabilities, if this fails, display an error message
    if(!file.open(QIODevice::ReadOnly | QFile::Text)){
        QMessageBox::warning(0, "Warning", "Cannot open file: " + file.errorString());
        return;
    }

    //If successful, update the currentFile name
    manager->updateFileName(fileName);

    //copy the text from file, and display it in the textEdit widget
    QTextStream in(&file);
    QString text = in.readAll();
    manager->loadEditorText(text);
    file.close();
    //ui->actionSave->setEnabled(true);
    openFileControlResponse();


}





