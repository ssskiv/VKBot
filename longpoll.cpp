#include "longpoll.h"

LongPoll::LongPoll()
{
    _manager=new QNetworkAccessManager();
    QQmlComponent _component(QQmlEngine &engine,QUrl = QUrl::fromLocalFile("main.qml"));
consPrint("It almost works!");
}
/**
 * Метод получает данные для соединения с Long Poll сервером ВКонтакте.
 */
void LongPoll::getLongPollServer()
{

    QObject*tfield=_gui->findChild<QObject*>("TabView")->findChild<QObject*>("VKTab")->findChild<QObject*>("rect")->findChild<QObject*>("TOKEN");
    QVariant _acsvtoken=tfield->property("text");
    QString _acstoken =_acsvtoken.toString();
    QUrl url("https://api.vk.com/method/messages.getLongPollServer"); // Адрес запроса к API
    QUrlQuery query;
    query.addQueryItem("access_token", _acstoken); // Указывается Access Token
    query.addQueryItem("v", "5.53"); // Указывается версия используемого API
    url.setQuery(query); // Параметры запроса конкатенируются с адресом запроса
    _manager->get(QNetworkRequest(url)); // Выполняется GET-запрос к серверу ВКонтакте
    consPrint("It works!");
}
void LongPoll::consPrint(QString text)
{
    _gui->findChild<QObject*>("main")->setProperty("cppcin",text);
}
/*
 * Метод создаёт соединение с Long Poll сервером.
 */
void LongPoll::doLongPollRequest() {
    QUrl url("https://" + _server); // Формирование адреса запроса
    QUrlQuery query;
    query.addQueryItem("act", "a_check"); // Параметр действия по умолчанию
    query.addQueryItem("key", _key); // Ключ доступа
    query.addQueryItem("ts", QString("%1").arg(_ts)); // Номер последнего события
    query.addQueryItem("wait", "25"); // Максимум 25 секунд ожидания
    query.addQueryItem("mode", "10"); // Получение вложений и расширенного набора событий
    url.setQuery(query); // Параметры запроса конкатенируются с адресом запроса
    _manager->get(QNetworkRequest(url)); // Выполнение GET-запроса к Long Poll серверу
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
    QJsonDocument jDoc = QJsonDocument::fromJson(reply->readAll()); // Преобразование ответа в JSON
    if (_server.isNull() || _server.isEmpty()) {
        // ...
        // Сохранение параметров соединения
        // ...
    } else {
        QJsonObject jObj = jDoc.object();
        if (jObj.contains("failed")) { // Проверка на успешность запроса к серверу
            if (jObj.value("failed").toInt() == 1) { // Проверка типа ошибки
                _ts = jObj.value("ts").toInt(); // Сохранение нового номера последнего события
                doLongPollRequest(); // Повторный запрос к Long Poll серверу
            } else {
                _server.clear(); // Удаление адреса сервера
                _key.clear(); // Удаление ключа доступа
                _ts = ""; // Удаление номера последнего события
                getLongPollServer(); // Запрос новой информации для соединения
            }
        } else { // Если запрос выполнился без ошибок
            _ts = jObj.value("ts").toInt(); // Сохранение нового номера последнего события
            parseLongPollUpdates(jObj.value("updates").toArray()); // Разбор ответа от сервера
            doLongPollRequest(); // Повторный запрос к Long Poll серверу
        }
    }
    reply->deleteLater(); // Удаление ответа из памяти
}
/*
 * Метод разбирает события, пришедшие от Long Poll сервера.
 * @:param: updates -- массив с новыми событиями.
 */
void LongPoll::parseLongPollUpdates(const QJsonArray& updates) {
    for (auto value : updates) { // Цикл по всем событиям
        QJsonArray update = value.toArray(); // Получение объекта события
        switch (update.at(0).toInt()) { // Проверка типа события
        case NEW_MESSAGE:
            emit gotNewMessage(update.at(1).toInt());
            break;
        case INPUT_MESSAGES_READ:
            emit readMessages(update.at(1).toInt(), update.at(2).toInt(), false);
            break;
        case OUTPUT_MESSAGES_READ:
            emit readMessages(update.at(1).toInt(), update.at(2).toInt(), true);
            break;
        case USER_TYPES_IN_DIALOG:
            emit userTyping(update.at(1).toInt(), 0);
            break;
        case USER_TYPES_IN_CHAT:
            emit userTyping(update.at(1).toInt(), update.at(2).toInt());
            break;
        case UNREAD_DIALOGS_CHANGED:
            emit unreadDialogsCounterUpdated(update.at(1).toInt());
            break;
        default:
            break;
        }
    }
}
