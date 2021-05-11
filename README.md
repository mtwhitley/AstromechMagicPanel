# Astromech Magic Panel (AMP)

This project enables the building of LED Magic Panels for Astromech (R2-D2) droids. For more information on building your own droid, visit [Astromech.net](https://www.astromech.net)

## About
This version of the AMP cycles through 8 predefined color pallets at 30 second intervals. The brightness pulses. The colors, intervals, sequences, speed, and density are all configurable. 

The default color sequence is:

 - Red, *\<Off\>*
 - Red with hints of Blue
 - Blue, *\<Off\>*
 - Red with hints of White
 - White, *\<Off\>* 
 - Blue with hints of White
 - Blue, *\<Off\>*
 - Rainbow, *\<Off\>*

If you are interested in purchasing a prebuilt unit, please DM me on [Instagram](https://www.instagram.com/mw.labs/) or send me a message in the [Astromech forums](https://astromech.net/forums/member.php?46338-umlungu).

## Videos

Click the image to view the video on Youtube.

Rainbow Animation

[<img src="https://raw.githubusercontent.com/mtwhitley/AstromechMagicPanel/main/photos/Rainbow.png" height="300">](https://www.youtube.com/watch?v=29eVVwuxKLU)

Red and Blue Animations

[<img src="https://raw.githubusercontent.com/mtwhitley/AstromechMagicPanel/main/photos/RedAndBlue.png" height="300">](https://www.youtube.com/watch?v=H4pSufZo-co)

Horizontal & Vertical Lenses Compared

[<img src="https://raw.githubusercontent.com/mtwhitley/AstromechMagicPanel/main/photos/LensesCompared.png" height="300">](https://www.youtube.com/watch?v=DCI3bl-R6VM)


## Getting Started

To build the Astromech Magic Panel (AMP) you will need the following hardware:

 - 1 x [Adafruit QT Py (SAMD21)](https://www.adafruit.com/product/4600)
 - 2 x [Adafruit DotStar 8x8 Grid](https://www.adafruit.com/product/3444) or [SparkFun LuMini LED Matrix - 8x8](https://www.sparkfun.com/products/15047) The Adafruit Matrix is more densely packed but the Sparkfun Matrix is easier to solder
 - 8 x M2, 6mm screws (Adafruit) or 8 x M3, 6mm screws (Sparkfun)
 - 8 x F/F jumper wires (Adafruit) or 4 x F/F jumper wires (Sparkfun)
 - USB Type-C Cable supporting both Data and Power 
 - Soldering Iron and Solder
 - The [Arduino IDE](https://www.arduino.cc/en/software)
 - The ability to print the included mounting brackets

Here are the components prior to assembly

**Sparkfun LuMini**

<img src="https://raw.githubusercontent.com/mtwhitley/AstromechMagicPanel/main/photos/IMG_5275.jpeg" width="500">

**Adafruit Dotstar**

<img src="https://raw.githubusercontent.com/mtwhitley/AstromechMagicPanel/main/photos/IMG_5276.jpeg" width="500">

**Note:** You will also need a semi-transparent Magic Panel. If 3D printing this panel I recommend printing the panel *vertically* using a clear PETG filament. I used 6 perimeters/shells with 10% gyroid infill. Fewer perimeters and less infill will result in poorer LED diffusion. I recommend using the Panel 7 STL from [Michael Baddeley](https://www.patreon.com/mrbaddeley/overview).  

### Step 1: Solder 
First, solder the straight header pins to the Adafruit QT Py facing up.
<img src="https://raw.githubusercontent.com/mtwhitley/AstromechMagicPanel/main/photos/IMG_5284.jpeg" width="500">

Next, solder two wires to the power pads on the opposite side of the QT Py.
<img src="https://raw.githubusercontent.com/mtwhitley/AstromechMagicPanel/main/photos/IMG_5285.jpeg" width="500">

***Sparkfun Instructions***

Next, solder the 5V, CO-CI, DO-DI, and GND pads together on a flat surface. Also place a bit of solder on the remaining 5V, CI, DI, and GND pads on the top board.

<img src="https://raw.githubusercontent.com/mtwhitley/AstromechMagicPanel/main/photos/IMG_5280.jpeg" width="500">

Next, spread the pins of the right angle headers apart slightly and solder them to the 5V, CI, DI, and GND pads on the top board.
<img src="https://raw.githubusercontent.com/mtwhitley/AstromechMagicPanel/main/photos/IMG_5281.jpeg" width="500">

***Adafruit Instructions***

Next, solder the capacitors supplied with the matrices to the boards. Be sure to solder the + and - capacitor leads to the corresponding pads on the board. Once soldered trim the leads. Also place a bit of solder on the CIN, DIN, GND, and +5V pads. Do the same for the +5V, GND, DOUT, and COUT pads on one of the boards.

<img src="https://raw.githubusercontent.com/mtwhitley/AstromechMagicPanel/main/photos/IMG_5282.jpeg" width="500">

Next, solder the right angle headers to the pads prepared in the step above. Note that with the Adafruit board the right angle headers do not need to be spread apart.

<img src="https://raw.githubusercontent.com/mtwhitley/AstromechMagicPanel/main/photos/IMG_5288.jpeg" width="500">

### Step 2: Program
Using a USB C cable, a computer, and the [Arduino IDE](https://www.arduino.cc/en/software), connect the QT Py microcontroller and upload the *AstromechMagicPanel.ino* sketch found in the *src* directory.

### Step 3: 3D Print
Print the QT Py and Base mounting brackets found in the models folder. Only print the base model corresponding to the LED matrix you are using.

Print the Magic Panel *vertically* (standing on the shorter side) using clear PETG filament. I used 6 perimeters/shells with 10% gyroid infill. Fewer perimeters and less infill will result in poorer LED diffusion. I recommend using "Panel 7" model from [Michael Baddeley's](https://www.patreon.com/mrbaddeley/overview) project.  The light is diffused perpendicular to the print layer direction.

### Step 4: Assemble
Next, use CA glue to attach the QT Py bracket to the base.

<img src="https://raw.githubusercontent.com/mtwhitley/AstromechMagicPanel/main/photos/IMG_5286.jpeg" width="500">

Next, screw the LED panels into the bracket.

<img src="https://raw.githubusercontent.com/mtwhitley/AstromechMagicPanel/main/photos/IMG_5287.jpeg" width="500">

Then connect the QT Py to the LED panels using the female jumper wires.
<img src="https://raw.githubusercontent.com/mtwhitley/AstromechMagicPanel/main/photos/IMG_5309.jpeg" width="500">

<img src="https://raw.githubusercontent.com/mtwhitley/AstromechMagicPanel/main/photos/IMG_5314.jpeg" width="500">

## More Help
For additional assistance please contact Michael Whitley (umlungu) on the Astromech.net forums.

