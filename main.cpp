#include <QApplication>
#include <QtWidgets>
#include <QPalette>
#include "longpoll.h"
void cprint(QString text,QLabel* cont);
QPushButton *createButton(const QString &text, const char *member, QObject* th);
void clicked();



QString ct;
bool cld;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget w;
    QHBoxLayout layout(&w);
    QTabWidget tabs;
    QWidget vktab;
    QWidget contab;
    QPalette vk;
    QPalette console;
    //QPushButton tfrstrtbt(&vktab);
    QPushButton tfrstrtbt= createButton("",&vktab,);
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
    //tfrstrtbt.setFlat(true);
    tfrstrtbt.setAutoFillBackground(true);
    tabs.addTab(&vktab,"VK");
    tabs.addTab(&contab,"Console");
    cprint("App started",&cont);
    if(cld){
    cprint("clicked",&cont);
    cld=false;
    }
    w.show();
    return a.exec();

}
void cprint(QString text,QLabel* cont)
{
    QDateTime tm(QDateTime::currentDateTime());
    ct+=tm.toString(Qt::SystemLocaleShortDate)+": "+text+'\n';
    cont->setText(ct);
}
QPushButton *createButton(const QString &text, const char *member, QObject* th)
{
    QPushButton *button = new QPushButton(text);
    QObject::connect(button, SIGNAL(clicked()), th, member);
    return button;
}
void clicked()
{
cld=true;
}
