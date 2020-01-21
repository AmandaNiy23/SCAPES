#ifndef RUNCONTROL_H
#define RUNCONTROL_H

#include <QObject>
#include <QString>
#include <Program.h>

class InputManager;

class RunControl:public QObject
{
    Q_OBJECT
public:
    RunControl(InputManager* const inputmanager, QString name);
    ~RunControl();
    void run();
    void print(QString);

public slots:
    void printStmtResp(std::string text);
    void getUserInput(std::string text);

signals:
    void sendUserInputResp(std::string text);

private:
    InputManager *manager;
    Program *program;
    QString runOutput;
};

#endif // RUNCONTROL_H


