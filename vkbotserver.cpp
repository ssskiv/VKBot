#include "vkbotserver.h"
#include "ui_vkbotserver.h"

VKBotServer::VKBotServer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::VKBotServer)
{
    ui->setupUi(this);
}

VKBotServer::~VKBotServer()
{
    delete ui;
}

