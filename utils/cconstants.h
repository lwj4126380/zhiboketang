#ifndef CCONSTANTS_H
#define CCONSTANTS_H

#include <QObject>
#include "stable.h"

class CConstants : public QObject {
    Q_OBJECT
public:
    CConstants(QObject* obj = NULL);
    READONLY_PROPERTY(QString, app_name)
    READONLY_PROPERTY(QString, app_ver)
    READONLY_PROPERTY(int, shadow_len)
    READONLY_PROPERTY(int, wnd_radius)
    READONLY_PROPERTY(int, title_height)
    READONLY_PROPERTY(int, wnd_min_width)
    READONLY_PROPERTY(int, wnd_min_height)

private:
};
#endif  // CCONSTANTS_H
