#ifndef FRAMEPROVIDER_H
#define FRAMEPROVIDER_H

#include <QObject>
#include <QAbstractVideoSurface>
#include <QVideoSurfaceFormat>
#include <QDebug>

class FameProvider : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QAbstractVideoSurface *videoSurface READ videoSurface WRITE setVideoSurface)


public:
    QAbstractVideoSurface* videoSurface() const { return m_surface; }

private:
    QAbstractVideoSurface *m_surface = NULL;
    QVideoSurfaceFormat m_format;

public:

    Q_INVOKABLE void getOneFrame()
    {
        QVideoFrame frame(QImage("J:\\test.jpg"));
        setFormat(frame.width(), frame.height(), frame.pixelFormat());
        onNewVideoContentReceived(frame);
    }

    void setVideoSurface(QAbstractVideoSurface *surface)
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

    void setFormat(int width, int heigth, QVideoFrame::PixelFormat format)
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

public slots:
    void onNewVideoContentReceived(const QVideoFrame &frame)
    {
        if (m_surface) {
            m_surface->present(frame);
        }
    }
};

#endif // FRAMEPROVIDER_H

