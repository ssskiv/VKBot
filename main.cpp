#include <QApplication>
#include <QtWidgets>
#include <QPalette>
#include "longpoll.h"
#include "vkbot.h"
//void cprint(QString text,QLabel* cont);

//QString ct;
//bool cld;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    vkbot bot;
    bot.show();
    /*QWidget w;
    QHBoxLayout layout(&w);
    QTabWidget tabs;
    QWidget vktab;
    QWidget contab;
    QPalette vk;
    QPalette console;
    //QPushButton vkbut(&vktab);
    //connect(vkbut,SIGNAL(clicked()),vktab,SLOT());
    Button vkbut= Button::createButton("",SLOT(vkclicked()));
    QLabel cont(&contab);
    ct="dfsjlkfbsdksdjfgbslkjdfhbskljfhbskldjfbskjfsbdkljfbskjdf\n";
    cont.setText(ct);
    ct+="dfsjlkfbsdksdjfgbslkjdfhbskljfhbskldjfbskjfsbdkljfbskjdf\n";
    cont.setText(ct);

    w.resize(640,480);
    w.setWindowTitle("bot");
    w.setWindowIcon(QIcon(":/icons/icon.jpg"));
    layout.addWidget(&tabs);
    console.setColor(QPalette::Window, Qt::black);
    console.setColor(QPalette::WindowText, Qt::green);
    vk.setColor(QPalette::Button, Qt::darkCyan);
    vk.setColor(QPalette::Window, Qt::blue);
    vktab.setPalette(vk);
    vktab.setAutoFillBackground(true);
    contab.setPalette(console);
    contab.setAutoFillBackground(true);
    //vkbut.setFlat(true);
    vkbut.setAutoFillBackground(true);
    tabs.addTab(&vktab,"VK");
    tabs.addTab(&contab,"Console");
    cprint("App started",&cont);

    w.show();*/
    qApp->setStyle(QStyleFactory::create("Fusion"));
    return a.exec();
}
/*void cprint(QString text,QLabel* cont)
{
    QDateTime tm(QDateTime::currentDateTime());
    ct+=tm.toString(Qt::SystemLocaleShortDate)+": "+text+'\n';
    cont->setText(ct);
}*/
