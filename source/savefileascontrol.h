#ifndef SAVEFILEASCONTROL_H
#define SAVEFILEASCONTROL_H

#include <QString>
#include <QObject>

class InputManager;

class SaveFileAsControl: public QObject
{
    Q_OBJECT
public:
    SaveFileAsControl(InputManager* const inputmanager);
    ~SaveFileAsControl();
    bool isSaved();
    void saveFileAs(QString);



protected:
    //void saveFileAs(QString text);

public slots:

signals:
    void saveFileAsControlResponse();

private:
    InputManager *manager;
    bool saved;


};
#endif // SAVEFILEASCONTROL_H

