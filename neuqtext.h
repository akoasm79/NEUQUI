#ifndef NEUQTEXT_H
#define NEUQTEXT_H

#include <QLineEdit>

namespace neuqui {

class NEUQText : public QLineEdit
{
    Q_OBJECT
public:
    enum State {
        Normal,
        Error,
        Success
    };

    explicit NEUQText(QWidget *parent = nullptr);

    void setState(State s);
    void setThemeColor(const QColor &color);
    void setErrorTip(const QString &tip);

    void onEnter(std::function<void(const QString&)> func);

private:
    State state;
    QColor themeColor;
    std::function<void(const QString&)> enterHandler;
};

}

#endif
