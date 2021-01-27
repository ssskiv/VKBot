#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "longpoll.h"

void consPrint(QString text, QObject* gui);

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
    consPrint("IT WOOOOOORK", obj);
    qDebug("it work");
    delete obj;
    return app.exec();
}
void consPrint(QString text, QObject* gui)
{

    //   QObject* tf= gui->findChild<QQuickItem*>("TOKEN");
    if(gui){

       QObject*cptext= gui->findChild<QObject*>("cptext");
cptext->setProperty("text",text);
                //setProperty("text",text);
        qDebug("yea");
    }
    // QMetaObject::invokeMethod(main, "consOut",Q_ARG(QString, text));
}
