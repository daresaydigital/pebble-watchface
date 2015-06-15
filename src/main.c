#include "watch_face.h"

static void init() {
  init_watch_face();
}

static void deinit() {
  deinit_watch_face();
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
