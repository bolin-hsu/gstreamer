#include "writable_interface.h"

static void writable_base_init(gpointer g_class);
//static void writable_finalize(WritableInterface* iface, void* tmp);
static void writable_init(WritableInterface* iface);

GType writable_get_type(void) {
  static GType writable_type = 0;
  if (!writable_type) {
    static const GTypeInfo writable_info = {
      sizeof(WritableInterface),
      NULL,  // base_init
      NULL,  // base_finalize
      (void (*)(void *, void *))writable_init,  // class_init
      NULL,  // class_finalize
      NULL,  // class_data
      0,
      0,  // n_preallocs
      NULL  // instance_init
    };

    writable_type = g_type_register_static(G_TYPE_INTERFACE, "Writable",
                                           &writable_info, 0);
  }

  return writable_type;
}

static void writable_init(WritableInterface* iface) {
  g_debug("+ %s", __FUNCTION__);
  static gboolean initialized = FALSE;

  if (!initialized) {
    // do stuff
    initialized = TRUE;
  }
}

//static void writable_finalize(WritableInterface* iface, void* tmp) {
//  g_debug("- %s", __FUNCTION__);
//  // cleanup what was done by init
//}

void writable_write(Writable* self, gchar* text) {
  g_debug("%s: %s", __FUNCTION__, text);
  WRITABLE_GET_INTERFACE(self)->write(self, text);
}

gint writable_get_char_count(Writable* self) {
  g_debug("%s", __FUNCTION__);
  return WRITABLE_GET_INTERFACE(self)->get_char_count(self);
}
