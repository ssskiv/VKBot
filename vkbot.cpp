#include "vkbot.h"
vkbot::~vkbot()
{
    //delete
}
vkbot::vkbot(/*QWidget *parent*/)
{
    QWidget w;
    QVBoxLayout *layout = new QVBoxLayout;
    QHBoxLayout *hlay = new QHBoxLayout;
    pal.setColor(QPalette::Window, Qt::gray);
    //pal.setColor(QPalette::WindowText, Qt::green);
    pal.setColor(QPalette::Button, Qt::darkCyan);
    //pal.setColor(QPalette::, Qt::darkCyan);
    qApp->setPalette(pal);
    Button *vk = createButton("Изменить ключ доступа", SLOT(vkClicked()));
    Button *vsk = createButton("Запустить бота", SLOT(feditingFinished()));
    // connect(tokenf,SIGNAL(editingFinished()),this,SLOT(feditingFinished()));
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
    // if(token!=nullptr)
    // {
    // lp->settoken(token);
    // lp->getLongPollServer();
    // lp->doLongPollRequest();
    //lp->parseLongPollUpdates();
    print("Started");
    connect(lp, SIGNAL(gotNewMessage(const int, const QString)), this, SLOT(newMes(const int, const QString)));

    // }
}
void vkbot::vkClicked()
{
    tokenf->setEnabled(true);
}
Button *vkbot::createButton(const QString &text, const char *member)
{
    Button *button = new Button(text);
    connect(button, SIGNAL(clicked()), this, member);
    return button;
}
void vkbot::feditingFinished()
{
    tokenf->setEnabled(false);
    token = tokenf->text();
    lb->setText(token);

    print("Ключ доступа:" + token);
    lp->settoken(token);
    lp->getLongPollServer();
    // lp->connectLongPoll();
    qDebug("Connected");
    // QNetworkReply* rep= lp->getrep();
    //lp->finished(rep);
    // lp->doLongPollRequest();
    print("Bot started");
}
void vkbot::print(QString text)
{
    log += text + '\n';
    notl->setText(log);
}
void vkbot::send(QString mesg, int user_id)
{
    QUrl url("https://api.vk.com/method/messages.send");
    QUrlQuery query;
    query.addQueryItem("user_id", QString::number(user_id));
    query.addQueryItem("message", mesg);
    query.addQueryItem("access_token", token);
    query.addQueryItem("v", "5.90");
    query.addQueryItem("random_id", "0");
    url.setQuery(query);
    print(url.toString());
    manager->get(QNetworkRequest(url));
}
void vkbot::newMes(int id, QString msg)
{
    print(QString(id) + ": " + msg);
    if(msg=="02")
        send("zero-two",id);
   // send(msg,id);
}
