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

class LongPoll : public QObject
{

    Q_OBJECT
    QNetworkAccessManager *manager;
    QString server, key, token;
    QString ts;
    QNetworkRequest req;
    QNetworkReply *rep;
    QJsonDocument upda;

public:
    LongPoll();
    void settoken(QString toke);
    void getLongPollServer();
    void doLongPollRequest();
    void parseLongPollUpdates(const QJsonArray updates /*const*/ /*QJsonDocument upd*/);
    void connectLongPoll();
    int getts();
    ~LongPoll()
    {
        delete manager;
    }

public slots:
    void finished(QNetworkReply *reply);
signals:

    void gotNewMessage(const int id, const QString msg);
};

#endif // LONGPOLL_H
