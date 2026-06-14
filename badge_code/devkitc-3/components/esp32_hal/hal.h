#ifndef HAL_H
#define HAL_H
#include <stdint.h>

typedef enum {
    HAL_GPIO_LOW = 0,
    HAL_GPIO_HIGH = 1
}hal_gpio_out_t;

#define SPI_SPEED 10000000

void hal_init();

//General
void hal_delay_us(uint32_t us);
void hal_delay_ms(uint32_t ms);

//GPIO
void hal_gpio_set(uint8_t pin, hal_gpio_out_t output);
uint8_t hal_gpio_read(uint8_t pin);
void hal_gpio_register_callback(uint8_t pin, void *callback, void *args);

//SPI
void hal_spi_send_byte(uint8_t byte);

#endif /* HAL_H */