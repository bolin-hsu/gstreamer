#include "example.h"

void LOG(gchar* message) {
  g_debug("########## %s ##########", message);
}

int main() {
  LOG("creating object");
  Example* ex = example_new("Initial message");
  g_debug("total char: %d", example_get_char_count(ex));

  LOG("calling class method");
  example_add_message(ex, "Message to class");
  g_debug("total char: %d", example_get_char_count(ex));

  LOG("calling overridable class method");
  example_write(ex, "Text to overridable method");
  g_debug("total char: %d", example_get_char_count(ex));

  LOG("calling interface method");
  writable_write(WRITABLE(ex), "Message to interface");
  g_debug("class total char: %d", example_get_char_count(ex));
  g_debug("interface total char: %d", writable_get_char_count(WRITABLE(ex)));

  LOG("deleting object");
  g_object_unref(ex);
}
