#include "neuqpageview.h"
#include <QVBoxLayout>
#include <QStackedWidget>
#include "neuqui.h"

using namespace neuqui;

NEUQPageView::NEUQPageView(QWidget *parent)
    : QWidget(parent)
{
    stack = new QStackedWidget(this);

    auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(stack);

    pagecount=0;
}

QWidget* NEUQPageView::addPage(QWidget *page , const QString& title)
{
    stack->addWidget(page);
    pages.append(page);
    titles << title;
    pagecount++;
    emit pageAdded(title, pagecount-1);
    return page;
}

void NEUQPageView::bindPrevButton(QPushButton *btn)
{
    connect(btn, &QPushButton::clicked, this, [=](){
        int i = stack->currentIndex();
        if (i > 0) stack->setCurrentIndex(i - 1);
    });
}

void NEUQPageView::bindNextButton(QPushButton *btn)
{
    connect(btn, &QPushButton::clicked, this, [=](){
        int i = stack->currentIndex();
        if (i < stack->count() - 1)
            stack->setCurrentIndex(i + 1);
    });
}

void NEUQPageView::bindJumpButton(QPushButton *btn, int index)
{
    connect(btn, &QPushButton::clicked, this, [=](){
        if (index >= 0 && index < stack->count())
            stack->setCurrentIndex(index);
    });
}

QString NEUQPageView::pageTitle(int index) const {
    return titles.value(index);
}

QStackedWidget* NEUQPageView::get_Stack(){
    return stack;
}
