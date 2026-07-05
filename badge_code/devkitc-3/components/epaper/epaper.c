#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "board.h"
#include "epaper.h"
#include "hal.h"
#include "imgs.h"



#define DISPLAY_X 128
#define DISPLAY_Y 296
#define FRAME_BUF_SIZE (DISPLAY_Y*(DISPLAY_X >> 3))
/*************
 * Private Functions
 */
void epaper_send_cmd(uint8_t cmd);
void epaper_reset();
void epaper_wait_busy();
void epaper_refresh();
void epaper_load_custom_lut();



/******
 * Private Vars
 */

// Frame buffer x=128 y=296(8*32)
static unsigned char buffer[FRAME_BUF_SIZE] = {0};


/* LUT taken from East Rising example -> Probably a little faster refresh*/
// OTP LUT ~1.5 sec
// Custom LUT ~0.9 sec but leaves faded previous img
static unsigned char custom_lut[] = {
0xAA,	0x99,	0x10,	0x00,	0x00,	0x00,	0x00,	0x55,	0x99,	0x80,	0x00,	0x00,	0x00,	0x00,	0x8A,	0xA8,
0x9B,	0x00,	0x00,	0x00,	0x00,	0x8A,	0xA8,	0x9B,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,
0x00,	0x00,	0x00,	0x0F,	0x0F,	0x0F,	0x0F,	0x02,	0x14,	0x14,	0x14,	0x14,	0x06,	0x14,	0x14,	0x0C,
0x82,	0x08,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,
0x00,	0x00,	0x00,	0x00,	0x00,	0x00,		
};

void epaper_init(){
    hal_gpio_set(CS_PIN, HAL_GPIO_HIGH);
    hal_gpio_set(DC_PIN, HAL_GPIO_HIGH);
    hal_gpio_set(RET_PIN, HAL_GPIO_HIGH);
    // DEVICE FLOW

    // Wait ~10ms after power is supplied (should just happen auto)
    // HW and SW reset w/ cmd 0x12
    epaper_reset();
    //Wait ~10ms
    hal_delay_ms(10);
    // Set gate driver output w/ cmd 0x01
    // write the number of gate lines in hex
    hal_gpio_set(CS_PIN, HAL_GPIO_LOW);
    epaper_send_cmd(SSD_CMD_DOC);
    hal_spi_send_byte(0x27);
    hal_spi_send_byte(0x01);
    hal_spi_send_byte(0x00);
    hal_gpio_set(CS_PIN, HAL_GPIO_HIGH);

    // Set display RAM size w/ cmd 0x11, 0x44, 0x45
    // Set data entry mode settings
    hal_gpio_set(CS_PIN, HAL_GPIO_LOW);
    epaper_send_cmd(SSD_CMD_DE);
    hal_spi_send_byte(0x03);
    hal_gpio_set(CS_PIN, HAL_GPIO_HIGH);
    
    //Set ram x start and end positions (end is DISP_X/8)
    hal_gpio_set(CS_PIN, HAL_GPIO_LOW);
    epaper_send_cmd(SSD_CMD_RMSX);
    hal_spi_send_byte(0x00);
    hal_spi_send_byte(0x0F);
    hal_gpio_set(CS_PIN, HAL_GPIO_HIGH);

    //Set ram y start and end positions (end is DISP_Y)
    hal_gpio_set(CS_PIN, HAL_GPIO_LOW);
    epaper_send_cmd(SSD_CMD_RMSY);
    hal_spi_send_byte(0x00);
    hal_spi_send_byte(0x00);
    hal_spi_send_byte(0x27);
    hal_spi_send_byte(0x01);
    hal_gpio_set(CS_PIN, HAL_GPIO_HIGH);

    // Set panel border by cmd 0x3C
    hal_gpio_set(CS_PIN, HAL_GPIO_LOW);
    epaper_send_cmd(SSD_CMD_BWC);
    hal_spi_send_byte(0x05);
    hal_gpio_set(CS_PIN, HAL_GPIO_HIGH);
    // Tell SSD to skip red ram and invert black ram
    hal_gpio_set(CS_PIN, HAL_GPIO_LOW);
    epaper_send_cmd(SSD_CMD_DUC1);
    hal_spi_send_byte(0x40);
    hal_spi_send_byte(0x80); 
    hal_gpio_set(CS_PIN, HAL_GPIO_HIGH);
    // Sense temp w/ internal temp sensor w/ 0x18
    hal_gpio_set(CS_PIN, HAL_GPIO_LOW);
    epaper_send_cmd(SSD_CMD_TSS);
    hal_spi_send_byte(0x80);
    hal_gpio_set(CS_PIN, HAL_GPIO_HIGH);
    // Load waveform LUT from OTP w/ command 0x22, 0x20 or by MCU
    // Program the display to load temp and LUT
    epaper_load_custom_lut();

    hal_gpio_set(CS_PIN, HAL_GPIO_LOW);
    epaper_send_cmd(SSD_CMD_DUC2);
    hal_spi_send_byte(TEMP_LUT_1); 
    hal_gpio_set(CS_PIN, HAL_GPIO_HIGH);
    // Execute the programmed sequence
    hal_gpio_set(CS_PIN, HAL_GPIO_LOW);
    epaper_send_cmd(SSD_CMD_MA);
    hal_gpio_set(CS_PIN, HAL_GPIO_HIGH);
    // Wait until busy assert low
    epaper_wait_busy();
    // Write initial img data in RAM w/ 0x4E, 0x4F, 0x24, 0x26
    // Set softstart setting w/ 0x0C (POR looks good)
    // Drive display by 0x22, 0x20
    // Always wait until busy asseerts low

}

void epaper_send_cmd(uint8_t cmd){
    epaper_wait_busy();
    hal_gpio_set(DC_PIN, HAL_GPIO_LOW);
    hal_spi_send_byte(cmd);
    hal_gpio_set(DC_PIN, HAL_GPIO_HIGH);
}

//administer a hardware and software reset
void epaper_reset(){
    hal_delay_ms(200);
    hal_gpio_set(RET_PIN, HAL_GPIO_LOW);
    hal_delay_ms(200);
    hal_gpio_set(RET_PIN, HAL_GPIO_HIGH);
    hal_delay_ms(200);
    epaper_wait_busy();
    hal_gpio_set(CS_PIN, HAL_GPIO_LOW);
    epaper_send_cmd(SSD_CMD_RST);
    hal_gpio_set(CS_PIN, HAL_GPIO_HIGH);
    epaper_wait_busy();
}

void epaper_wait_busy(){
    while(hal_gpio_read(BUSY_PIN)) hal_delay_ms(2);
}

void epaper_write_bitmap(const unsigned char *bitmap){
    memset(buffer, 0, FRAME_BUF_SIZE*sizeof(char));
    for(int i = 0; i < FRAME_BUF_SIZE; i++){
        buffer[i] = bitmap[i];
    }
}

void epaper_push_frame(){
    epaper_wait_busy();
    //set starting x address
    hal_gpio_set(CS_PIN, HAL_GPIO_LOW);
    epaper_send_cmd(SSD_CMD_RMXC);
    hal_spi_send_byte(0x00);
    hal_gpio_set(CS_PIN, HAL_GPIO_HIGH);
    // set starting y address
    hal_gpio_set(CS_PIN, HAL_GPIO_LOW);
    epaper_send_cmd(SSD_CMD_RMYC);
    hal_spi_send_byte(0x00);
    hal_spi_send_byte(0x00);
    hal_gpio_set(CS_PIN, HAL_GPIO_HIGH);
    // write data to black ram
    hal_gpio_set(CS_PIN, HAL_GPIO_LOW);
    epaper_send_cmd(SSD_CMD_RMBW);
    for(int i = 0; i < FRAME_BUF_SIZE; i++){
        hal_spi_send_byte(buffer[i]);
    }
    hal_gpio_set(CS_PIN, HAL_GPIO_HIGH);
    epaper_refresh();
}

void epaper_refresh(){
    epaper_wait_busy();
    hal_gpio_set(CS_PIN, HAL_GPIO_LOW);
    epaper_send_cmd(SSD_CMD_DUC2);
    hal_spi_send_byte(DISP_1); 
    hal_gpio_set(CS_PIN, HAL_GPIO_HIGH);
    // Execute the programmed sequence
    hal_gpio_set(CS_PIN, HAL_GPIO_LOW);
    epaper_send_cmd(SSD_CMD_MA);
    hal_gpio_set(CS_PIN, HAL_GPIO_HIGH);
}

void epaper_load_custom_lut(){
    epaper_wait_busy();
    hal_gpio_set(CS_PIN, HAL_GPIO_LOW);
    epaper_send_cmd(SSD_CMD_LUTW);
    for(int i = 0; i < 70; i++){
        hal_spi_send_byte(custom_lut[i]);
    }
    hal_gpio_set(CS_PIN, HAL_GPIO_HIGH);

}

