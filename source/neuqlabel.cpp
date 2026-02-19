#include "neuqlabel.h"
#include "neuqui.h"

namespace neuqui{

NEUQLabel::NEUQLabel(const QString &text, QWidget *parent)
    : QLabel(text, parent),
      m_color("#333333"),
      m_font("Microsoft YaHei", 10)
{
    setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    setMinimumHeight(26);
    applyStyle();
}

void NEUQLabel::setThemeColor(const QColor &color)
{
    m_color = color;
    applyStyle();
}

void NEUQLabel::setTextColor(const QColor &color)
{
    m_color = color;
    applyStyle();
}

void NEUQLabel::setTextFont(const QFont &font)
{
    m_font = font;
    applyStyle();
}

void NEUQLabel::setTextSize(int px)
{
    m_font.setPixelSize(px);
    applyStyle();
}

void NEUQLabel::applyStyle()
{
    setFont(m_font);
    setStyleSheet(QString(
        "QLabel{"
        "color:%1;"
        "}"
    ).arg(m_color.name()));
}
}
