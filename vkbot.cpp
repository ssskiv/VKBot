#include "vkbot.h"

vkbot::vkbot(/*QWidget *parent*/)
{
QWidget w;
QVBoxLayout layout(&w);
pal.setColor(QPalette::Window, Qt::black);
pal.setColor(QPalette::WindowText, Qt::green);
pal.setColor(QPalette::Button, Qt::darkCyan);
pal.setColor(QPalette::Window, Qt::blue);
w.setPalette(pal);
w.setAutoFillBackground(true);
Button *vk=createButton("VK",SLOT(vkClicked()));
layout.addWidget(vk);
setLayout(&layout);
}
void vkbot::vkClicked(){}
Button *vkbot::createButton(const QString &text, const char *member)
{
    Button *button = new Button(text);
    connect(button, SIGNAL(clicked()), this, member);
    return button;
}
