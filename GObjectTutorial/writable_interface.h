#ifndef __WRITABLEINTERFACE_H__
#define __WRITABLEINTERFACE_H__

#include <glib-object.h>

typedef struct _Writable Writable;

typedef struct _WritableInterface {
  GTypeInterface base_interface;

  // Method we want to declare for the interface
  void (*write) (Writable* object, gchar* text);
  gint (*get_char_count) (Writable* object);
} WritableInterface;

GType writable_get_type(void);

// utility method
void writable_write(Writable* self, gchar* text);
gint writable_get_char_count(Writable* self);

#define TYPE_WRITABLE (writable_get_type())

#define WRITABLE(object) \
  (G_TYPE_CHECK_INSTANCE_CAST((object), TYPE_WRITABLE, Writable))

#define IS_WRITABLE(object) \
  (G_TYPE_CHECK_INSTANCE_TYPE((object), TYPE_WRITABLE))

#define WRITABLE_GET_INTERFACE(object) \
  (G_TYPE_INSTANCE_GET_INTERFACE((object), TYPE_WRITABLE, WritableInterface))

#endif // __WRITABLEINTERFACE_H__
