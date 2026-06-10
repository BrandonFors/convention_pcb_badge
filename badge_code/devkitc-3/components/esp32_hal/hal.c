#include <stdint.h>
#include "board.h"

#include "driver/gpio.h"

//init spi device
//spi write 
//spi read


//init gpio button interrupt

void hal_init(){

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

    //configure button 3
    gpio_reset_pin(BUT_3_PIN);
    gpio_set_direction(BUT_3_PIN, GPIO_MODE_INPUT);

    gpio_pullup_en(BUT_3_PIN);
    gpio_pulldown_dis(BUT_3_PIN);

    gpio_set_intr_type(BUT_3_PIN, GPIO_INTR_NEGEDGE);

    gpio_install_isr_service(0);

}

void hal_register_gpio_callback(uint8_t pin, void *callback, void *args){
    //set callback functions for button interrupts
    gpio_isr_handler_add(pin, callback, args);
}
