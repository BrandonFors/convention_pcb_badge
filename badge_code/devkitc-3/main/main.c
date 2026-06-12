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


static const char *TAG = "MAIN";

void app_main(void)
{
    hal_init();
    buttons_init();
    epaper_init();


    while(1){
        ESP_LOGI(TAG, "In forever");
    };
}