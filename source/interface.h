#ifndef INTERFACE_H
#define INTERFACE_H

#include <QMainWindow>
#include <codeeditor.h>
#include <terminal.h>
#include <QPlainTextEdit>
#include <QResizeEvent>
#include <QAction>
#include <QMenu>
#include <string>
#include <QEventLoop>

using namespace std;

class InputManager;

namespace Ui {
class Interface;
}

class Interface : public QMainWindow
{
    Q_OBJECT

public:
    explicit Interface(QWidget *parent = nullptr);
    ~Interface();
    QString getCurrentFileName();
    QString getEditorText();
    void setEditorText(QString);
    void setTerminalText(QString);
    void userInputReq(QString);
    QString getUserInput();

protected:
    void resizeEvent(QResizeEvent *event);
    void closeEvent(QCloseEvent *event);

public slots:

    void clearTextEditor();
    void newFileOption();
    void saveFileOption();
    void saveFileAsOption();
    void openFileOption();

    void copyOption();
    void cutOption();
    void pasteOption();
    void undoOption();
    void redoOption();
    void compileOption();
    void runOption();

    void exitOption();
    void setCurrentName(QString name);
    void setEnabledSaveOption(bool trueOrFalse);

    void userInput(QString input);


signals:
    void newFileSignal();
    void saveFileSignal();
    void saveFileAsSignal();
    void openFileSignal();
    void compileSignal();
    void runSignal();
    void inputChanged();

private:
    Ui::Interface *ui;
    QString currentName;
    bool isCompiled = false;
    CodeEditor *texteditor;
    Terminal *terminal;
    InputManager *manager;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuRun;
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionSaveAs;
    QAction *actionExit;
    QAction *actionCopy;
    QAction *actionCut;
    QAction *actionPaste;
    QAction *actionUndo;
    QAction *actionRedo;
    QAction *actionRun;
    QAction *actionCompile;
    QString input = "";
    QEventLoop loop;


};

#endif // INTERFACE_H
