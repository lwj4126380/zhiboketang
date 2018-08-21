#include "frameprovider.h"
#include "iLive.h"

FrameProvider::FrameProvider(QObject *parent) : QObject(parent)
{

}

QAbstractVideoSurface* FrameProvider::videoSurface() const
{
    return m_surface;
}


void FrameProvider::getOneFrame()
{
    QVideoFrame frame(QImage("J:\\test.jpg"));
    setFormat(frame.width(), frame.height(), frame.pixelFormat());
    onNewVideoContentReceived(frame);
}

void FrameProvider::setVideoSurface(QAbstractVideoSurface *surface)
{
    if (m_surface && m_surface != surface  && m_surface->isActive()) {
        m_surface->stop();
    }

    m_surface = surface;

    if (m_surface && m_format.isValid())
    {
        m_format = m_surface->nearestFormat(m_format);
        m_surface->start(m_format);

    }
}

void FrameProvider::setFormat(int width, int heigth, QVideoFrame::PixelFormat format)
{
    QSize size(width, heigth);
    QVideoSurfaceFormat video_format(size, format);
    m_format = video_format;

    if (m_surface)
    {
        if (m_surface->isActive())
        {
            m_surface->stop();
        }
        m_format = m_surface->nearestFormat(m_format);
        m_surface->start(m_format);
    }
}

void FrameProvider::onNewVideoContentReceived(const QVideoFrame &frame)
{
    if (m_surface) {
        m_surface->present(frame);
    }
}

