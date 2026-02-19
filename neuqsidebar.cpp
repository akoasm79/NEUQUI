#include "neuqsidebar.h"
#include "neuqpageview.h"
#include "neuqpageview.h"

using namespace neuqui;

NEUQSideBar::NEUQSideBar(QWidget *parent):QWidget(parent){
    layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignTop);
    layout->setSpacing(4);
}

void NEUQSideBar::bind(NEUQPageView *view){
    pageView = view;
    connect(view, &NEUQPageView::pageAdded,
            this, &NEUQSideBar::onPageAdded);
}

void NEUQSideBar::add(const QString &text){
    auto btn = new NEUQButton(text,this);
    int index = buttons.size();

    connect(btn,&QPushButton::clicked,[=]{
       // if(pageView) pageView->setCurrentIndex(index);
        setCurrent(index);
    });

    buttons.append(btn);
    layout->addWidget(btn);
}

void NEUQSideBar::setCurrent(int index){
    for(int i=0;i<buttons.size();i++){
        buttons[i]->setChecked(i==index);
    }
    updateStyle();
}

void NEUQSideBar::updateStyle(){
    for(auto b:buttons){
        b->setStyleSheet(b->isChecked()
                         ? "background:#2d7dff;color:white;border-radius:6px;padding:6px;"
                         : "background:transparent;color:#444;padding:6px;");
    }
}

void NEUQSideBar::onPageAdded(const QString &title, int index){
    auto btn = new neuqui::NEUQButton(title,this);

    connect(btn,&QPushButton::clicked,[=]{
        //pageView->setCurrentIndex(index);
        setCurrent(index);
    });

    buttons.insert(index,btn);
    layout->insertWidget(index,btn);
}

