#ifndef FRAMEPROVIDER_H
#define FRAMEPROVIDER_H

#include <QObject>
#include <QAbstractVideoSurface>
#include <QVideoSurfaceFormat>
#include <QDebug>

class FrameProvider : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QAbstractVideoSurface *videoSurface READ videoSurface WRITE setVideoSurface)


public:
    FrameProvider(QObject *parent=nullptr);
    QAbstractVideoSurface* videoSurface() const;

private:
    QAbstractVideoSurface *m_surface = NULL;
    QVideoSurfaceFormat m_format;

public:

    Q_INVOKABLE void getOneFrame();
    void setVideoSurface(QAbstractVideoSurface *surface);

    void setFormat(int width, int heigth, QVideoFrame::PixelFormat format);

public slots:
    void onNewVideoContentReceived(const QVideoFrame &frame);
};

#endif // FRAMEPROVIDER_H

