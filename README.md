
# RCChannel Library
A library to decode PWM RC signals

## Usage
The RCChannel library is for use with Remote Control systems which have a connector similar to a servo connector:
```|S|+|-|``` 
Where 'S' is signal, '+' is VCC (usually 5V), and '-' is ground.

The signal pin must produce a PWM signal and be connected to an interrupt-capable digital pin. For a table of interrupt-capable pins, refer to https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/
## Installation
Start the Ardiono software and select Sketch->Include Library ->Add ZIP library and select the ZIP file containing the RCChannel library. 
## Code
See the [Wiki on GitHub](https://github.com/foliagecanine/rcchannel/wiki) for documentation.
Examples are provided. To open them, start the Arduino software and select File->Examples->RCChannel for a list of examples.  
It is recommended to start with the BasicRC example to learn how to calibrate your receiver.
## License
See LICENSE for license information.
