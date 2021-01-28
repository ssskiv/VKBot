#include "vkbot.h"

vkbot::vkbot(/*QWidget *parent*/)
{
QWidget w;
QVBoxLayout *layout= new QVBoxLayout;

pal.setColor(QPalette::Window, Qt::gray);
//pal.setColor(QPalette::WindowText, Qt::green);
pal.setColor(QPalette::Button, Qt::darkCyan);
//pal.setColor(QPalette::, Qt::darkCyan);
qApp->setPalette(pal);
Button *vk=createButton("VK",SLOT(vkClicked()));
if(vkclicked){
lb->setText("sdbnfjklsdfshdfsdgflsdfs");
//vkclicked=false;
}
layout->addWidget(vk);
layout->addWidget(lb);
lb->setFrameStyle(QFrame::Panel | QFrame::Sunken);
//lb.setLayout(&layout);

setLayout(layout);
setWindowTitle("bot");
setWindowIcon(QIcon(":/icons/icon.jpg"));
}
void vkbot::vkClicked()
{
lb->setText("work");
}
Button *vkbot::createButton(const QString &text, const char *member)
{
    Button *button = new Button(text);
    connect(button, SIGNAL(clicked()), this, member);
    return button;
}
