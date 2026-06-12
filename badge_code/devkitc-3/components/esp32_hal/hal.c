#include <stdint.h>
#include "board.h"

#include "driver/spi_master.h"
#include "driver/gpio.h"
#include "esp_err.h"
#include "esp_log.h"

#include "hal.h"

static const char *TAG = "HAL";

static spi_device_handle_t spi_handle;
static spi_bus_config_t spi_config;
static spi_transaction_t transaction;
static spi_device_interface_config_t spi_device_config;

static uint8_t spi_sendbuf;


//init spi device
//spi write 
//spi read


//init gpio button interrupt

void hal_init(){

    //configure SPI
    ESP_LOGI(TAG, "Initializing SPI");


    spi_config = (spi_bus_config_t){ //configure for spi communcation for led row
        .mosi_io_num = MOSI,
        .miso_io_num = -1,
        .sclk_io_num = SCLK,
    };

    spi_device_config = (spi_device_interface_config_t){
        .clock_speed_hz = 10000000, // MAX clock speed is 20MHz
        .mode = 0,
        .spics_io_num = -1, // handling CS manually (just connected to 5V on board)
        .queue_size = 1,
    };

    transaction = (spi_transaction_t){
        .length = 8,
        .tx_buffer = &spi_sendbuf,
        .rx_buffer = NULL,
    };
    
    ESP_ERROR_CHECK(spi_bus_initialize(SPI2_HOST, &spi_config, SPI_DMA_CH_AUTO));


    ESP_LOGI(TAG, "Initializing GPIO Pins");
    
    //configure spi related gpios
    gpio_set_direction(CS, GPIO_MODE_OUTPUT);
    gpio_set_direction(DC, GPIO_MODE_OUTPUT);
    gpio_set_direction(RET, GPIO_MODE_OUTPUT); 
    gpio_set_direction(BUSY, GPIO_MODE_INPUT);

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

void hal_gpio_register_callback(uint8_t pin, void *callback, void *args){
    //set callback functions for button interrupts
    gpio_isr_handler_add(pin, callback, args);
    gpio_intr_enable(pin);
}

void hal_gpio_set(uint8_t pin, hal_gpio_out_t output){
    gpio_set_level(pin, output);
}

uint8_t hal_gpio_read(uint8_t pin){
    return gpio_get_level(pin);
}

// could add a multiple byte function later once everything works
void hal_spi_send_byte(uint8_t byte){
    spi_sendbuf = byte;
    spi_device_transmit(spi_handle, &transaction);
}
