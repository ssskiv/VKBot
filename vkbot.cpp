#include "vkbot.h"
vkBot::~vkBot()
{
    delete lb;
    delete status;
    delete notl;
    delete tokenf;
    delete lp;
    delete manager;
    delete layout;
    delete hlay;
}
vkBot::vkBot()
{
    QWidget w;
    pal.setColor(QPalette::Window, Qt::gray);
    pal.setColor(QPalette::Button, Qt::darkCyan);
    qApp->setPalette(pal);
    Button *vk = createButton("Изменить ключ доступа", SLOT(vkClicked()));
    Button *vsk = createButton("Запустить бота", SLOT(feditingFinished()));
    hlay->addWidget(vk);
    hlay->addWidget(vsk);
    layout->addLayout(hlay);
    hlay->addWidget(lb);
    layout->addWidget(status);
    layout->addWidget(tokenf);
    layout->addWidget(notl);
    lb->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    status->setText(QString(lp->getts()));
    setLayout(layout);
    setWindowTitle("bot");
    setWindowIcon(QIcon(":/icons/icon.jpg"));
    setMaximumSize(1920, 1080);
    setMinimumSize(640, 480);
    print("Started");
    connect(lp, SIGNAL(gotNewMessage(const int, const QString)), this, SLOT(newMes(const int, const QString)));
}
void vkBot::vkClicked()
{
    tokenf->setEnabled(true);
}
Button *vkBot::createButton(const QString &text, const char *member)
{
    Button *button = new Button(text);
    connect(button, SIGNAL(clicked()), this, member);
    return button;
}
void vkBot::feditingFinished()
{
    tokenf->setEnabled(false);
    token = tokenf->text();
    lb->setText(token);
    print("Ключ доступа:" + token);
    lp->setToken(token);
    lp->getLongPollServer();
    qDebug("Connected");
    print("Bot started");
}
void vkBot::print(QString text)
{
    log += text + '\n';
    notl->setText(log);
}
void vkBot::send(QString mesg, int user_id, QString atchmnt)
{
    QUrl url("https://api.vk.com/method/messages.send");
    QUrlQuery query;
    query.addQueryItem("user_id", QString::number(user_id));
    query.addQueryItem("message", mesg);
    if (!atchmnt.isNull())
        query.addQueryItem("attachment", atchmnt);
    query.addQueryItem("access_token", token);
    query.addQueryItem("v", "5.90");
    query.addQueryItem("random_id", "0");
    url.setQuery(query);
    print(url.toString());
    manager->get(QNetworkRequest(url));
}
void vkBot::newMes(int id, QString msg)
{
    print(QString(id) + ": " + msg);
    if (msg == "02")
        send("Zero Two", id, "photo-167643469_457241195");
}
