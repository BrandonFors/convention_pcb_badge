#include <stdio.h>

//espidf drivers
#include "esp_err.h"
#include "esp_log.h"
#include "driver/gpio.h"
#include "esp_timer.h"
#include "driver/gptimer.h"

//Custom
#include "board.h"
#include "hal.h"
#include "buttons.h"
#include "epaper.h"
#include "imgs.h"



#define NUM_BITMAPS 2
#define BETWEEN_SLIDES_MS 5000
#define BETWEEN_BLINKS_MS 1000

static const char *TAG = "MAIN";

static const unsigned char *bitmap_arr[] = {irishsat_bitmap, gImage};
volatile uint8_t bitmap_idx = 0;
volatile uint8_t button_flag = 0;
static uint32_t curr_time = 0;
volatile uint32_t last_time = 0;
static uint32_t last_led_time = 0;
static uint8_t led_state = HAL_GPIO_LOW;


void slide_hold(){
    last_time = hal_get_time_ms();
}

void slide_forward(){
    button_flag = 1;
    bitmap_idx++;
    bitmap_idx %= NUM_BITMAPS;
}

void slide_backward(){
    button_flag = 1;
    if(bitmap_idx == 0){
        bitmap_idx = NUM_BITMAPS - 1;
        return;
    }
    bitmap_idx--;
}


void app_main(void)
{
    hal_init();
    buttons_init();
    epaper_init();
    hal_gpio_set(RED_LED_PIN, HAL_GPIO_HIGH);


    while(1){
        curr_time = hal_get_time_ms();
        if(curr_time > last_led_time + BETWEEN_BLINKS_MS){
            led_state = !led_state;
            hal_gpio_set(YEL_LED_PIN, led_state);
            last_led_time = curr_time;
        }
        if(button_flag){
            epaper_write_bitmap(bitmap_arr[bitmap_idx]);
            epaper_push_frame();
            last_time = curr_time;
            button_flag = 0;
        }
        if (curr_time > last_time + BETWEEN_SLIDES_MS){
            ESP_LOGI(TAG, "Writing and Pushing Bitmap");
            epaper_write_bitmap(bitmap_arr[bitmap_idx++]);
            bitmap_idx %= NUM_BITMAPS;
            epaper_push_frame();
            last_time = curr_time;
        }



        ESP_LOGI(TAG, "Spinning");
        hal_delay_ms(100);
    };
}