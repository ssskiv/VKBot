#ifndef LONGPOLL_H
#define LONGPOLL_H
#include <QObject>
#include <QUrl>
#include <QUrlQuery>
#include <QNetworkAccessManager>
#include <QQmlEngine>
#include <QUrl>
#include <QQmlComponent>
#include <QLocale>
#include <QVariant>
class LongPoll: public QObject
{

    Q_OBJECT

    QQmlEngine _engine;
    QQmlComponent _component;
    QObject *_gui = _component.create();
    QNetworkAccessManager*_manager;
public:
    LongPoll();
    void getLongPollServer();
    void consPrint(QString text);
    ~LongPoll(){
        delete _manager;
    }
};

#endif // LONGPOLL_H
