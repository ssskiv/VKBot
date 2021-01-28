#include "vkbot.h"

vkbot::vkbot(/*QWidget *parent*/)
{
QWidget w;
QBoxLayout layout(QBoxLayout::LeftToRight,&w);
pal.setColor(QPalette::Window, Qt::black);
pal.setColor(QPalette::WindowText, Qt::green);
pal.setColor(QPalette::Button, Qt::darkCyan);
pal.setColor(QPalette::Window, Qt::blue);
w.setPalette(pal);
w.setAutoFillBackground(true);
}
void vkbot::vkclicked(){}
