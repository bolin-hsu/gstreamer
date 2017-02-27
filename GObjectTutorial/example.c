#include "example.h"

const gchar* TAG = "";

typedef struct _ExamplePrivate ExamplePrivate;

struct _ExamplePrivate {
  GQueue* queue;
  guint index;
  gboolean active;
};

// G_DEIFNE_TYPE creates the following methods:
//   example_get_type()
// and the prototpye of the following functions:
//   example_init(Example *self)
//   example_class_init(ExampleClass *klass)
// as well as the static variable pointing to parent class
//   static gpointer example_parent_class = NULL;
G_DEFINE_TYPE(Example, example, G_TYPE_OBJECT);

static void real_example_write(Example* self, gchar* text);
static gint real_example_get_char_count(Example* self);
static void example_dispose(GObject *object);
static void example_finalize(GObject *object);

// Implement class initialization function.
// It's signature is defined by G_DEFINE_TYPE macro
static void example_class_init(ExampleClass *klass) {
  g_debug("%s", __FUNCTION__);
  GObjectClass *g_object_class;

  g_type_class_add_private(klass, sizeof(ExamplePrivate));

  g_object_class = G_OBJECT_CLASS(klass);

  // Hook overridable methods
  klass->write = real_example_write;
  klass->get_char_count = real_example_get_char_count;

  // Hook finalization functions
  g_object_class->dispose = example_dispose;  // reverse of instance init
  g_object_class->finalize = example_finalize;  // reverse of class init
}

// Implement instance initialization function.
// It's signature is defined by G_DEFINE_TYPE macro
static void example_init(Example* self) {
  g_debug("%s", __FUNCTION__);
  // Retrieve private data structure
  ExamplePrivate *priv = EXAMPLE_GET_PRIVATE(self);
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
  g_debug("%s", __FUNCTION__);
  // Reverse what was allocated by class init
  G_OBJECT_CLASS(example_parent_class)->finalize(object);
}

// Instance destructor
static void example_dispose(GObject *object) {
  g_debug("%s", __FUNCTION__);
  // Reverse what was allocated by instance init
  Example *self = EXAMPLE(object);
  ExamplePrivate *priv;

  priv = EXAMPLE_GET_PRIVATE(self);

  g_queue_foreach(priv->queue, (GFunc)g_object_unref, NULL);
  g_queue_free(priv->queue);

  G_OBJECT_CLASS(example_parent_class)->dispose(object);
}

// Public methods
gchar* example_get_last_message(Example* ex) {
  g_return_val_if_fail(IS_EXAMPLE(ex), NULL);

  // do stuff

  return NULL;
}

void example_add_message(Example *ex, gchar* message) {
  g_debug("%s: %s", __FUNCTION__, message);
  g_return_if_fail(IS_EXAMPLE(ex));

  // do stuff
}

static void real_example_write(Example* self, gchar* text) {
  // do stuff
}

static gint real_example_get_char_count(Example* self) {
  // do stuff
  return 0;
}

void example_write(Example* self, gchar* text) {
  return EXAMPLE_CLASS(self)->write(self, text);
}

gint example_get_char_count(Example* self) {
  return EXAMPLE_CLASS(self)->get_char_count(self);
}

Example* example_new(gchar* initial_message) {
  Example* myex;
  myex = g_object_new(TYPE_EXAMPLE, NULL);
  example_add_message(myex, initial_message);
  return myex;
}
