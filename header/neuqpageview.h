#ifndef NEUQPAGE_H
#define NEUQPAGE_H

#pragma once
#include <QWidget>
#include <QStackedWidget>
#include <QPushButton>
#include <QVector>

namespace neuqui {

class NEUQPageView : public QWidget
{
    Q_OBJECT
public:
    explicit NEUQPageView(QWidget *parent = nullptr);

    QStackedWidget* get_Stack();

    QWidget* addPage(QWidget *page , const QString& title);

    void bindPrevButton(QPushButton *btn);
    void bindNextButton(QPushButton *btn);
    void bindJumpButton(QPushButton *btn, int index);

    QString pageTitle(int index) const ;

signals:
    void pageAdded(const QString &title, int index);

private:
    QStackedWidget *stack;
    QVector <QWidget*> pages;
    QStringList titles;
    int pagecount;
};

}




#endif // NEUQPAGE_H
