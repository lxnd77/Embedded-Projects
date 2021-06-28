# Embedded Projects 

## ServoRun

### Automatic cup dispenser on coin acceptance
Arduino recieves input from coin acceptor and initiates a servo rotation of 90 degrees and back.
The servo is connected to a star attachment with a metal rod on one of the star points. The metal rod is attached to a Button on a plastic cup dispenser.
On recieving a 1 Ruppee coin, the machine spits out one cup onto a holder. The machine is tamper proof.

![Diagram](https://i.imgur.com/DlkLw3O.png)


## WaterQualityProject

### Output PH and TDS values to a screen

PH, TDS, Water Level, and temperature sensors attached to an Arduino sending Serial output to a Raspberry Pi Zero which is running a Python program using Tkinter to display the sensor readings. The Arduino and sensor controller boards are housed in a 5'x7'x3' plastic box. The Raspberry Pi is housed in a small plastic box. All wires are soldered and sheathed. 

The main.py file in the Pi is scheduled to start itself on machine boot, look for the serial USB connection to the Arduino and start displaying data. Startup takes around 30 seconds - 1 minute.

Known Issues:   The SD Card will need to be replaced in around 1 - 2 years of continuous usage.
                The PH Sensor I have used is not meant for continuous usage and will have to be replaced.

Please contact me if you need the BOQ, Pictures, Raspberry Pi Image etc.

![Diagram](https://i.imgur.com/5CHoJl5.png)

