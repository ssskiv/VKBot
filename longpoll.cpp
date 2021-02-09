#include "longpoll.h"

LongPoll::LongPoll()
{
    _manager=new QNetworkAccessManager();
    connect(_manager,&QNetworkAccessManager::finished,this,&LongPoll::finished);
    qDebug() << QSslSocket::supportsSsl() << QSslSocket::sslLibraryBuildVersionString() << QSslSocket::sslLibraryVersionString();
}
/**
 * Метод получает данные для соединения с Long Poll сервером ВКонтакте.
 */
void LongPoll::getLongPollServer()
{
    QUrl url("https://api.vk.com/method/messages.getLongPollServer"); // Адрес запроса к API
    QUrlQuery query;
    query.addQueryItem("access_token", token); // Указывается Access Token
    query.addQueryItem("v", "5.90"); // Указывается версия используемого API
    QNetworkRequest request;
    url.setQuery(query); // Параметры запроса конкатенируются с адресом запроса
    request.setUrl(url);
    _manager->get(request); // Выполняется GET-запрос к серверу ВКонтакте
    qDebug()<<url;

}

/*
 * Метод создаёт соединение с Long Poll сервером.
 */
void LongPoll::doLongPollRequest() {
    QUrl url("https://" + _server); // Формирование адреса запроса
    QUrlQuery query;
    // qDebug("Connecting....");
    req.setUrl(url);
    query.addQueryItem("act", "a_check"); // Параметр действия по умолчанию
    query.addQueryItem("key", _key); // Ключ доступа
    query.addQueryItem("wait", "25"); // Максимум 25 секунд ожидания
    query.addQueryItem("ts", QString("%1").arg(/*QString(*/_ts/*)*/)); // Номер последнего события

    // query.addQueryItem("mode", "10"); // Получение вложений и расширенного набора событий
    url.setQuery(query); // Параметры запроса конкатенируются с адресом запроса
    // _manager->get(req); // Выполнение GET-запроса к Long Poll серверу
    // req.setRawHeader("Content-Type", "application/x-www-form-urlencoded");
    // QByteArray par="";
    //_manager->get(req);
    rep=_manager->get(req);
    qDebug()<<"Request"<<url;

    //reply=_manager->get(QNetworkRequest(url));
    // qDebug(reply);
}
/*
 * Метод обрабатывает результаты запроса к серверу.
 * @:param: reply -- указатель на ответ сервера.
 */
/*
 * Метод обрабатывает результаты запроса к серверу.
 * @:param: reply -- указатель на ответ сервера.
 */
void LongPoll::finished(QNetworkReply* reply) {
    //qDebug()<<reply;
    //reply->open(QIODevice::ReadWrite);
   // QByteArray data= reply->readAll();
    QJsonArray upd;
    QJsonDocument jDoc( QJsonDocument::fromJson(reply->readAll())); // Преобразование ответа в JSON
    //QVariantMap map = QJsonDocument::fromJson(reply->readAll()).object().toVariantMap();
    //  qDebug()<<jDoc.toVariant().toInt();
    if (_server.isNull() || _server.isEmpty()) { // Проверка на наличие сохранённых данных
        QJsonObject jObj = jDoc.object().value("response").toObject();
        _server = jObj.value("server").toString(); // Сохранение адреса сервера
        _key = jObj.value("key").toString(); // Сохранение ключа доступа
        _ts  = jObj.value("ts").toInt(); // Сохранение номера последнего события
        doLongPollRequest(); // Открытие соединения с Long Poll сервером
    } else {
        QJsonObject jObj = jDoc.object();
        if (jObj.contains("failed")) { // Проверка на успешность запроса к серверу
            if (jObj.value("failed").toInt() == 1) { // Проверка типа ошибки
                _ts = jObj.value("ts").toInt()/*.toInt()*/; // Сохранение нового номера последнего события
                doLongPollRequest(); // Повторный запрос к Long Poll серверу
                qDebug("Failed - ts");
            } else {
                _server.clear(); // Удаление адреса сервера
                _key.clear(); // Удаление ключа доступа
                _ts= 0; // Удаление номера последнего события
                qDebug("Unknown error");
                getLongPollServer(); // Запрос новой информации для соединения
            }
        } else { // Если запрос выполнился без ошибок
            // qDebug()<<"TS:"<<_ts/*jObj.value("ts").toString()*/;
          //  QJsonObject ob=jObj.value("response").toObject();

            if(!jObj.value("response").toObject().isEmpty()){
                _ts = jObj.value("response").toObject().value("ts").toInt(); // Сохранение нового номера последнего события
                //upd=jObj.value("updates").toArray();
            }
            //  else
            // _ts = jObj.value("ts").toInt();
            // qDebug()<<"NEW TS:"<<_ts;
          //  upda=&jDoc;

           // qDebug()<<upda->isNull();
            /*if(!jObj.value("updates").toObject().isEmpty()){*/
            upd= jObj.value("updates").toArray();
            parseLongPollUpdates(&upd); // Разбор ответа от сервера
//}
            doLongPollRequest(); // Повторный запрос к Long Poll серверу

        }

    }

    reply->deleteLater(); // Удаление ответа из памяти
}
/*
 * Метод разбирает события, пришедшие от Long Poll сервера.
 * @:param: updates -- массив с новыми событиями.
 */
void LongPoll::parseLongPollUpdates(const QJsonArray* update/*const*/ /*QJsonDocument upd*/) {
    /*for (auto value : updates) { // Цикл по всем событиям
        QJsonArray update = value.toArray(); // Получение объекта события
        qDebug()<<update.at(4).toString();
        switch (update.at(4).toInt()) { // Проверка типа события
        case 4:
            qDebug("New message");
            // emit gotNewMessage(update.at(1).toInt());
            break;
        }
    }*/
    // QJsonArray updates =map.value("updates").toJsonArray();
    /*  if ( updates.isEmpty() )
    {
        qDebug() << "NO UPDATES";
        return;
    }*/
    // qDebug()<<"Updates:"<<updates.size();
    //QJsonValue obj =upda->object().value("updates");
   // QJsonArray updates=upda->object().value("updates").toArray();
    QJsonArray updates=*update;
    qDebug()<<"Updates:"<<updates.isEmpty();
    for(int i=0; i<updates.size();i++)
    {
        //QVariantList lama= updates.toVariantList();
        QJsonArray cur = updates.at(i).toArray();
        qDebug()<<"Updates:"<<updates;
        if ( cur.size() < 2 )
            continue;

        int type = cur.at(0).toInt();
        qDebug()<<"Type:"<<type;
        if ( type == 4 )
        {
            if ( cur.count() < 6 )
                continue;


            int message_flags = cur.at(2).toInt();
            QString message_text = cur.at(6).toString();
            int user_id=cur.at(3).toInt();

            if ( message_flags & 2 )
            {
                // ...
            }
            else
            {
                qDebug("New message");
                emit gotNewMessage(user_id,message_text);
            }
        }
    }
}
void LongPoll::settoken(QString toke)
{
    token=toke;
}
/*void LongPoll::connectLongPoll()
{
    QString url("{$server}?act=a_check&key={$key}&ts={$ts}&wait=25 ");
    url.replace("{$server}", _server);
    url.replace("{$key}", _key);
    url.replace("{$ts}", _ts);
    _manager->get(QNetworkRequest(url));
}*/
/*void LongPoll::gotNewMessage(int id,QString msg)
{
    qDebug()<<id;
    qDebug()<<msg;
}*/
int LongPoll::getts()
{
    return _ts;//.toInt();
}
