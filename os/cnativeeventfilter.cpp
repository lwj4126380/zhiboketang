#include "cnativeeventfilter.h"

#include <Windows.h>
#include <windowsx.h>
#include <QDebug>
#include "../utils/cconstants.h"

CNativeEventFilter::CNativeEventFilter(HWND handle, QQuickWindow *wnd)
    : QAbstractNativeEventFilter(), m_wnd(wnd), m_hand(handle)
{
}

CNativeEventFilter::~CNativeEventFilter() {
    qDebug() << "CNativeEventFilter destroyed...";
}

bool CNativeEventFilter::nativeEventFilter(const QByteArray &, void *m, long *r)
{
    // On Windows,
    // eventType is set to "windows_generic_MSG" for messages sent to toplevel
    // windows, and "windows_dispatcher_MSG" for system-wide messages  such as
    // messages from a registered hot key. In both cases, the message can be
    // casted to a MSG pointer. The result pointer is only used on Windows, and
    // corresponds to the LRESULT pointer.

    const auto msg = static_cast<MSG *>(m);
    if (msg->hwnd != m_hand && m_wnd->windowState() == Qt::WindowMaximized) {
        return false;
    }

    auto result = r;
    switch (msg->message) {
        case WM_NCHITTEST: {
            *result = 0;
            //整个窗口大小在整个屏幕中的四个点坐标;
            RECT winrect;
            GetWindowRect(m_hand, &winrect);

            const auto x = GET_X_LPARAM(msg->lParam);
            const auto y = GET_Y_LPARAM(msg->lParam);
            //鼠标可以改变窗口大小的像素值范围;
            const ushort scope = 5;
            const auto margin_width
                = CSingleton<CConstants>::Instance()->shadow_len() * m_wnd->devicePixelRatio();

            bool is_resizeable_l = false;
            bool is_resizeable_r = false;
            bool is_resizeable_t = false;
            bool is_resizeable_d = false;
            if (margin_width >= scope) {
                is_resizeable_l = x >= winrect.left + margin_width - scope
                                  && x < winrect.left + margin_width;
                is_resizeable_r = x >= winrect.right - margin_width
                                  && x < winrect.right - margin_width + scope;
                is_resizeable_t = y >= winrect.top + margin_width - scope
                                  && y < winrect.top + margin_width;
                is_resizeable_d = y >= winrect.bottom - margin_width
                                  && y < winrect.bottom - margin_width + scope;
            }
            else  // if (border_width < scope)
            {
                is_resizeable_l = x >= winrect.left && x < winrect.left + scope;
                is_resizeable_r
                    = x >= winrect.right - scope && x < winrect.right;
                is_resizeable_t = y >= winrect.top && y < winrect.top + scope;
                is_resizeable_d
                    = y >= winrect.bottom - scope && y < winrect.bottom;
            }

            const bool resizeWidth = true;  // minimumWidth() != maximumWidth();
            const bool resizeHei = true;  // minimumHeight() != maximumHeight();

            if (resizeWidth) {
                if (is_resizeable_l) {
                    *result = HTLEFT;
                }
                if (is_resizeable_r) {
                    *result = HTRIGHT;
                }
            }
            if (resizeHei) {
                if (is_resizeable_d) {
                    *result = HTBOTTOM;
                }
                if (is_resizeable_t) {
                    *result = HTTOP;
                }
            }
            if (resizeWidth && resizeHei) {
                if (is_resizeable_l && is_resizeable_d) {
                    *result = HTBOTTOMLEFT;
                }
                if (is_resizeable_r && is_resizeable_d) {
                    *result = HTBOTTOMRIGHT;
                }
                if (is_resizeable_l && is_resizeable_t) {
                    *result = HTTOPLEFT;
                }
                if (is_resizeable_r && is_resizeable_t) {
                    *result = HTTOPRIGHT;
                }
            }

            return *result != 0;
        }
    }
    return false;
}
