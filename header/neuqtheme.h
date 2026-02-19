#ifndef NEUQTHEME_H
#define NEUQTHEME_H

#endif // NEUQTHEME_H

#include <QColor>
#include <QObject>

//===========================================
//=================neuq主题==================
namespace neuqui{
    class Theme : public QObject
    {
        Q_OBJECT
    public:
        enum Style { Light, Dark, NEUQ };  //三种主题

        static Theme* instance();

        void setTheme(Style style);
        QColor primary() const;
        QColor background() const;
        QColor text() const;

    signals:
        void themeChanged();

    private:
        explicit Theme(QObject* parent = nullptr);
        static Theme* m_instance;
        Style m_style;
    };
}
//==========================================
//==========================================
