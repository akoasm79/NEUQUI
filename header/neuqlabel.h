#ifndef NEUQLABEL_H
#define NEUQLABEL_H

#include <QLabel>
#include <QColor>
#include <QFont>


namespace neuqui {

class NEUQLabel : public QLabel
{
    Q_OBJECT
public:
    explicit NEUQLabel(const QString &text = "", QWidget *parent = nullptr);

    // 主题接口
    void setThemeColor(const QColor &color);

    // 自定义接口
    void setTextColor(const QColor &color);
    void setTextFont(const QFont &font);
    void setTextSize(int px);

private:
    QColor m_color;
    QFont  m_font;

    void applyStyle();
};

}


#endif
