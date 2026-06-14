So you wanna make a pcb huh? Well you've come to the (probably wrong but) right place ;)

Here's my initial notes after looking at it for like 5 minutes

Your traces are all the same width, which isn't necessarily bad, but I'm worried about the 3.7V trace. Typically power lines have wider traces because they need to be able to supply the required current. Wider trace = more current capacity. It would be worth looking into  the nominal current draw of whatever you are supplying power to, and then using KiCad's trace width calculator in the project menu (very useful things underneath 'calculator tools') to calculate the minimum width of trace you need

The JST you are using for the battery is in the middle of the board. Fair play if that's what you want, but it'll probably be pretty annoying trying to connect to it. Typically all peripheral connectors are placed as close as possible to the edge of the board and facing out so it is a lot easier to access them (except perhaps for pin headers, but even then they tend to be on the outskirts of the board so they don't interfere with trace layout. In general, the layout for your power system is a but overly complex, and with a few small adjustments of component placement, the layout will be simpler and much more user friendly.

I'm unsure what the purpose of the solder jumper to GND for the battery is (I'm too lazy to check the datasheet of what you are messing with). If the purpose is to add an additional resistor to ground to make a voltage divider, I would suggest just via to GND right at the battery, via to GND close to the GND pad of the resistor and solder jumper from the other pad of the resistor to the voltage divider connection. That saves you from the long trace from the solder jumper to the battery, and in general its standard practice to place GND as close as possible to the pad to reduce the current return path (I don't really understand the physics but everything I see says to reduce the length of the return path as much as possible) Since you are working with low frequency I assume, it probably isn't an issue, but better safe then sorry.

You may be able to mess around with the placement and orientation of the Xiao thingie and your pin header connector to reduce via use. It probably isn't a big deal, but I at least try not to use vias whenever possible. But, if it's unavoidable its not a super big deal for your application

It shouldn't be a huge deal, but try to keep the power lines as far away as possible from the I2C lines. Power lines create larger magnetic fields (more current = more magnetic field intensity) and that can potentially corrupt your data as it is transmitted. Since it's only 3.7V and your lines are really short it shouldn't be a major major issue, but I would look into it to see how big of a problem it will be and just give it some space at least

Finally, your traces a just a bit messy. There's no reason not to use straight lines where applicable (For example, the two resistors can very easily be shifted so that there isn't a little hitch in the trace). Also, you have a weird little hanging trace on the connection to the 3rd button that can be cleaned up

Overall there'd definitely some things to touch up, but overall not too shabby! My biggest advice is to just mess around with component placement so that it 1. Makes sense for the user 2. Doesn't interfere with trace paths (especially for through hole components) *This doesn't apply too much to this board, but is good advice in general* 3. Allows for the simplest trace pathway

You have plenty of space on the board to play around with so don't be scared to try different setups!

LMK if you need any more help, I'm happy to give my thoughts whenever you need :)