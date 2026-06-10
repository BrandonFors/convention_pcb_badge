#ifndef HAL_H
#define HAL_H

void hal_init();
void hal_register_gpio_callback(uint8_t pin, void *callback, void *args);

#endif /* HAL_H */