# Vehicle Environment Monitor (VEM)

I created this project to remotely monitor temperature in my car when I bring
my dog on a trip and have to leave him tempororaly in the car. This gives me
a piece of mind knowing that the temperature is good for him to comfortably 
stay in the car.

**NOTE** [Here][1] cites the laws in different states that prohibits leaving
animal in motor vehicle in cirtain situations. 

# Range Tests

* 915MHz
* Tx Power: 23dBm
* Modem config: Bw125Cr48Sf4096: Bw = 125 kHz, Cr = 4/8, Sf = 4096chips/symbol,
  CRC on.
* Wire antenna at quarter wavelength

**Test1**

Tx: Sammamish Metropolitan parking lot (upper)
Rx: Sammamish Metropolitan cafe
Min SNR: -13dB


**Test2**

Tx: Sammamish City Hall parking lot
Rx: Sammamish Library underground parking lot
Min SNR: -4dB


# Battery Tests

## Tx Side

**Problem with 9V**: voltage slowly goes down making temperature reading
gradually goes up.

Measured tx side power consumption from 9v:

* 90mA non-transmission mode
* 215mA transmission mode


**Test1**: 9v battery (used)

9V battery, almost new, after 70+ minutes, the 5V regulated Vin measured only 3.0V. 
Battery itself was measured only 4.3V. Not good.

The dropped voltage caused the measured temperature to be misinterpreted and
went up from 19C to incorrectly 62C.


**Test2**: 9v battery (new)

* 9V battery
* Initial: vol=9.46v, 5vin=? temperature reading: 17C
* After 3507s (58min): vol=7.5v, 5vin=5v temperature reading: 20C
* After 5409s (90min): vol=7.3v, 5vin=5.06v temperature reading: 19C


**Test3**: Anker PowerCore+ mini

**Test4**: Constant from car battery

**Test5**: All above with IRQ sleep&wake


[1]: http://blog.gopetfriendly.com/is-it-illegal-to-leave-your-pet-alone-in-the-car/
