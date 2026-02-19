#ifndef NEUQLINKBUTTON_H
#define NEUQLINKBUTTON_H

#include "neuqbutton.h"
#include <QUrl>
#include <QString>

namespace neuqui {

class NEUQLinkButton : public NEUQButton{
    Q_OBJECT
public:
    explicit NEUQLinkButton(QWidget* parent = nullptr);
    explicit NEUQLinkButton(const QString &text,QWidget* parent = nullptr);

    void setUrl(const QString &url);
    void setUrl(const QUrl &url);

private slots:
    void openlink();

private:
    QUrl m_url;
};

}
#endif // NEUQLINKBUTTON_H
