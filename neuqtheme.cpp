#include "neuqui.h"

namespace neuqui{
    //=============================================
    //=================neuq主题==================== //有三种风格：深色，浅色和东秦色（蓝白）
    Theme* Theme::m_instance = nullptr;

    Theme* Theme::instance()
    {
        if(!m_instance)
            m_instance = new Theme;
        return m_instance;
    }

    Theme::Theme(QObject*) : m_style(NEUQ) {}

    void Theme::setTheme(Style style)
    {
        m_style = style;
        emit themeChanged();
    }

    QColor Theme::primary() const
    {
        if(m_style == Dark) return QColor("#2D2D30");
        if(m_style == Light) return QColor("#FFFFFF");
        return QColor("#005BAC");
    }

    QColor Theme::background() const
    {
        if(m_style == Dark) return QColor("#1E1E1E");
        if(m_style == Light) return QColor("#F5F5F5");
        return QColor("#E6F0FA");
    }

    QColor Theme::text() const
    {
        if(m_style == Dark || m_style == NEUQ) return QColor("#FFFFFF");
        return QColor("#000000");
    }
}
//=============================================
//=============================================
