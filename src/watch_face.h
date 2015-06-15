#ifndef WATCH_FACE_H
  #define WATCH_FACE_H
  #include <pebble.h>
  #include "fonts.h"
  #include "colors.h"

  void init_watch_face();
  void deinit_watch_face();

  static Window *s_main_window;
  static TextLayer *s_time_layer;
  static GFont *s_time_font;

  static void window_load(Window *window);
  static void window_unload(Window *window);
  static void create_time_layer();
  static void tick_handler(struct tm *tick_time, TimeUnits units_changed);
  static void update_time();
#endif
