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
