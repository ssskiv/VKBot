#ifndef VKBOTSERVER_H
#define VKBOTSERVER_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class VKBotServer; }
QT_END_NAMESPACE

class VKBotServer : public QMainWindow
{
    Q_OBJECT

public:
    VKBotServer(QWidget *parent = nullptr);
    ~VKBotServer();

private:
    Ui::VKBotServer *ui;
};
#endif // VKBOTSERVER_H
