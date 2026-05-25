# Convention Badge Project

## The Idea

We create a custom and interactive badge for conventions. The badge would have at least a display and a lipo power supply and some cool designs on the pcb. It would also probably have buttons for interactivity and other fun things.

- could have unpopulated vias for future modificaiton.

## Design

ESP32(C3?) microcontroller. PCB designed in KiCad. Programming done with espressif

ESPRESSIF has layouts of their breakout boards. We can copy and then modify a development board layout. 

## Display options

2.13 inch e-Paper Display Module: https://www.buydisplay.com/black-2-13-inch-e-paper-122x250-display-module-for-arduino-raspberry-pi
Datasheet: https://www.buydisplay.com/download/manual/ER-EPD0213-2-5076_Datasheet.pdf
UC8251 Controller: https://www.buydisplay.com/download/ic/UC8251.pdf

- is a breakout board and would be good for development on a breadboard. 
- has mounting holes that would be easy to use for the badge
- tutorial exists online for developing an entire display driver for this specific board.

2.6 inch e-Paper Display Pannel: https://www.buydisplay.com/2-6-inch-e-ink-152x296-e-paper-display-panel-red-white-black-spi
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