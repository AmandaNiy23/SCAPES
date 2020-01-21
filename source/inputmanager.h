#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H
#include <interface.h>
#include <newfilecontrol.h>
#include <openfilecontrol.h>
#include <savefilecontrol.h>
#include <savefileascontrol.h>
#include <compilecontrol.h>
#include <runcontrol.h>


class InputManager : public QObject
{
    Q_OBJECT
public:
    InputManager(Interface* const);
    void updateFileName(QString);
    void updateFullPath(QString);
    void loadEditorText(QString);
    void setFileDirectory(QString);
    void setFullPath(QString);
    void print(QString);
    QString getUserInput(QString);
    QString getFileName();
    QString getFileDirectory();



public slots:
    void createNewFileControl();
    void newFileControlResponse();
    void createSaveFileControl();;
    void createSaveFileAsControl();
    void createOpenFileControl();
    void openFileControlResponse();
    void createCompileControl();
    void compilationSuccessResponse();
    void createRunControl();

signals:
    void clearEditorSignal();


private:
    Interface *ui;
    NewFileControl *newfilecontrol;
    saveFileControl *savefilecontrol;
    SaveFileAsControl *savefileascontrol;
    OpenFileControl *openfilecontrol;
    CompileControl *compilecontrol;
    RunControl *runcontrol;
    QString fileDirectory;
    QString fullPath;
    QString fileName;
};

#endif // INPUTMANAGER_H
