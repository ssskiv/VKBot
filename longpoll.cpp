#include "longpoll.h"

LongPoll::LongPoll()
{
    manager = new QNetworkAccessManager();
    connect(manager, &QNetworkAccessManager::finished, this, &LongPoll::finished);
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
    query.addQueryItem("v", "5.90");           // Указывается версия используемого API
    QNetworkRequest request;
    url.setQuery(query); // Параметры запроса конкатенируются с адресом запроса
    request.setUrl(url);
    manager->get(request); // Выполняется GET-запрос к серверу ВКонтакте
    qDebug() << url;
}

/*
 * Метод создаёт соединение с Long Poll сервером.
 */
void LongPoll::doLongPollRequest()
{
    QString url("https://{$server}?act=a_check&key={$key}&ts={$ts}&wait=25" ); // Формирование адреса запроса
    url.replace("{$server}", server);
    url.replace("{$key}", key);
    url.replace("{$ts}", QString::number(ts));
    /* QUrlQuery query;
    req.setUrl(url);
    query.addQueryItem("act", "a_check");                               // Параметр действия по умолчанию
    query.addQueryItem("key", key);                                     // Ключ доступа
    query.addQueryItem("wait", "25");                                   // Максимум 25 секунд ожидания
    query.addQueryItem("ts", QString("%1").arg(QString( ts*/ /*)*//*));*/ // Номер последнего события
    // query.addQueryItem("mode", "10"); // Получение вложений и расширенного набора событий
   // url.setQuery(query);*/ // Параметры запроса конкатенируются с адресом запроса
    manager->get(QNetworkRequest(QUrl(url))/*req*/);
    qDebug() << "Request" << url;
}
/*
 * Метод обрабатывает результаты запроса к серверу.
 * @:param: reply -- указатель на ответ сервера.
 */
void LongPoll::finished(QNetworkReply *reply)
{
    QByteArray saveData = reply->readAll();
    QJsonDocument jDoc(QJsonDocument::fromJson(saveData)); // Преобразование ответа в JSON
    if (server.isNull() || server.isEmpty())
    { // Проверка на наличие сохранённых данных
        QJsonObject jObj = jDoc.object().value("response").toObject();
        server = jObj.value("server").toString(); // Сохранение адреса сервера
        key = jObj.value("key").toString();       // Сохранение ключа доступа
        ts = jObj.value("ts").toInt();
        qDebug("NOT OK");// Сохранение номера последнего события
        doLongPollRequest();                      // Открытие соединения с Long Poll сервером
    }
    else
    {
        QJsonObject jObj = jDoc.object();
        if (jObj.contains("failed"))
        { // Проверка на успешность запроса к серверу
            if (jObj.value("failed").toInt() == 1)
            {                                               // Проверка типа ошибки
                ts = jObj.value("ts").toInt() /*.toInt()*/; // Сохранение нового номера последнего события
                doLongPollRequest();                        // Повторный запрос к Long Poll серверу
                qDebug("Failed - ts");
            }
            else
            {
                server.clear(); // Удаление адреса сервера
                key.clear();    // Удаление ключа доступа
                ts = 0;         // Удаление номера последнего события
                qDebug("Unknown error");
                getLongPollServer(); // Запрос новой информации для соединения
            }
        }
        else
        { // Если запрос выполнился без ошибок
           // if (!jObj.value("ts").toObject().isEmpty()){
                ts = jObj.value("ts").toInt();
           // }
            parseLongPollUpdates(jDoc.object().value("updates").toArray()); // Разбор ответа от сервера
            jDoc.object().value("updates").toString().clear();
            doLongPollRequest();                                            // Повторный запрос к Long Poll серверу
        }
    }

    reply->deleteLater(); // Удаление ответа из памяти
}
/*
 * Метод разбирает события, пришедшие от Long Poll сервера.
 * @:param: updates -- массив с новыми событиями.
 */
void LongPoll::parseLongPollUpdates(const QJsonArray updates)
{

   // qDebug() << "Updates:" << !updates.isEmpty();
    if (!updates.isEmpty())
    {
        for (int i = 0; i < updates.size(); i++)
        {
            QJsonArray cur = updates.at(i).toArray();
         //   qDebug() << "Updates:" << updates;
            if (cur.size() < 2)
                continue;

            int type = cur.at(0).toInt();
          //  qDebug() << "Type:" << type;
            if (type == 4)
            {
                if (cur.count() < 6)
                    continue;

                int message_flags = cur.at(2).toInt();
                QString message_text = cur.at(6).toString();
                int user_id = cur.at(3).toInt();

                if (message_flags & 2)
                {
                    // ...
                }
                else
                {
                    qDebug("New message");
                    emit gotNewMessage(user_id, message_text);
                }
            }
        }
    }
}
void LongPoll::settoken(QString toke)
{
    token = toke;
}
int LongPoll::getts()
{
    return ts; //.toInt();
}
