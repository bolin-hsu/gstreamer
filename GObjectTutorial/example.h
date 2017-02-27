#ifndef __EXAMPLE_H__
#define __EXAMPLE_H__

#include <glib-object.h>

// Example implements writable interface
#include "writable_interface.h"

#define BOLIN_TYPE_EXAMPLE (example_get_type())

// Macro for upcast object
#define BOLIN_EXAMPLE(object) \
  (G_TYPE_CHECK_INSTANCE_CAST((object), BOLIN_TYPE_EXAMPLE, Example))

// Macro for upcast subclass
#define BOLIN_EXAMPLE_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST((klass), BOLIN_TYPE_EXAMPLE, ExampleClass))

//
#define BOLIN_IS_EXAMPLE(object) \
  (G_TYPE_CHECK_INSTANCE_TYPE((object), BOLIN_TYPE_EXAMPLE))

#define BOLIN_IS_EXAMPLE_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE((klass), BOLIN_TYPE_EXAMPLE))

#define BOLIN_EXAMPLE_GET_CLASS(object) \
  (G_TYPE_INSTANCE_GET_CLASS((object), BOLIN_TYPE_EXAMPLE, ExampleClass))

#define BOLIN_EXAMPLE_GET_PRIVATE(o) \
  (G_TYPE_INSTANCE_GET_PRIVATE((o), BOLIN_TYPE_EXAMPLE, ExamplePrivate))


typedef struct _Example {
  GObject parent_instance;
  gint value;
} Example;

typedef struct _ExampleClass {
  GObjectClass parent_class;

  /* Overridable methods */
  void (*write) (Example* self, gchar* text);
  gint (*get_char_count) (Example* self);
} ExampleClass;

// Public methods
gchar* example_get_last_message (Example* ex);
void example_add_message (Example* ex, gchar* message);
void example_write (Example* self, gchar* text);
gint example_get_char_count (Example* self);	

// constructor
Example* example_new(gchar* initial_message);

#endif // __EXAMPLE_H__
