#ifndef VKBOT_H
#define VKBOT_H

#include <QObject>
#include <QPalette>
#include <QtWidgets>
#include <QApplication>
class vkbot: public QWidget
{
    Q_OBJECT
    QPalette pal;


public:
    vkbot(/*QWidget *parent = nullptr*/);
private slots:
    void vkclicked();
};

#endif // VKBOT_H
