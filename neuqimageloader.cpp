#include "neuqimageloader.h"
#include "neuqui.h"
#include <QVBoxLayout>
#include <QFileDialog>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>

using namespace neuqui;

ImageUploader::ImageUploader(QWidget* parent)
    : QWidget(parent), currentX(0), currentY(0)
{
    setAcceptDrops(true);  // 支持拖放

    imageLabel = new neuqui::NEUQLabel("",this);
    //imageLabel->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    imageLabel->setStyleSheet("background-color: #f0f0f0; border: 1px solid #ccc;");

    QVBoxLayout* layout = new QVBoxLayout(this);

    layout->addWidget(imageLabel);
    setLayout(layout);

}

void ImageUploader::loadImage(const QString& filePath, int x, int y)
{
    QPixmap pix(filePath);
    if (!pix.isNull())
    {
        currentPixmap = pix;
        currentX = x;
        currentY = y;

        imageLabel->setPixmap(pix);
        imageLabel->resize(pix.size());
        imageLabel->move(x, y);

        emit imageLoaded(currentPixmap, x, y);
    }
}

QPixmap ImageUploader::getPixmap() const
{
    return currentPixmap;
}

void ImageUploader::dragEnterEvent(QDragEnterEvent* event)
{
    if (event->mimeData()->hasUrls())
        event->acceptProposedAction();
}

void ImageUploader::dropEvent(QDropEvent* event)
{
    auto urls = event->mimeData()->urls();
    if (!urls.isEmpty())
    {
        QString fileName = urls.first().toLocalFile();
        loadImage(fileName, currentX, currentY);
    }
}
