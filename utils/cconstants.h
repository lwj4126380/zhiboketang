#ifndef CCONSTANTS_H
#define CCONSTANTS_H

#include <QObject>
#include "stable.h"

#define SuixinboServerUrl	"http://118.89.110.196/index.php"
#define SuixinboAppid		1400124346
#define SuixinboAccountType 34657
#define SuixinboZhiboid		1257290608


#define LiveMaster	"LiveMaster" //主播
#define LiveGuest	"LiveGuest"  //连麦观众
#define Guest		"Guest"		 //观众

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
