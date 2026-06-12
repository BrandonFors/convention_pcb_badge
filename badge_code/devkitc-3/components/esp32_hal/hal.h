#ifndef HAL_H
#define HAL_H
#include <stdint.h>

typedef enum {
    HAL_GPIO_LOW = 0,
    HAL_GPIO_HIGH = 1
}hal_gpio_out_t;

void hal_init();

//GPIO
void hal_gpio_register_callback(uint8_t pin, void *callback, void *args);

//SPI
void hal_spi_send_byte(uint8_t byte);

#endif /* HAL_H */