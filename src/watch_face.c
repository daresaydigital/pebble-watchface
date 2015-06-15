#include "watch_face.h"

void init_watch_face() {
  s_main_window = window_create();
  s_time_font = fonts_load_custom_font(resource_get_handle(FONT_LARGE));
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);

  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload
  });

  window_set_background_color(s_main_window,COLOR_BACKGROUND);
  window_stack_push(s_main_window, true);
}

void deinit_watch_face() {
  tick_timer_service_unsubscribe();
  fonts_unload_custom_font(s_time_font);
  window_destroy(s_main_window);
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  update_time();
}

static void window_load(Window *window) {
  create_time_layer(window);
}

static void window_unload(Window *window) {
  text_layer_destroy(s_time_layer);
}

static void create_time_layer(Window *window) {
  // Create time TextLayer
  s_time_layer = text_layer_create(GRect(0, 55, 144, 50));
  text_layer_set_background_color(s_time_layer, TRANSPARENT);
  text_layer_set_text_color(s_time_layer, COLOR_CLOCK);

  // Improve the layout to be more like a watchface
  text_layer_set_font(s_time_layer, s_time_font);
  text_layer_set_text_alignment(s_time_layer, GTextAlignmentCenter);

  // Add it as a child layer to the Window's root layer
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_time_layer));
}

static void update_time() {
  // Get a tm structure
  time_t temp = time(NULL);
  struct tm *tick_time = localtime(&temp);

  // Create a long-lived buffer
  static char buffer[] = "00:00";

  // Write the current hours and minutes into the buffer
  if(clock_is_24h_style() == true) {
    // Use 24 hour format
    strftime(buffer, sizeof("00:00"), "%H:%M", tick_time);
  } else {
    // Use 12 hour format
    strftime(buffer, sizeof("00:00"), "%I:%M", tick_time);
  }

  // Display this time on the TextLayer
  text_layer_set_text(s_time_layer, buffer);
}
