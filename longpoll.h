#ifndef LONGPOLL_H
#define LONGPOLL_H

#include <QObject>
#include <QUrl>
#include <QUrlQuery>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

class LongPoll: public QObject
{

    Q_OBJECT
    QNetworkAccessManager*_manager;
    QString _server,_key,_ts,token;
    QNetworkRequest req;
    QNetworkReply* rep;
    enum LONGPOLL_EVENTS {
        NEW_MESSAGE = 4, // Новое сообщение
        INPUT_MESSAGES_READ = 6, // Входящие сообщения прочитаны
        OUTPUT_MESSAGES_READ = 7, // Исходящие сообщения прочитаны
        USER_TYPES_IN_DIALOG = 61, // Пользователь набирает текст в диалоге
        USER_TYPES_IN_CHAT = 62, // Пользователь набирает текст в чате
        UNREAD_DIALOGS_CHANGED = 80, // Изменение количества непрочитанных диалогов
    };
public:
    LongPoll();
    void settoken(QString toke);
    void getLongPollServer();

    void doLongPollRequest();
    void parseLongPollUpdates(const QJsonArray& updates);
    ~LongPoll(){
        delete _manager;

    }

public slots:
    void finished(QNetworkReply* reply);
};

#endif // LONGPOLL_H
