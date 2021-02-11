#ifndef VKBOT_H
#define VKBOT_H
#include "button.h"
#include "longpoll.h"
#include <QObject>
#include <QPalette>
#include <QtWidgets>
#include <QApplication>
class vkbot : public QWidget
{
    Q_OBJECT
    QPalette pal;
    Button *createButton(const QString &text, const char *member);
    QLabel *lb = new QLabel;
    QLabel *status = new QLabel;
    QLabel *notl = new QLabel;
    QLineEdit *tokenf = new QLineEdit;
    LongPoll *lp = new LongPoll;
    QString token = nullptr;
    QString log;
    QNetworkAccessManager *manager = new QNetworkAccessManager();
    bool vkclicked = false;

public:
    vkbot(/*QWidget *parent = nullptr*/);
    ~vkbot();
    void print(QString text);
    void send(QString mesg, int user_id,QString atchmnt=0);
private slots:
    void vkClicked();
    void feditingFinished();
    void newMes(const int id, const QString msg);
};

#endif // VKBOT_H
