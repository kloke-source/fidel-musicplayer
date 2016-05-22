#ifndef __RESOURCE_fidel_H__
#define __RESOURCE_fidel_H__

#include <gio/gio.h>

class Resource{
public: 
  static G_GNUC_INTERNAL GResource *fidel_get_resource (void); 
};
#endif
