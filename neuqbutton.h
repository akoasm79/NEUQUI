#ifndef NEUQBUTTON_H
#define NEUQBUTTON_H

#include <QPushButton>
#include <QColor>
#include <QString>

namespace neuqui{
    //==================================================
    //==============neuq按钮=============================
    class NEUQButton : public QPushButton
    {
        Q_OBJECT
    public:
        explicit NEUQButton(QWidget *parent = nullptr); //创建按钮
        explicit NEUQButton( const QString &text,QWidget *parent = nullptr);

        void setThemeColor(const QColor &color); //设置颜色

        void updateStyle(); //更新主题

        void bindClick(const std::function<void()>& callback);//点击绑定功能
    };
    //==================================================
    //==================================================
}
#endif // NEUQBUTTON_H
