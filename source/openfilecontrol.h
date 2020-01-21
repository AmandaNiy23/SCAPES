#ifndef OPENFILECONTROL_H
#define OPENFILECONTROL_H

#include <QObject>

class InputManager;

class OpenFileControl :  public QObject
{
    Q_OBJECT
public:
    OpenFileControl(InputManager* const inputmanager);
    ~OpenFileControl();
    void openFile();

public slots:


signals:
    void openFileControlResponse();

protected:



private:
    InputManager *manager;
};

#endif // OPENFILECONTROL_H
