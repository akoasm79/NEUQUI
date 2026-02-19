#include "neuqui.h"
#include <QString>

namespace neuqui{
//=============================================
//=================neuq按钮====================
NEUQButton::NEUQButton(QWidget *parent)
    : QPushButton(parent)
{
    setFixedHeight(40);
    setText("NEUQ Button");

    auto theme = Theme::instance();

    QColor c = theme->primary();

    setStyleSheet(QString(
                      "QPushButton{background:%1;color:%2;border-radius:6px;font-size:16px;}"
                      "QPushButton:hover{background:%3;}"
                      ).arg(c.name(),
                           theme->text().name(),
                           c.lighter(120).name()));

    connect(theme, &Theme::themeChanged, this, &NEUQButton::updateStyle);
}

NEUQButton::NEUQButton(const QString &text,QWidget *parent)
    : QPushButton(text,parent)
{
    setFixedHeight(40);
    setText(text);

    auto theme = Theme::instance();

    QColor c = theme->primary();

    setStyleSheet(QString(
                      "QPushButton{background:%1;color:%2;border-radius:6px;font-size:16px;}"
                      "QPushButton:hover{background:%3;}"
                      ).arg(c.name(),
                           theme->text().name(),
                           c.lighter(120).name()));

    connect(theme, &Theme::themeChanged, this, &NEUQButton::updateStyle);
}

void NEUQButton::setThemeColor(const QColor &color)
{
    QString style = QString(
                        "QPushButton { background-color: %1; color: white; border-radius: 6px; font-size: 16px; }"
                        "QPushButton:hover { background-color: %2; }"
                        ).arg(color.name(), color.lighter(120).name());

    setStyleSheet(style);
}

void NEUQButton::updateStyle()
{
    auto t = Theme::instance();
    QColor c = t->primary();

    setStyleSheet(QString(
                      "QPushButton{background:%1;color:%2;border-radius:6px;font-size:16px;}"
                      "QPushButton:hover{background:%3;}"
                      ).arg(c.name(),
                           t->text().name(),
                           c.lighter(120).name()));
}

void NEUQButton::bindClick(const std::function<void()>& callback) {
    connect(this, &NEUQButton::clicked, this, [=]() {
        if (callback) {
            callback();
        }
    });
}

//============================================
//============================================
}
