#include "example.h"
void LOG(gchar* message) {
  g_debug("<<< %s >>>", message);
}

int main() {
  LOG("creating object");
  Example* ex = example_new("Initial message");

  LOG("calling method");
  example_add_message(ex, "More message");

  LOG("deleting object");
  g_object_unref(ex);
}
