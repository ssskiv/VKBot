#include "vkbot.h"

vkbot::vkbot(/*QWidget *parent*/)
{
    QWidget w;
    QVBoxLayout *layout= new QVBoxLayout;
    QHBoxLayout *hlay= new QHBoxLayout;
    pal.setColor(QPalette::Window, Qt::gray);
    //pal.setColor(QPalette::WindowText, Qt::green);
    pal.setColor(QPalette::Button, Qt::darkCyan);
    //pal.setColor(QPalette::, Qt::darkCyan);
    qApp->setPalette(pal);
    Button *vk=createButton("Изменить ключ доступа",SLOT(vkClicked()));
    Button *vsk=createButton("вторая кнопка",SLOT(vkClicked()));
    connect(tokenf,SIGNAL(editingFinished()),this,SLOT(feditingFinished()));
    hlay->addWidget(vk);
    hlay->addWidget(vsk);
    layout->addLayout(hlay);
    hlay->addWidget(lb);
    layout->addWidget(tokenf);
    layout->addWidget(notl);
    lb->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    setLayout(layout);
    setWindowTitle("bot");
    setWindowIcon(QIcon(":/icons/icon.jpg"));
    setMaximumSize(1920,1080);
    setMinimumSize(640, 480);
    if(token!=nullptr)
    {
        lp->settoken(token);
        lp->getLongPollServer();
        lp->finished(lp->getrep());
        print("started");
        send("Bot started","356213674");
    }
}
void vkbot::vkClicked()
{
    tokenf->setReadOnly(false);
}
Button *vkbot::createButton(const QString &text, const char *member)
{
    Button *button = new Button(text);
    connect(button, SIGNAL(clicked()), this, member);
    return button;
}
void vkbot::feditingFinished()
{
    tokenf->setReadOnly(true);
    token=tokenf->text();
    lb->setText(token);

    print("Ключ доступа:"+token);
    lp->settoken(token);
    lp->getLongPollServer();
    lp->finished(lp->getrep());
    print("started");
    send("Bot started","356213674");
}
void vkbot::print(QString text)
{
    log+=text+'\n';
    notl->setText(log);
}
void vkbot::send(QString mesg, QString user_id)
{
QUrl url("https://api.vk.com/method/messages.send");
QUrlQuery query;
query.addQueryItem("user_id", user_id);
query.addQueryItem("message",mesg);
url.setQuery(query);
manager->get(QNetworkRequest(url));
}
