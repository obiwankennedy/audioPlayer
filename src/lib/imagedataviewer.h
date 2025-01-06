#ifndef IMAGEDATAVIEWER_H
#define IMAGEDATAVIEWER_H

#include <QQuickItem>
#include <QByteArray>
#include <QImage>

class ImageDataViewer : public QQuickItem
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QImage image READ image WRITE setImage NOTIFY imageChanged FINAL)
    Q_PROPERTY(QByteArray imageData READ imageData WRITE setImageData NOTIFY imageDataChanged FINAL)
public:
    ImageDataViewer();

    QByteArray imageData() const;
    void setImageData(const QByteArray &newImageData);

    QImage image() const;
    void setImage(const QImage &newImage);

protected:
    virtual QSGNode *updatePaintNode(QSGNode *oldNode, QQuickItem::UpdatePaintNodeData *updatePaintNodeData) override;

signals:
    void imageDataChanged();
    void imageChanged();

private:
    QByteArray m_imageData;
    QImage m_image;
};

#endif // IMAGEDATAVIEWER_H
