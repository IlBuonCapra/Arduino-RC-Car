# Arduino - RC Car
Arduino RC Car with nRF20L01 module, controlled by Syma X5C remote controller.
I used **[Symaxrx Library]**(https://github.com/Suxsem/symaxrx) to control the car with Syma X5C remote controller.

##PCB
I also created my personal shield for this projects using Eagle PCB.
Everything works with 12 volts from a battery packs made of six 18650 batteries.

A L298 Dual Full Bridge Driver is used to drive motors in each directions.
L298's enables are connected to 5 volts, so the motors are always ready to work.
If you want, you can short-circuit resistors R1,R2.
Unfortunaly, the steering motor is not controlled with PWM due to the reduced number of PWM pins of Arduino, but the car steers well.

12 volts leds are used like lights and a buzzer is used like clacson.

For this shield, i used the following pins:
| PIN | Function |
| --- | --- |
| 3 | CLACSON |
| 4 | LIGHTS |
| 5 | MOTOR1 |
| 6 | MOTOR2 |
| 7 | STEERING1 |
| 8 | STEERING2 |
| 9 | NRF_CE |
| 10 | NRF_CSN |
| 11 | NRF_MOSI |
| 12 | NRF_MISO |
| 13 | NRF_SCK |
