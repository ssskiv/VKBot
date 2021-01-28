#ifndef VKBOT_H
#define VKBOT_H
#include "button.h"
#include <QObject>
#include <QPalette>
#include <QtWidgets>
#include <QApplication>
class vkbot: public QWidget
{
    Q_OBJECT
    QPalette pal;
    Button *createButton(const QString &text, const char *member);

public:
    vkbot(/*QWidget *parent = nullptr*/);
private slots:
    void vkClicked();
};

#endif // VKBOT_H
