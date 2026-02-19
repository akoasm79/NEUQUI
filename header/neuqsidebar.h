#ifndef NEUQSIDEBAR_H
#define NEUQSIDEBAR_H

#pragma once
#include <QWidget>
#include <QVBoxLayout>
#include "neuqbutton.h"

namespace neuqui {

class NEUQPageView;

class NEUQSideBar : public QWidget {
    Q_OBJECT
public:
    explicit NEUQSideBar(QWidget *parent=nullptr);

    void bind(NEUQPageView *view);
    void add(const QString &text);
    void setCurrent(int index);

private:
    QVBoxLayout *layout;
    QVector<NEUQButton*> buttons;
    NEUQPageView *pageView = nullptr;

    void updateStyle();

private slots:
    void onPageAdded(const QString &title, int index);

};

}

#endif // NEUQSIDEBAR_H
