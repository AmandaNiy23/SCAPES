#include "inputmanager.h"
#include <QMessageBox>
#include <QTime>

InputManager::InputManager(Interface* const interface)
{

   ui = interface;

   //Establishing the necessary connections between the ui and the interface manager
   connect(ui, SIGNAL(newFileSignal()), this, SLOT(createNewFileControl()));
   connect(this, SIGNAL(clearEditorSignal()), ui, SLOT(clearTextEditor()));
   connect(ui, SIGNAL(saveFileSignal()), this, SLOT(createSaveFileControl()));
   connect(ui, SIGNAL(saveFileAsSignal()), this, SLOT(createSaveFileAsControl()));
   connect(ui, SIGNAL(openFileSignal()), this, SLOT(createOpenFileControl()));
   connect(ui, SIGNAL(compileSignal()), this, SLOT(createCompileControl()));
   connect(ui, SIGNAL(runSignal()), this, SLOT(createRunControl()));

}

/*
newFileControlResponse
    purpose: creates a new file control object
*/
void InputManager::createNewFileControl(){
    newfilecontrol = new NewFileControl(this);
    newfilecontrol->newFile();
    delete newfilecontrol;
}

/*
newFileControlResponse
    purpose: triggered by a signal in the control object, loads a new empty file
*/
void InputManager::newFileControlResponse(){
    //delete newfilecontrol;
    clearEditorSignal();
    ui->setWindowTitle("untitled - SCAPES");
    ui->setEnabledSaveOption(false);
}

/*
createOpenFileControl
    purpose: creates a file opening control object
*/
void InputManager::createOpenFileControl(){
    openfilecontrol = new OpenFileControl(this);
    openfilecontrol->openFile();
    delete openfilecontrol;
}

/*
createSaveFileControl
    purpose: creates a file saving control object
*/
void InputManager::createSaveFileControl(){
    QString text = ui->getEditorText();
    QString name = ui->getCurrentFileName();
    savefilecontrol = new saveFileControl(this);
    savefilecontrol->saveFile(text, name);
    delete savefilecontrol;
}



/*
createSaveFileAsControl
    purpose: creates a file saving control object that will request that the user enters a file name
*/
void InputManager::createSaveFileAsControl(){
    QString text = ui->getEditorText();
    savefileascontrol = new SaveFileAsControl(this);
    savefileascontrol->saveFileAs(text);

    //Verifies if the user selected actually gave the file a name
    if(savefileascontrol->isSaved()){
        ui->setEnabledSaveOption(true);
    }
    delete savefileascontrol;
}

/*
createCompileControl
    purpose: creates a compilation control object
*/
void InputManager::createCompileControl(){
    QString text = ui->getEditorText();
    QString name  = ui->getCurrentFileName();

    //displaying a message indicating the begining of compilation
    QTime current = QTime::currentTime();
    ui->setTerminalText(current.toString() + ":  Starting  ...");

    compilecontrol = new CompileControl(this, name, text);
    try {
        compilecontrol->compile();
    } catch (string& e) {

        current = QTime::currentTime();
        ui->setTerminalText(current.toString() + ": " +QString::fromStdString(e));
        throw e;
    }
    delete compilecontrol;
}

/*
createRunControl
    purpose: creates a program execution control object
*/
void InputManager::createRunControl(){
    QString name  = ui->getCurrentFileName();

    runcontrol = new RunControl(this, name);

    try {
        runcontrol->run();
    } catch (string& e) {
        ui->setTerminalText(QString::fromStdString(e));
    }
    delete runcontrol;

}

/*
openFileControlResponse
    purpose: triggered by signal from teh control object, enables the save button
*/
void InputManager::openFileControlResponse(){
    ui->setEnabledSaveOption(true);
}



void InputManager::setFullPath(QString path){
    fullPath = path;
}
void InputManager::setFileDirectory(QString directory){
    fileDirectory = directory;
}

QString InputManager::getFileName(){
    return fileName;
}

QString InputManager::getFileDirectory(){
    return fileDirectory;
}


/*
compilationSuccessResponse
    purpose: display a compilation success message
*/
void InputManager::compilationSuccessResponse(){
    QTime current = QTime::currentTime();
    ui->setTerminalText(current.toString() + ": Compilation Succeeded.");
}

/*
updateFileName
    purpose: update the file name and the window title

    in:
      QString: name - file name
*/
void InputManager::updateFileName(QString name){
    fileName = name;
    ui->setCurrentName(name);
    ui->setWindowTitle(name + " - SCAPES");
}

/*
loadEditorText
    purpose: loading the text found on file during the openFile option

    in:
      QString: text - file contents
*/
void ::InputManager::loadEditorText(QString text){
    ui->setEditorText(text);
}

void InputManager::print(QString text){
    ui->setTerminalText(text);
}

QString InputManager::getUserInput(QString text){
    ui->userInputReq(text);
    QString userinput = ui->getUserInput();
    ui->userInputReq("\n");
    return userinput;
}
