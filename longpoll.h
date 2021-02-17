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
    Q_OBJECT //Добавляется макрос

    QNetworkAccessManager *manager; //Отправляет, принимает и обрабатывает запросы
    QString server, key, token;         //Строки
    int ts;
    ////QNetworkRequest req;
    //// QNetworkReply *rep;
    //// QJsonDocument upda;
public:
    LongPoll();                                          // Конструктор по умолчанию
    void setToken(QString _token);                       //Метод задает access token классу
    void getLongPollServer();                            //Метод получает первый ts, key и адрес сервера
    void doLongPollRequest();                            //Метод отправляет запрос на получение нового ts
    void parseLongPollUpdates(const QJsonArray updates); //Метод получает массив с обновлениями и новым ts
    //// void connectLongPoll();
    int getts();
    ~LongPoll() { delete manager; }
public slots:
    void finished(QNetworkReply *reply); //Активируется при каждом завершении doLongPollRequest()
signals:
    void gotNewMessage(const int id, const QString msg); //Отправляется при получении нового сообщения
};

#endif // LONGPOLL_H
