#ifndef CNATIVEEVENTFILTER_H
#define CNATIVEEVENTFILTER_H

#include <qt_windows.h>
#include <QAbstractNativeEventFilter>
#include <QQuickWindow>

class CNativeEventFilter : public QAbstractNativeEventFilter {
public:
    CNativeEventFilter(HWND handle, QQuickWindow *wnd);

    virtual bool nativeEventFilter(const QByteArray &eventType,
                                   void *message,
                                   long *result);

private:
    QQuickWindow *m_wnd;
    HWND m_hand;
};
#endif  // CNATIVEEVENTFILTER_H
