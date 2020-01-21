#ifndef COMPILECONTROL_H
#define COMPILECONTROL_H

#include <QObject>
#include <QString>
#include <Program.h>

class InputManager;

class CompileControl:public QObject
{
    Q_OBJECT
public:
    CompileControl(InputManager* const inputmanager, QString name, QString text);
    ~CompileControl();
    QString getCompilationOutput();
    void compile();

public slots:

signals:
    void compilationSucceeds();
    void compilationFailed();

private:
    InputManager *manager;
    Program *program;
    QString compilationOutput;

};

#endif // COMPILECONTROL_H
