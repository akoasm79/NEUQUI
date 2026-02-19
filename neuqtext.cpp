#include "neuqtext.h"
#include "neuqui.h"

using namespace neuqui;

NEUQText::NEUQText(QWidget *parent)
    : QLineEdit(parent),
    state(Normal),
    themeColor(52,152,219)
{
    setStyleSheet(
        "QLineEdit{border:1px solid #ccc;border-radius:4px;padding:4px;}"
        );
    connect(this, &QLineEdit::returnPressed, this, [=](){
        if (enterHandler)
            enterHandler(text());
    });
}

void NEUQText::setThemeColor(const QColor &color)
{
    themeColor = color;
    setState(state);
}

void NEUQText::setErrorTip(const QString &tip)
{
    setPlaceholderText(tip);
}

void NEUQText::setState(State s)
{
    state = s;

    if (state == Normal)
        setStyleSheet("QLineEdit{border:1px solid #ccc;}");
    else if (state == Error)
        setStyleSheet("QLineEdit{border:2px solid red;}");
    else if (state == Success)
        setStyleSheet(
            QString("QLineEdit{border:2px solid %1;}").arg(themeColor.name())
            );
}

void NEUQText::onEnter(std::function<void(const QString&)> func)
{
    enterHandler = func;
}
