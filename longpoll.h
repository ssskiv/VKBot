#ifndef LONGPOLL_H
#define LONGPOLL_H
#include <QObject>
#include <QUrl>
#include <QUrlQuery>
#include <QNetworkAccessManager>
 #include <QQmlEngine>
 #include <QUrl>
 #include <QQmlComponent>

class LongPoll
{
    Q_OBJECT
    QQmlEngine _engine;
    QQmlComponent _component;
    QObject *_gui = _component.create();
    QNetworkAccessManager*_manager;
public:
    LongPoll();
    void getLongPollServer();
};

#endif // LONGPOLL_H
