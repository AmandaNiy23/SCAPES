#include "savefileascontrol.h"
#include <inputmanager.h>
#include <QMessageBox>
#include <QTextStream>
#include <QFileDialog>
#include <QFileInfo>

SaveFileAsControl::SaveFileAsControl(InputManager* const inputmanager)
{
    manager = inputmanager;
    saved = false;
}

/*
saveFileAs
    purpose: save a file and prompt the user for a file name

    in:
      QString: text - contents of the file
*/
void SaveFileAsControl::saveFileAs(QString text)
{
    //full file path
    QFileDialog fileDialog;
    QString fullPath = QFileDialog::getSaveFileName(0, " Save As");

    //file directory
    QDir absoluteDir = QFileInfo(fullPath).absoluteDir();
    QString absolute=absoluteDir.absolutePath();

    //file name
    QString name = QFileInfo(fullPath).fileName();
    manager->setFileDirectory(absolute);

    QFile file(fullPath);


    //Try opening the file with Write Only capabilities, if this fails, display an error message
    if(!file.open(QIODevice::WriteOnly | QFile::Text)){
        QMessageBox::warning(nullptr, "Warning", "Cannot save file: " + file.errorString());
        return;
    }

    //Update the current file name and the window title
    manager->updateFileName(name);


    //update full path
    manager->setFullPath(fullPath);
    //setWindowTitle(fileName);

    //copy the text from the textEdit area, convert it to plain text, and output it to the file
    QTextStream out(&file);
    out << text;

    file.close();

    saved = true;
    //ui->actionSave->setEnabled(true);

    //saveFileAsControlResponse();
}

SaveFileAsControl::~SaveFileAsControl()
{

}

/*
isSaved
    purpose: verify if the file has been saved or not
*/
bool SaveFileAsControl::isSaved(){
    return saved;
}
