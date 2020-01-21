#ifndef NEWFILECONTROL_H
#define NEWFILECONTROL_H
#include <QObject>

class InputManager;

class NewFileControl : public QObject
{
    Q_OBJECT
public:
    NewFileControl(InputManager* const inputmanager);
    ~NewFileControl();
    void newFile();

public slots:


signals:
    void loadNewFile();
    //bool editorIsSaved();


private:
    InputManager *manager;
};

#endif // NEWFILECONTROL_H
