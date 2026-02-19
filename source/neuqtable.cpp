#include "neuqui.h"
#include <QHeaderView>
#include <QMenu>
#include <QClipboard>
#include <QApplication>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>

namespace neuqui{
NEUQTable::NEUQTable(QWidget *parent)
    : QTableWidget(parent)
{
    setAlternatingRowColors(true);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    applyTheme();
    btnAdd  = new QPushButton("新增");
    btnDel  = new QPushButton("删除");
    btnUp   = new QPushButton("上移");
    btnDown = new QPushButton("下移");
    btnSave   = new QPushButton("保存");
    btnLoad = new QPushButton("加载");

    setEditTriggers(QAbstractItemView::DoubleClicked
                    | QAbstractItemView::EditKeyPressed);
    horizontalHeader()->setSectionsClickable(false);


}

void NEUQTable::enableAutoResize(bool on)
{
    auto mode = on ? QHeaderView::Stretch : QHeaderView::Interactive;
    horizontalHeader()->setSectionResizeMode(mode);
    verticalHeader()->setSectionResizeMode(mode);
}

void NEUQTable::setThemeColor(const QColor &color)
{
    themeColor = color;
    applyTheme();
}

void NEUQTable::applyTheme()
{
    setStyleSheet(QString(
        "QTableWidget {"
        "  gridline-color:%1;"
        "  selection-background-color:%2;"
        "}"
        "QHeaderView::section {"
        "  background:%1;"
        "  color:white;"
        "  padding:4px;"
        "}"
    ).arg(themeColor.name(), themeColor.lighter(130).name()));
}

void NEUQTable::addRow(const QList<QString> &data)
{
    int row = rowCount();
    insertRow(row);

    for (int c = 0; c < columnCount(); ++c)
    {
        QTableWidgetItem *item = new QTableWidgetItem;
        if (c < data.size())
            item->setText(data[c]);
        setItem(row, c, item);
    }

    setCurrentCell(row, 0);
}


void NEUQTable::removeSelectedRow()
{
    int row = currentRow();
    if (row >= 0)
        removeRow(row);
}


void NEUQTable::moveRowUp()
{
    int row = currentRow();
    if (row <= 0) return;

    for(int c=0;c<columnCount();++c)
    {
        QString tmp = item(row,c)->text();
        item(row,c)->setText(item(row-1,c)->text());
        item(row-1,c)->setText(tmp);
    }
    setCurrentCell(row-1,0);
}

void NEUQTable::moveRowDown()
{
    int row = currentRow();
    if (row < 0 || row >= rowCount()-1) return;

    for(int c=0;c<columnCount();++c)
    {
        QString tmp = item(row,c)->text();
        item(row,c)->setText(item(row+1,c)->text());
        item(row+1,c)->setText(tmp);
    }
    setCurrentCell(row+1,0);
}


void NEUQTable::setupToolbar()
{
    bar = new QHBoxLayout;

    btnAdd  = new QPushButton("新增", this);
    btnDel  = new QPushButton("删除", this);
    btnUp   = new QPushButton("上移", this);
    btnDown = new QPushButton("下移", this);
    btnSave   = new QPushButton("保存", this);
    btnLoad = new QPushButton("加载", this);

    bar->addWidget(btnAdd);
    bar->addWidget(btnDel);
    bar->addWidget(btnUp);
    bar->addWidget(btnDown);
    bar->addWidget(btnSave);
    bar->addWidget(btnLoad);
    bar->addStretch();
}


NEUQTable* NEUQTable::attach(QWidget *parent, const QRect &rect)
{
    auto wrapper = new QWidget(parent);
    auto layout  = new QVBoxLayout(wrapper);

    auto bar = new QHBoxLayout;
    auto table = new NEUQTable(wrapper);

    bar->addWidget(table->btnAdd);
    bar->addWidget(table->btnDel);
    bar->addWidget(table->btnUp);
    bar->addWidget(table->btnDown);
    bar->addWidget(table->btnSave);
    bar->addWidget(table->btnLoad);
    bar->addStretch();

    layout->addLayout(bar);
    layout->addWidget(table);

    if (!rect.isNull())
        wrapper->setGeometry(rect);
    else
        parent->layout()->addWidget(wrapper);

    connect(table->btnAdd,  &QPushButton::clicked, table, &NEUQTable::onAddClicked);
    connect(table->btnDel,  &QPushButton::clicked, table, &NEUQTable::onDelClicked);
    connect(table->btnUp,   &QPushButton::clicked, table, &NEUQTable::onUpClicked);
    connect(table->btnDown, &QPushButton::clicked, table, &NEUQTable::onDownClicked);
    connect(table->btnSave, &QPushButton::clicked, table, &NEUQTable::onSaveClicked);
    connect(table->btnLoad, &QPushButton::clicked, table, &NEUQTable::onLoadClicked);


    return table;
}


void NEUQTable::onAddClicked()
{
    QList<QString> row;

    int cur = currentRow();
    if (cur >= 0)
    {
        for(int c = 0; c < columnCount(); ++c)
            row << item(cur,c)->text();
    }
    addRow(row);
}

void NEUQTable::onDelClicked()
{
    removeSelectedRow();
}

void NEUQTable::onUpClicked()
{
    moveRowUp();
}

void NEUQTable::onDownClicked()
{
    moveRowDown();
}

void NEUQTable::onSaveClicked()
{
    QString fileName = QFileDialog::getSaveFileName(
        this,
        "保存",
        QDir::homePath(),
        "文件 (*.pwd)"
        );

    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);

    for (int r = 0; r < rowCount(); ++r)
    {
        QStringList row;
        for (int c = 0; c < columnCount(); ++c)
        {
            auto item = this->item(r, c);
            row << (item ? item->text() : "");
        }
        out << row.join(",") << "\n";
    }
}


void NEUQTable::onLoadClicked()
{
    QString fileName = QFileDialog::getOpenFileName(
        this,
        "读取",
        QDir::homePath(),
        "文件 (*.pwd)"
        );

    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    setRowCount(0);
    QTextStream in(&file);

    while (!in.atEnd())
    {
        QString line = in.readLine();
        addRow(line.split(","));
    }
}


void NEUQTable::setHeaders(const QStringList &headers)
{
    setColumnCount(headers.size());
    setHorizontalHeaderLabels(headers);

    horizontalHeader()->setStretchLastSection(true);
}

bool NEUQTable::saveToFile(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    QTextStream out(&file);

    // 先写表头
    QStringList headers;
    for (int c = 0; c < columnCount(); ++c)
        headers << horizontalHeaderItem(c)->text();
    out << headers.join(",") << "\n";

    // 写数据
    for (int r = 0; r < rowCount(); ++r)
    {
        QStringList row;
        for (int c = 0; c < columnCount(); ++c)
            row << item(r,c)->text();
        out << row.join(",") << "\n";
    }

    file.close();
    return true;
}

bool NEUQTable::loadFromFile(int opt,const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QTextStream in(&file);

    clearContents();
    setRowCount(0);

    // 读取表头
    if (opt ==1 && !in.atEnd())
    {
        QStringList headers = in.readLine().split(",");
        setHeaders(headers);
    }

    // 读取数据
    while (!in.atEnd())
    {
        QString line = in.readLine();
        QStringList row = line.split(",");
        addRow(row);
    }

    file.close();
    return true;
}

}
/*自动铺满
auto table = neuqui::NEUQTable::attach(ui->centralWidget);
table->setRowCount(10);
table->setColumnCount(5);
*/

/*指定位置与大小
auto table = neuqui::NEUQTable::attach(ui->centralWidget, QRect(30,40,500,300));
*/

/*改主题色
table->setThemeColor(QColor(0,180,140));
*/

/*一键创建
auto table = neuqui::NEUQTable::attach(ui->centralWidget);
*/
