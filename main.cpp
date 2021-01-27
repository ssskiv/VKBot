#include <QApplication>
#include <QtWidgets>
#include <QPalette>
void cprint(QString text);


QTabWidget tabs;
QWidget vktab;
QWidget contab;
QPalette vk;
QPalette console;
QPushButton tfrstrtbt(&vktab);
QLabel cont(&contab);
QString ct;
int main(int argc, char *argv[])
{
QApplication a(argc, argv);
QWidget w;
QHBoxLayout layout(&w);
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
cprint("shalabola");
    w.show();
    return a.exec();

}
void cprint(QString text)
{
    ct+=text+'\n';
    cont.setText(ct);
}
