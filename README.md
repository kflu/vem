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

### 9v Battery

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
* After 9201s (153min): vol=, 5vin temperature reading: 56C

![Temerature and SNR over time][2]

From the chart it can be seen that temerature is well maintained constant over
most of the battery life, but only raised up (due to low voltage) at the end of
it. SNR is maintained over entire battery life and cut off when power is not
sufficient.

For 9v 300mAH, current expected battery life is

    300 / (90 + 200/5) = 2.3hour

(90mA + 200mA/5) is the average current draw. 200mA transmission mode occurs every 5 sec.

This aligns well with the experiment. Now if we put it to sleep during the 5 sec wait, expected
battery life is

    300 / (200/5) = 7.5hour


**Test3**: Anker PowerCore+ mini

**Test4**: Constant from car battery

**Test5**: All above with IRQ sleep&wake


[1]: http://blog.gopetfriendly.com/is-it-illegal-to-leave-your-pet-alone-in-the-car/
[2]: doc/temperature_time.png
