#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_err.h"
#include "buttons.h"
#include "board.h"


/**************************************
 * Private function prototypes
 */
void IRAM_ATTR gpio_isr_handler(void* arg);

void buttons_init(){
  //configure button 1 
  gpio_reset_pin(BUT_1_PIN);
  gpio_set_direction(BUT_1_PIN, GPIO_MODE_INPUT);

  gpio_pullup_en(BUT_1_PIN);
  gpio_pulldown_dis(BUT_1_PIN);

  gpio_set_intr_type(BUT_1_PIN, GPIO_INTR_NEGEDGE);
  
  //configure button 2
  gpio_reset_pin(BUT_2_PIN);
  gpio_set_direction(BUT_2_PIN, GPIO_MODE_INPUT);

  gpio_pullup_en(BUT_2_PIN);
  gpio_pulldown_dis(BUT_2_PIN);

  gpio_set_intr_type(BUT_2_PIN, GPIO_INTR_NEGEDGE);


  //configure button 2
  gpio_reset_pin(BUT_3_PIN);
  gpio_set_direction(BUT_3_PIN, GPIO_MODE_INPUT);

  gpio_pullup_en(BUT_3_PIN);
  gpio_pulldown_dis(BUT_3_PIN);

  gpio_set_intr_type(BUT_3_PIN, GPIO_INTR_NEGEDGE);

  gpio_install_isr_service(0);


    //set callback functions for button interrupts
    gpio_isr_handler_add(BUT_1_PIN, gpio_isr_handler, (void *)BUTTON_1);
    gpio_isr_handler_add(BUT_2_PIN, gpio_isr_handler, (void *)BUTTON_2);
    gpio_isr_handler_add(BUT_3_PIN, gpio_isr_handler, (void *)BUTTON_3);

}

//button interrupt function
void IRAM_ATTR gpio_isr_handler(void* arg){
  ButtonEvent button_pressed = (ButtonEvent)(uintptr_t)arg;
  uint64_t now = esp_timer_get_time() / 1000;
  BaseType_t task_woken = pdFALSE;

  int button_idx = button_pressed - 1;  // Assuming BUTTON_1=1, BUTTON_2=2
  if(now - last_button_time[button_idx] < DEBOUNCE_TIME_MS) return;
  last_button_time[button_idx] = now;

}
