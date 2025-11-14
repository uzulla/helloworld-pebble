#include <pebble.h>

static Window *window;
static TextLayer *text_layer;

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  // Create the TextLayer with specific bounds
  text_layer = text_layer_create(GRect(0, 55, bounds.size.w, 50));

  // Set the text, font, and text alignment
  text_layer_set_text(text_layer, "Hello World!");
  text_layer_set_font(text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
  text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);

  // Add the text layer to the window
  layer_add_child(window_layer, text_layer_get_layer(text_layer));
}

static void window_unload(Window *window) {
  // Destroy the text layer
  text_layer_destroy(text_layer);
}

static void init(void) {
  // Create main Window element and assign to pointer
  window = window_create();

  // Set handlers to manage the elements inside the Window
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });

  // Show the Window on the watch, with animated=true
  window_stack_push(window, true);
}

static void deinit(void) {
  // Destroy Window
  window_destroy(window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
