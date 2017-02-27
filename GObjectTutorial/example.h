//#include <glib.h>
#include <glib-object.h>
#define TYPE_EXAMPLE (example_get_type())

// Macro for upcast object
#define EXAMPLE(object) \
  (G_TYPE_CHECK_INSTANCE_CAST((object), TYPE_EXAMPLE, Example))

// Macro for upcast subclass
#define EXAMPLE_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST((klass), TYPE_EXAMPLE, ExampleClass))

// 
#define IS_EXAMPLE(object) \
  (G_TYPE_CHECK_INSTANCE_TYPE((object), TYPE_EXAMPLE)) 

#define IS_EXAMPLE_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE((klass), TYPE_EXAMPLE))

#define EXAMPLE_GET_CLASS(object) \
  (G_TYPE_INSTANCE_GET_CLASS((object), TYPE_EXAMPLE, ExampleClass))

#define EXAMPLE_GET_PRIVATE(o) \
  (G_TYPE_INSTANCE_GET_PRIVATE((o), TYPE_EXAMPLE, ExamplePrivate))


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

