#include "interface.h"
#include "ui_interface.h"
#include <QDesktopWidget>
#include <QMessageBox>
#include <inputmanager.h>
#include <QCloseEvent>

Interface::Interface(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Interface)
{
    ui->setupUi(this);

    //setting the window size to 90% of the user's computer screen size
    resize(QDesktopWidget().availableGeometry(this).size()*0.9);

    //adding the editor and terminal fields
    texteditor = new CodeEditor(ui->centralWidget);
    terminal = new Terminal(ui->centralWidget);


    //setting the Dark Mode color scheme
    this->setStyleSheet("MainWindow {background-color: #3b3c40; color: white}");
    texteditor->setStyleSheet("CodeEditor {background-color: #0a0e24; color: white}");
    terminal->setStyleSheet("QPlainTextEdit {background-color: #0a0e24; color: white}");

    //setting the "File" menu label and options
    menuFile = ui->menuBar->addMenu("File");
    actionNew = menuFile->addAction("New");
    actionOpen = menuFile->addAction("Open");
    actionSave = menuFile->addAction("Save");
    actionSave->setEnabled(false);
    actionSaveAs = menuFile->addAction("Save As");
    actionExit = menuFile->addAction("Exit");

    //setting the "Edit" menu label and options
    menuEdit = ui->menuBar->addMenu("Edit");
    actionCopy = menuEdit->addAction("Copy");
    actionCut = menuEdit->addAction("Cut");
    actionPaste = menuEdit->addAction("Paste");
    actionUndo = menuEdit->addAction("Undo");
    actionRedo = menuEdit->addAction("Redo");

    //setting the "File" menu label and options
    menuRun = ui->menuBar->addMenu("Run");
    actionRun = menuRun->addAction("Run");
    actionCompile = menuRun->addAction("Compile");

    setWindowTitle("untitled - SCAPES");
    manager = new InputManager(this);

    //Establishing all of the connections between ui menu options and their corresponding slots
    connect(actionNew, SIGNAL(triggered()), this, SLOT(newFileOption()));
    connect(actionOpen, SIGNAL(triggered()), this, SLOT(openFileOption()));
    connect(actionSave, SIGNAL(triggered()), this, SLOT(saveFileOption()));
    connect(actionSaveAs, SIGNAL(triggered()), this, SLOT(saveFileAsOption()));
    connect(actionExit, SIGNAL(triggered()), this, SLOT(exitOption()));

    connect(actionCopy, SIGNAL(triggered()), this, SLOT(copyOption()));
    connect(actionCut, SIGNAL(triggered()), this, SLOT(cutOption()));
    connect(actionPaste, SIGNAL(triggered()), this, SLOT(pasteOption()));
    connect(actionUndo, SIGNAL(triggered()), this, SLOT(undoOption()));
    connect(actionRedo, SIGNAL(triggered()), this, SLOT(redoOption()));

    connect(actionCompile, SIGNAL(triggered()), this, SLOT(compileOption()));
    connect(actionRun, SIGNAL(triggered()), this, SLOT(runOption()));


}

Interface::~Interface()
{
    delete texteditor;
    delete terminal;
    delete manager;
    delete ui;
}

//Resizing the text editor and the terminal when a window resizing event is detected
void Interface::resizeEvent(QResizeEvent *e)
{
    QMainWindow::resizeEvent(e);
    QRect cr = contentsRect();
    int padding = 15;
    int editorHeight = ((cr.height()-100)/3)*2 -padding - padding/2;
    int terminalTop = editorHeight + (2*padding);
    int terminalHeight = cr.height() - (6*padding) - editorHeight;

    texteditor->setGeometry(QRect(padding, padding, cr.width()-(2*padding), editorHeight));
    terminal->setGeometry(QRect(padding, terminalTop, cr.width()-(2*padding), terminalHeight));

}


void Interface::clearTextEditor()
{
    texteditor->setPlainText("");
    currentName.clear();
}





/*
closeEvent
    purpose: handle the event of the user clicking x
    in:
      QCloseEvent*: event - event of a window being closed
*/
void Interface::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, "Exit",
                                                                tr("Are you sure you want to exit?\n"),
                                                                QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
                                                                QMessageBox::Yes);
    if (resBtn != QMessageBox::Yes) {
        event->ignore();
    } else {
        event->accept();
    }
}

//When the compile button is pressed, the signal triggers this compileOption function
void Interface::compileOption()
{
    //if the current file has never been saved, initiate
    //the save-as option otherwise simply save the file and compile
    if(!(actionSave->isEnabled())){
        saveFileAsOption();
    }else{
        saveFileOption();
    }
    isCompiled = true;

    //if the file has now been saved, proceed with the compilation of the contents of the file
    //by sending the compile signal
    if(actionSave->isEnabled()){
        try {
            compileSignal();
        } catch (string& e) {
            isCompiled = false;
        }
    }
}

//When the run button is pressed, the signal triggers this runOption function
void Interface::runOption()
{

    compileOption();

    //if the file has now been compiled, run the program
    if(isCompiled){
        runSignal();
    }
}

//When the new button is pressed, the signal triggers this newFileOption function
void Interface::newFileOption()
{
    newFileSignal();
}

//When the open button is pressed, the signal triggers this openFileOption function
void Interface::openFileOption()
{
    openFileSignal();
}

//When the save button is pressed, the signal triggers this saveFileOption function
void Interface::saveFileOption(){
    saveFileSignal();
}

//When the "Save As button is pressed, the signal triggers this saveFileAsOption function
void Interface::saveFileAsOption(){
    saveFileAsSignal();
}

//When the exit button is pressed, the signal triggers this exitOption function
void Interface::exitOption(){
    QApplication::quit();
}

//When the copy button is pressed, the signal triggers this copyOption function
void Interface::copyOption(){
    texteditor->copy();
}

//When the cut button is pressed, the signal triggers this cutOption function
void Interface::cutOption(){
    texteditor->cut();
}

//When the paste button is pressed, the signal triggers this pasteOption function
void Interface::pasteOption(){
    texteditor->paste();
}

//When the undo button is pressed, the signal triggers this undoOption function
void Interface::undoOption(){
    texteditor->undo();
}

//When the redo button is pressed, the signal triggers this redoOption function
void Interface::redoOption(){
    texteditor->redo();
}

QString Interface::getEditorText()
{
    return texteditor->toPlainText();
}

QString Interface::getCurrentFileName()
{
    return currentName;
}

void Interface::setEditorText(QString text)
{
    texteditor->setPlainText(text);
}


void Interface::setTerminalText(QString text){

    QString terminalContents = terminal->toPlainText();
    terminal->clear();
    terminal->insertPlainText(terminalContents + text + "\n");
    terminal->scrollDown();
}

void Interface::userInputReq(QString text){
    QString terminalContents = terminal->toPlainText();
    terminal->clear();
    terminal->insertPlainText(terminalContents + text);
    terminal->scrollDown();
}

void Interface::setEnabledSaveOption(bool trueOrFalse)
{
    actionSave->setEnabled(trueOrFalse);
}

void Interface::setCurrentName(QString name){
    currentName = name;
}

QString Interface::getUserInput(){
    //enable user inputs
    terminal->setIsListening(true);
    connect(terminal, SIGNAL(userInput(QString)), this, SLOT(userInput(QString)));

    //wait until the user input has been entered
    connect(this, SIGNAL(inputChanged()), &loop, SLOT(quit()));
    loop.exec();

    return input;

}

void Interface::userInput(QString userinput){
    //setTerminalText(userinput);
    input = userinput;

    //add new line for cleanliness
    //setTerminalText("\n");

    //signal input change
    inputChanged();

}

