#ifndef TERMINAL_H
#define TERMINAL_H


#include <string>
#include <QPlainTextEdit>
#include <QObject>

class Terminal: public QPlainTextEdit
{
    Q_OBJECT

public:
    Terminal(QWidget *parent = nullptr);
    void keyPressEvent(QKeyEvent *event);
    QString getLastLine();
    void setIsListening(bool);
    void scrollDown();

public slots:

signals:
    void userInput(QString input);

private:
    bool isListening;

};

#endif // TERMINAL_H
