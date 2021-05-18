﻿#ifndef BESBUTTON_H
#define BESBUTTON_H

#include <QPushButton>

class BesButton :public QPushButton
{
public:
    BesButton(QWidget* parent = Q_NULLPTR) : QPushButton(parent) {  }
    BesButton(const QIcon& icon, const QString &text, QWidget *parent = Q_NULLPTR) : QPushButton(icon,text,parent) {  }

    virtual void enterEvent(QEvent *event)
    {
        setCursor(QCursor(Qt::PointingHandCursor));
        QPushButton::enterEvent(event);
    }

    virtual void leaveEvent(QEvent *event)
    {
        unsetCursor();
        QPushButton::leaveEvent(event);
    }
};

#endif // BESBUTTON_H
