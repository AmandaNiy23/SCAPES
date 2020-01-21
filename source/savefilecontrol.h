#ifndef SAVEFILECONTROL_H
#define SAVEFILECONTROL_H

#include <QString>
#include <QObject>
class InputManager;

class saveFileControl : public QObject
{
    Q_OBJECT
public:
    saveFileControl(InputManager* const inputmanager);
    ~saveFileControl();
    void saveFile(QString, QString);

public slots:

signals:
    void saveFileControlResponse();

private:
    InputManager *manager;
};

#endif // SAVEFILECONTROL_H
