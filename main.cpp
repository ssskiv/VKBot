#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "longpoll.h"
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,&app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);}, Qt::QueuedConnection);
    QQmlComponent component(&engine,QUrl(QStringLiteral("qrc:/main.qml")));
    engine.load(url);
    QObject* obj=component.create();
    LongPoll lp;
    /*lp.getLongPollServer();
    lp.doLongPollRequest();*/
    lp.consPrint("IT WOOOOOORK", obj);
    delete obj;
    return app.exec();
}
