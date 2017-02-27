#include <string.h>
#include "example.h"

const gchar* TAG = "";

typedef struct _ExamplePrivate ExamplePrivate;

struct _ExamplePrivate {
  GQueue* queue;
  guint index;
  gboolean active;
};

static void example_writable_interface_init(WritableInterface* iface,
                                            gpointer iface_data);
// G_DEIFNE_TYPE creates the following methods:
//   example_get_type()
// and the prototpye of the following functions:
//   example_init(Example *self)
//   example_class_init(ExampleClass *klass)
// as well as the static variable pointing to parent class
//   static gpointer example_parent_class = NULL;
G_DEFINE_TYPE_EXTENDED(Example, example, G_TYPE_OBJECT, 0, G_IMPLEMENT_INTERFACE(TYPE_WRITABLE, example_writable_interface_init));

static void real_example_write(Example* self, gchar* text);
static gint real_example_get_char_count(Example* self);
static void example_dispose(GObject *object);
static void example_finalize(GObject *object);

// Implement class initialization function.
// It's signature is defined by G_DEFINE_TYPE macro
static void example_class_init(ExampleClass *klass) {
  g_debug("+ %s", __FUNCTION__);

  g_type_class_add_private(klass, sizeof(ExamplePrivate));

  // Hook overridable methods
  klass->write = real_example_write;
  klass->get_char_count = real_example_get_char_count;

  // Hook finalization functions
  GObjectClass *g_object_class = G_OBJECT_CLASS(klass);
  g_object_class->dispose = example_dispose;  // reverse of instance init
  g_object_class->finalize = example_finalize;  // reverse of class init
}

// Implement instance initialization function.
// It's signature is defined by G_DEFINE_TYPE macro
static void example_init(Example* self) {
  g_debug("+ %s", __FUNCTION__);
  // Retrieve private data structure
  ExamplePrivate *priv = BOLIN_EXAMPLE_GET_PRIVATE(self);
  // Alternatively we could do
  // ExamplePrivate *priv = self->priv;

  // Initialize private fields
  self->value = 0;

  // Initialize private fields
  priv->queue = g_queue_new();
  priv->index = 0;
  priv->active = TRUE;
}

// Class destructor
static void example_finalize(GObject *object) {
  g_debug("- %s", __FUNCTION__);
  // Reverse what was allocated by class init
  G_OBJECT_CLASS(example_parent_class)->finalize(object);
}

// Instance destructor
static void example_dispose(GObject *object) {
  g_debug("- %s", __FUNCTION__);
  // Reverse what was allocated by instance init
  Example *self = BOLIN_EXAMPLE(object);
  ExamplePrivate *priv;

  priv = BOLIN_EXAMPLE_GET_PRIVATE(self);

  g_queue_foreach(priv->queue, (GFunc)g_object_unref, NULL);
  g_queue_free(priv->queue);

  G_OBJECT_CLASS(example_parent_class)->dispose(object);
}

// Public methods
gchar* example_get_last_message(Example* ex) {
  g_return_val_if_fail(BOLIN_IS_EXAMPLE(ex), NULL);

  // do stuff

  return NULL;
}

void example_add_message(Example *ex, gchar* message) {
  g_debug("%s: %s", __FUNCTION__, message);
  g_return_if_fail(BOLIN_IS_EXAMPLE(ex));

  // do stuff
  ex->value += strlen(message);
}

static void real_example_write(Example* self, gchar* text) {
  g_debug("%s: %s", __FUNCTION__, text);
  // do stuff
  self->value += strlen(text);
}

static gint real_example_get_char_count(Example* self) {
  g_debug("%s", __FUNCTION__);
  // do stuff
  return self->value;
}

void example_write(Example* self, gchar* text) {
  g_debug("%s: %s", __FUNCTION__, text);
  return BOLIN_EXAMPLE_GET_CLASS(self)->write(self, text);
}

gint example_get_char_count(Example* self) {
  g_debug("%s", __FUNCTION__);
  return BOLIN_EXAMPLE_GET_CLASS(self)->get_char_count(self);
}

Example* example_new(gchar* initial_message) {
  Example* myex;
  myex = g_object_new(BOLIN_TYPE_EXAMPLE, NULL);
  example_add_message(myex, initial_message);
  return myex;
}

void example_writable_write(Writable* self, gchar* text);
gint example_writable_get_char_count(Writable* self);

static void example_writable_interface_init(WritableInterface *iface,
                                            gpointer iface_data) {
  g_debug("+ %s", __FUNCTION__);
  // Bind interface methods with actual implementation
  iface->write  = (void(*)(Writable* self, gchar* text))example_writable_write;
  iface->get_char_count =
    (gint(*)(Writable* self))example_writable_get_char_count;
}

void example_writable_write(Writable* self, gchar* text) {
  g_debug("%s: %s", __FUNCTION__, text);

  // Cast (Writable*) to (Example*) so we can access its data member value.
  Example* ex = BOLIN_EXAMPLE(self);
  ex->value += strlen(text);
}

gint example_writable_get_char_count(Writable* self) {
  g_debug("%s", __FUNCTION__);

  Example* ex = BOLIN_EXAMPLE(self);
  return ex->value;
}
