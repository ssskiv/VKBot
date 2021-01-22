#include "longpoll.h"

LongPoll::LongPoll()
{
_manager=new QNetworkAccessManager();
QQmlComponent _component(QQmlEngine &engine,QUrl = QUrl::fromLocalFile("main.qml"));

}
/**
 * Метод получает данные для соединения с Long Poll сервером ВКонтакте.
 */
void LongPoll::getLongPollServer() {
    QUrl url("https://api.vk.com/method/messages.getLongPollServer"); // Адрес запроса к API
    QUrlQuery query;
    query.addQueryItem("access_token", _gui->_accessToken.text); // Указывается Access Token
    query.addQueryItem("v", "5.53"); // Указывается версия используемого API
    url.setQuery(query); // Параметры запроса конкатенируются с адресом запроса
    _manager->get(QNetworkRequest(url)); // Выполняется GET-запрос к серверу ВКонтакте
}
