# Convention Badge Project

## The Idea

To create a custom and interactive badge for conventions. The badge would have at least a display and a lipo power supply and some cool designs on the pcb. It would also probably have buttons for interactivity and other fun things.

## Design

ESP32C3 microcontroller. PCB designed in KiCad. Programming done with espressif

### V1

This design features a basic form factor supporting the XIAO esp32c3 devboard along with a 2.9 inch display module. The design was never actually manufactured.

### V2

The V2 board was designed to serve as both a badge and a dev board. It hosts the esp32c3, has support for USB power and flashing, has a battery managment circuit, and various peripherals. The display circuitry still lies on a breakout board which is attached through header pins. It is designed to resemble a satelite.

This design experience was particularly new/challenging because it was the first PCB design I made where I had to consider how parts and integrated circuits interact rather than wiring pin headers together. I also had to consider manufacturing requirements, part availability, and cost.

After manufacturing this board through JLCPCB, I was able to flash the ESP32C3 over USBC and get my display, buttons, and leds working. However, there were a few mistakes within the battery managment circuit that made LiPo power unusable for this version. I was able to fix one to get battery charging working, but a misconfigured mosfet connection made powering the uC with the battery impossible without some reworking which I don't have the tools for. 

Code at this stage is pretty scrappy as the main focus was on PCB design and just getting a prototype working.

Overall, I consider this version great progress and a great step towards improving my PCB design skills. Even though the main complexity of the battery managment circuitry doesn't work, I know what to fix in my next revision. This was my first project where programming wasn't really the main focus and I feel that I have a solid understanding of what to expect the design process to look like in my next KiCad project. 

## KiCad

All relevant kicad files can be found in `convention_badge_kicad`. We'll probably start by designing a basic board that would just serve as a platform for the esp32-c3 xiao and an e-paper breakoutboard with pin headers. After that, we can scale up complexity and embed the uC on the pcb badge and choose whether or not to design the badge with an FCC connection. 

One reference we are using is Notre Dame's build-a-board workshop pcb design which features a working esp32-c3 breakout board design.

Build-A-Board Credits: https://engineering.nd.edu/news/electrical-engineering-students-create-circuit-boards-in-inaugural-build-a-board-workshop/



# Design Notes

Everything below here is scattered notes from my dev process.


## Display options

### ESP32C3
Datasheet (contains schematics): https://documentation.espressif.com/esp32-c3-wroom-02_datasheet_en.pdf

- could go with xiao module as a backup
- could break out all available gpios to exposed vias to double as a breakout board for future use

### 2.13 inch e-Paper Display Module

 https://www.buydisplay.com/black-2-13-inch-e-paper-122x250-display-module-for-arduino-raspberry-pi

Datasheet: https://www.buydisplay.com/download/manual/ER-EPD0213-2-5076_Datasheet.pdf

UC8251 Controller: https://www.buydisplay.com/download/ic/UC8251.pdf

- is a breakout board and would be good for development on a breadboard. 
- has mounting holes that would be easy to use for the badge
- tutorial exists online for developing an entire display driver for this specific board.

The raw pannel: https://www.buydisplay.com/graphic-2-13-inch-122x250-electronic-paper-display-manufacturers

### 2.9 inch e-Paper Display Module

* probably the best considering size and scalability

https://www.buydisplay.com/black-2-9-inch-e-paper-display-module-for-arduino-raspberry-pi#

Datasheet: https://www.buydisplay.com/download/manual/ER-EPD029-2-5073_Datasheet.pdf

SSD1680 Controller: https://www.buydisplay.com/download/ic/SSD1680.pdf

- development board that is slightly larger and probably better for display purposes
- option for a breakout board and raw board if we decide to integrate pannel regulation into badge

The raw pannel: https://www.buydisplay.com/serial-2-9-inch-e-paper-screen-128x296-for-electronic-shelf-label-lcd


### 2.6 inch e-Paper Display Pannel

https://www.buydisplay.com/2-6-inch-e-ink-152x296-e-paper-display-panel-red-white-black-spi

Datasheet: https://www.buydisplay.com/download/manual/ER-EPD026A1-1_Datasheet.pdf

SSD1675A Controller: https://www.buydisplay.com/download/ic/SSD1675A.pdf

FCC Cable: https://www.buydisplay.com/download/connector/ER-CON24HT-1.pdf


- doesn't have breakout board 
- slightly larger
- requires 24 pin fcc ribbon cable and a connector

## Manufacturing

Most likely JLCPCB

Will likely have to pay for at least partial assembly. 

## Price Estimate

Claude session resulted in price estimate of ~$32 per board including assembly and shipping on an order of 5.

To minimize price, we can design a one sided board (the back) and hand solder buttons and attach the scren on the front. I don't think that prevents solder mask designs on the front. 

## Design Notes

### PCB_BadgeV1

This board will utilize the XIAO ESP32 C3 and an 2.9 inch e-Paper Display Module for functionality. Both will be soldered to the badge using header pins. A 3.7V lipo battery will be soldered to the underside of the xiao module as I don't have a way to solder the pads directly to the badge board. The board will also have some buttons on remaining usable gpio pins. 

This board is largely complete and contains support for a 2.9 inch epaper breakout and and esp32 c3 xiao soldered to the board using male header pins. One pin is wired to a voltage divider for battery power readings. The board also has support for 3 standard 6mm buttons which use internal pull up resistors on the esp32-c3. Footprints are mostly for through hole breadboard components purely because I am not space constrained and wanted to design the board for components that I already had on hand to avoid shipping/assembly costs.

The odds are that this board is never manufactured just because the next one will feature more peripherals as it won't be constrained by the pinout of the xiao. V2 will support the esp32-c3 directly on the pcb, based largely on the Build-A-Board pcb mentioned above.

Note: This board does not have decoupling capacitors between the e paper display and the 3.3V xiao supply.

#### Notable Resources

XIAO Getting Started: https://wiki.seeedstudio.com/XIAO_ESP32C3_Getting_Started/

Display Datasheet: Datasheet: https://www.buydisplay.com/download/manual/ER-EPD029-2-5073_Datasheet.pdf

### PCB_BadgeV2

This board will be 4 layers with support for the esp32-c3 directly on the pcb. Whether or not the board supports the e-paper display directly with no breakout is TBD. I might opt for a hybrid board that supports both the breakout board and the raw screen with solder bridges to enable/disable either set of connections. 

Section 13 of the SSD1680 Datasheet has a diagram of exactly what the 24 pin connector should be wired to.

10k PU with a 1uF capacitor on the EN line creates a RC time constant of 10ms, allowing EN to stay low on to 3.3V stabalizes so the chip boots properly.

I need some way to handle the battery managment of this design. I think I might need a battery charging IC.

Need to make sure that parts are in stock in jlcpcb

https://jlcpcb.com/parts

Going to create a charging/bms circuit using:
- TP4056
- DW10A
- FS8205A

Then I can use TLV75733P for voltage regulation and hook everything to the output 3.3V from there.

Added breakout pins for debugging purposes

Main section is 54 tall and 90 wide -> top and bottom pannels can be 19 tall w/ 3mm gaps between board and pannels

Hex design is 17.5mm tall and 88.1 mm wide

### Code Development

Notable E-Paper Sections:
- 9: Operation Flow 
- 8: Command Description
- 12.1: Timing table and diagram

Using EastRising's example code and the SD1680 documentation, I've got a working program that prints out an example image onto the screen. The display is electronically configured to be used vertically, but horizontal use is easily fixed with some clever frame buffer software. I'm just going to make it cycle through preconfigured bitmaps with the buttons to control the cycle.

Bitmap Img Converter: https://javl.github.io/image2cpp/

LUT Experiment Notes:
Refresh by default is pretty slow at 1.5 sec
- May be able to cut down with custom lut -> tradeoff is quality bc OTP lut does a full cycle on all pixels to fully clear them
Custom lut provided by east rising results in 0.9 sec refresh but leaves a faded img of the previous frame

In the future I can diff two frame buffers to find the changed pixels/sections and then use the xram and yram start/end points to selectively update the screen to avoid some of the anoying refresh.