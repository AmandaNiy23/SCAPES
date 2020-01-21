#include "terminal.h"
#include <QTextStream>
#include <QScrollBar>

Terminal::Terminal(QWidget *parent) : QPlainTextEdit(parent)
{
    isListening = false;
}

void Terminal::keyPressEvent(QKeyEvent *event){


    if(event->key()==Qt::Key_Return){
        QTextStream(stdout) <<"!!!!!!"<< endl;
        isListening = false;
        userInput(getLastLine());
    }
    else {
       QPlainTextEdit::keyPressEvent( event );
    }

}

void Terminal::scrollDown(){
    this->verticalScrollBar()->setValue(verticalScrollBar()->maximum());
}

void Terminal::setIsListening(bool state){
    isListening = state;
}

QString Terminal::getLastLine(){

    int count = 0;
    QString text = toPlainText();
    count +=  text.count('\n');

    QString line = text.section('\n', count, count);
    return line.section(':',1,1);
}
