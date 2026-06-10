#include <stdio.h>

#include "esp_timer.h"
#include "driver/gptimer.h"
#include "esp_log.h"
#include "esp_err.h"
#include "buttons.h"

#include "board.h"
#include "hal.h"

static volatile uint64_t last_button_time[3] = {0}; // array to hold dobounce times


/**************************************
 * Private function prototypes
 */
void gpio_isr_handler(void* arg);

void buttons_init(){
    hal_register_gpio_callback(BUT_1_PIN, gpio_isr_handler, (void *)BUTTON_1);
    hal_register_gpio_callback(BUT_2_PIN, gpio_isr_handler, (void *)BUTTON_2);
    hal_register_gpio_callback(BUT_3_PIN, gpio_isr_handler, (void *)BUTTON_3);
}

//button interrupt function
void IRAM_ATTR gpio_isr_handler(void* arg){
  ButtonEvent button_pressed = (ButtonEvent)(uintptr_t)arg;
  uint64_t now = esp_timer_get_time() / 1000;
  int button_idx = button_pressed - 1;  // Assuming BUTTON_1=1, BUTTON_2=2
  if(now - last_button_time[button_idx] < DEBOUNCE_TIME_MS) return;
  last_button_time[button_idx] = now;

}
