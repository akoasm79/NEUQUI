#include "neuqlinkbutton.h"
#include "neuqui.h"
#include <QDesktopServices>
#include <QString>

namespace neuqui{

NEUQLinkButton::NEUQLinkButton(QWidget* parent):NEUQButton(parent){
    connect(this, &QPushButton::clicked, this, &NEUQLinkButton::openlink);
}

NEUQLinkButton::NEUQLinkButton(const QString &text,QWidget* parent):NEUQButton(text,parent){
    connect(this, &QPushButton::clicked, this, &NEUQLinkButton::openlink);
}

void NEUQLinkButton::setUrl(const QString &url){
    m_url = QUrl(url);
}

void NEUQLinkButton::setUrl(const QUrl &url){
    m_url = url;
}

void NEUQLinkButton::openlink(){
    if (!m_url.isEmpty())
        QDesktopServices::openUrl(m_url);
}

}
