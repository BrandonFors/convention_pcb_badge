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

static const char *TAG = "MAIN";

static const unsigned char *bitmap_arr[] = {irishsat_bitmap, gImage};
static uint8_t bitmap_idx = 0;

void app_main(void)
{
    hal_init();
    buttons_init();
    epaper_init();




    while(1){
        ESP_LOGI(TAG, "Writing and Pushing Bitmap");
        epaper_write_bitmap(bitmap_arr[bitmap_idx++]);
        bitmap_idx %= NUM_BITMAPS;
        epaper_push_frame();
        ESP_LOGI(TAG, "Spinning");
        hal_delay_ms(5000);
    };
}