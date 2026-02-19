#ifndef NEUQTABLE_H
#define NEUQTABLE_H

#include <QTableWidget>
#include <QColor>
#include <QPushButton>
#include <QHBoxLayout>


namespace neuqui {

//===========================================
//=================neuq表格==================
class NEUQTable : public QTableWidget
{
    Q_OBJECT
public:
    explicit NEUQTable(QWidget *parent = nullptr);

    //
    static NEUQTable* attach(QWidget *parent);                // 自动铺满
    static NEUQTable* attach(QWidget *parent, const QRect&); // 指定位置大小

    //
    void enableAutoResize(bool on = true);
    void setThemeColor(const QColor &color);
    void setHeaders(const QStringList &headers);
    bool saveToFile(const QString &filePath);
    bool loadFromFile(int opt , const QString &filePath);


public slots:
    void onAddClicked();
    void onDelClicked();
    void onUpClicked();
    void onDownClicked();
    void onSaveClicked();
    void onLoadClicked();

private:
    QHBoxLayout *bar;
    void applyTheme();
    QColor themeColor = QColor(33, 150, 243); // 默认 NEUQ 蓝
    QPushButton *btnAdd;
    QPushButton *btnDel;
    QPushButton *btnUp;
    QPushButton *btnDown;
    QPushButton *btnSave;
    QPushButton *btnLoad;

    void setupToolbar();

private slots:
    void addRow(const QStringList &data = {});
    void removeSelectedRow();
    void moveRowUp();
    void moveRowDown();
};
//==========================================
//==========================================

}

#endif
