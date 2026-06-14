#ifndef EPAPER_H
#define EPAPER_H

/*********************
 * Commands
 * Each of these commands should be written with DC
 * asserted low, then asserted high when writing/reading 
 * the following necessary data
 */
#define SSD_CMD_DOC  0x01
#define SSD_CMD_GVC  0x03
#define SSD_CMD_SVC  0x04
#define SSD_CMD_ICSP 0x08
#define SSD_CMD_ICSW 0x09
#define SSD_CMD_ICSR 0x0A
#define SSD_CMD_BSC  0x0C
#define SSD_CMD_DS   0x10
#define SSD_CMD_DE   0x11
#define SSD_CMD_RST  0x12
#define SSD_CMD_HVR  0x14
#define SSD_CMD_VCID 0x15
#define SSD_CMD_TSS  0x18
#define SSD_CMD_TSWI 0x1A
#define SSD_CMD_TSRI 0x1B
#define SSD_CMD_TSWE 0x1C
#define SSD_CMD_MA   0x20
#define SSD_CMD_DUC1 0x21
#define SSD_CMD_DUC2 0x22
#define SSD_CMD_RMBW 0x24
#define SSD_CMD_RMRW 0x26
#define SSD_CMD_RMR  0x27
#define SSD_CMD_VMS  0x28
#define SSD_CMD_VMSD 0x29
#define SSD_CMD_VMPO 0x2A
#define SSD_CMD_VMCW 0x2B
#define SSD_CMD_VMW  0x2C
#define SSD_CMD_OTPR 0x2D
#define SSD_CMD_UIDR 0x2E
#define SSD_CMD_STR  0x2F
#define SSD_CMD_WSOP 0x30
#define SSD_CMD_WSOL 0x31
#define SSD_CMD_LUTW 0x32
#define SSD_CMD_CRCC 0x34
#define SSD_CMD_CRCR 0x34
#define SSD_CMD_OTPP 0x36 
#define SSD_CMD_DSOW 0x37
#define SSD_CMD_UIDW 0x38
#define SSD_CMD_OTPM 0x39
#define SSD_CMD_BWC  0x3C
#define SSD_CMD_EO   0x3F
#define SSD_CMD_RMRO 0x41
#define SSD_CMD_RMSX 0x44
#define SSD_CMD_RMSY 0x45
#define SSD_CMD_RMRA 0x46
#define SSD_CMD_RMBA 0x47
#define SSD_CMD_RMXC 0x4E
#define SSD_CMD_RMYC 0x4F
#define SSD_CMD_NOP  0x7F


/*****
 * Display Update Control 2 Options
 * Please refer to SSD1680 for detailed descriptions
 */
#define CLK_EN  0x80
#define CLK_DIS 0x01
#define CLK_AN_EN 0xC0
#define CLK_AN_DIS 0x03
#define LUT_1 0x91
#define LUT_2 0x99
#define TEMP_LUT_1 0xB1
#define TEMP_LUT_2 0xB9
#define DISP_1 0xC7
#define DISP_2 0xCF
#define TEMP_DISP_1 0xF7
#define TEMP_DISP_2 0xFF



void epaper_init();
void epaper_write_bitmap(const unsigned char *bitmap);
void epaper_push_frame();

#endif