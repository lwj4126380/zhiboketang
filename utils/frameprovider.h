#ifndef FRAMEPROVIDER_H
#define FRAMEPROVIDER_H

#include <QObject>
#include <QAbstractVideoSurface>
#include <QVideoSurfaceFormat>
#include <QDebug>
#include "iLive.h"

using namespace ilive;

class FrameProvider : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QAbstractVideoSurface *videoSurface READ videoSurface WRITE setVideoSurface)


public:
    FrameProvider(QObject *parent=nullptr);
    ~FrameProvider();
    QAbstractVideoSurface* videoSurface() const;

    static void OnLocalVideo(const LiveVideoFrame* video_frame, void* custom_data);

private:
    QAbstractVideoSurface *m_surface = NULL;
    QVideoSurfaceFormat m_format;

public:

    void setVideoSurface(QAbstractVideoSurface *surface);

    void setFormat(int width, int heigth, QVideoFrame::PixelFormat format);

public slots:
    void onNewVideoContentReceived(const QVideoFrame &frame);
};

#endif // FRAMEPROVIDER_H

