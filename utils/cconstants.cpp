#include "cconstants.h"

CConstants::CConstants(QObject *obj)
    : QObject(obj),
      m_app_name("zhiboketang"),
      m_app_ver("1.0.0.0"),
      m_shadow_len(10),
      m_wnd_radius(4),
      m_title_height(60),
      m_wnd_min_height(480),
      m_wnd_min_width(640)
{

}
