#include "imagedataviewer.h"
#include <QSGSimpleTextureNode>
#include <QQuickTextureFactory>

ImageDataViewer::ImageDataViewer()
{
    setFlag(QQuickItem::ItemHasContents, true);
    connect(this, &ImageDataViewer::imageChanged, this, &ImageDataViewer::update);
    connect(this, &ImageDataViewer::xChanged, this, &ImageDataViewer::update);
    connect(this, &ImageDataViewer::yChanged, this, &ImageDataViewer::update);
    connect(this, &ImageDataViewer::widthChanged, this, &ImageDataViewer::update);
    connect(this, &ImageDataViewer::heightChanged, this, &ImageDataViewer::update);
}

QByteArray ImageDataViewer::imageData() const
{
    return m_imageData;
}

void ImageDataViewer::setImageData(const QByteArray &newImageData)
{
    if (m_imageData == newImageData)
        return;
    m_imageData = newImageData;
    emit imageDataChanged();
}

QImage ImageDataViewer::image() const
{
    return m_image;
}

void ImageDataViewer::setImage(const QImage &newImage)
{
    if (m_image == newImage)
        return;
    m_image = newImage;
    emit imageChanged();
}

QSGNode *ImageDataViewer::updatePaintNode(QSGNode *oldNode, QQuickItem::UpdatePaintNodeData *updatePaintNodeData)
{
    QSGSimpleTextureNode *n = static_cast<QSGSimpleTextureNode *>(oldNode);
    if (!n) {
        n = new QSGSimpleTextureNode();
    }
    qDebug() << "update PaintNode" << n->rect();
    n->setRect(boundingRect());
    auto factory = QQuickTextureFactory::textureFactoryForImage(m_image);
    if(factory)
        n->setTexture(factory->createTexture(window()));
    return n;
}
