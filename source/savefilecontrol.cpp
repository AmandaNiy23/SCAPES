#include "savefilecontrol.h"
#include <inputmanager.h>
#include <QMessageBox>
#include <QTextStream>

saveFileControl::saveFileControl(InputManager* const inputmanager)
{
    manager = inputmanager;
}

/*
saveFile
    purpose: save a file to it's existing directory

    in:
      QString: text - file contents
      QString: name -  file name
*/
void saveFileControl::saveFile(QString text, QString name)
{
    QFile file(name);

    //Try opening the file with Write Only capabilities, if this fails, display an error message
    if(!file.open(QIODevice::WriteOnly | QFile::Text)){
        QMessageBox::warning(nullptr, "Warning", "Cannot save file: " + file.errorString());
        return;
    }

    //copy the text from the textEdit area, convert it to plain text, and output it to the file
    QTextStream out(&file);
    out << text;
    file.close();
}

saveFileControl::~saveFileControl()
{

}
