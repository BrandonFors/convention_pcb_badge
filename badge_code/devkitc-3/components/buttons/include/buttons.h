#ifndef BUTTONS_H
#define BUTTONS_H

#define DEBOUNCE_TIME_MS 250


typedef enum {
  BUTTON_1 = 1,
  BUTTON_2 = 2,
  BUTTON_2 = 3,
  NA = 4,
} ButtonEvent;


void buttons_init();

#endif
