# Humidity sensor using ESP32C3 super mini and sht41
This project allows you to connect a sht41 and as esp32 c3 super mini module together to display room temp and humidity on the local internet. 
The esp runs a web server serving basic HTML to fetch the readings.
optionaly you can connect a battery via buck/booster so that the esp doesn't get cooked.

## How to run?
what you need:
SHT41 and an ESPC3 Super mini
to run this you have to have the following installed:
Arduino IDE and the Adafruit SHT4x library
You also need to have the board manager URL confgured for all of the esp32 boards

### Running it
Please slect the Makergo mini board 
Wire the the sht to esp followingly:
SHT       ESP
vin -> 3.3V
gnd -> gnd
sda -> 4
scl -> 5
(for battery put the gnd and vin along the out - and out +)

ther copy the main.ino code and setup wifi name and password
once you have done that upload it to the board and open serial monitor. 
Please wait until it connects to the wifi. it will show you and IP which you can visit. from there you can fetch the readings
