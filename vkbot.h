#ifndef VKBOT_H
#define VKBOT_H
#include "button.h"
#include "longpoll.h"
#include <QObject>
#include <QPalette>
#include <QtWidgets>
#include <QApplication>
class vkbot: public QWidget
{
    Q_OBJECT
    QPalette pal;
    Button *createButton(const QString &text, const char *member);
    QLabel *lb=new QLabel;
    QLabel *notl=new QLabel;
    QLineEdit *tokenf=new QLineEdit;
    LongPoll* lp=new LongPoll;
    QString token=nullptr;
    QString log;
bool vkclicked=false;
public:
    vkbot(/*QWidget *parent = nullptr*/);
    void print(QString text);
private slots:
    void vkClicked();
    void feditingFinished();
};

#endif // VKBOT_H
