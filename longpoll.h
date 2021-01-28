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
#include "button.h"

class LongPoll: public QObject
{

    Q_OBJECT
    QString access_token;
    QNetworkAccessManager*_manager;
    QString _server,_key,_ts;
    Button *createButton(const QString &text, const char *member);
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
    void getLongPollServer();
    void finished(QNetworkReply* reply);
    void doLongPollRequest();
    void parseLongPollUpdates(const QJsonArray& updates);
    ~LongPoll(){
        delete _manager;
    }


};

#endif // LONGPOLL_H
