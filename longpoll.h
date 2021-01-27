#ifndef LONGPOLL_H
#define LONGPOLL_H
#include <QObject>
#include <QUrl>
#include <QUrlQuery>
#include <QNetworkAccessManager>
#include <QQmlEngine>
#include <QQmlComponent>
#include <QLocale>
#include <QVariant>
#include <QJsonDocument>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonArray>
#include <fstream>
#include <QtQuick>
class LongPoll: public QObject
{

    Q_OBJECT
    QString access_token;
    QNetworkAccessManager*_manager;
    QString _server,_key,_ts;
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
    void getLongPollServer(QObject*_gui);

    void finished(QNetworkReply* reply, QObject* _gui);
    void doLongPollRequest();
    void parseLongPollUpdates(const QJsonArray& updates);
    ~LongPoll(){
        delete _manager;
    }
};

#endif // LONGPOLL_H
