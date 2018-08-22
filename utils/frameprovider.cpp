#include "frameprovider.h"
#include <QDebug>

FrameProvider::FrameProvider(QObject *parent) : QObject(parent)
{
    GetILive()->setLocalVideoCallBack(OnLocalVideo, this);
}

FrameProvider::~FrameProvider()
{
    qDebug() << "FrameProvider destroyed...";
    GetILive()->setLocalVideoCallBack(NULL, NULL);
}

QAbstractVideoSurface* FrameProvider::videoSurface() const
{
    return m_surface;
}

void FrameProvider::OnLocalVideo(const LiveVideoFrame *video_frame, void *custom_data)
{
    FrameProvider *provider = (FrameProvider *)custom_data;
    QVideoFrame frame(video_frame->dataSize, QSize(video_frame->desc.width, video_frame->desc.height),video_frame->desc.width, QVideoFrame::Format_YUV420P);
    frame.map(QAbstractVideoBuffer::ReadWrite);
    memcpy(frame.bits(), video_frame->data, video_frame->dataSize);
    frame.unmap();
    if (!provider->m_format.isValid()) {
        provider->setFormat(frame.width(), frame.height(), frame.pixelFormat());
    }
    provider->onNewVideoContentReceived(frame);
}

#include <QFile>
void FrameProvider::getOneFrame()
{
    QFile f("J:\\kkkkk111.rgb");
    f.open(QFile::ReadWrite);
    QByteArray da = f.readAll();
    f.close();
    QVideoFrame frame(da.size(), QSize(640, 480),640, QVideoFrame::Format_YUV420P);
    frame.map(QAbstractVideoBuffer::ReadWrite);
    memcpy(frame.bits(), da.data(), da.size());
    qDebug() << frame.bits();
    frame.unmap();

    frame.map(QAbstractVideoBuffer::ReadWrite);
    qDebug() << frame.bits()[460799];
    frame.unmap();
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

