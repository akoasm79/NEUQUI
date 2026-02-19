#ifndef NEUQIMAGELOADER_H
#define NEUQIMAGELOADER_H

#pragma once
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QPixmap>
#include <QString>
#include "neuqlabel.h"
#include "neuqbutton.h"

namespace neuqui
{

class ImageUploader : public QWidget
{
    Q_OBJECT
public:
    explicit ImageUploader(QWidget* parent = nullptr);

    // 直接加载图片，并指定显示位置
    void loadImage(const QString& filePath, int x = 0, int y = 0);

    // 获取当前图片
    QPixmap getPixmap() const;

signals:
    // 图片加载成功通知
    void imageLoaded(const QPixmap& pix, int x, int y);

protected:
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dropEvent(QDropEvent* event) override;

private:
    neuqui::NEUQLabel* imageLabel;
    QPixmap currentPixmap;
    int currentX;
    int currentY;
};

}
#endif // NEUQIMAGELOADER_H
