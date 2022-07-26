//
// Created by liosha on 03.01.2022.
//

#ifndef AIR_QUALITY_CLOCK_CONSTANTS_H
#define AIR_QUALITY_CLOCK_CONSTANTS_H

// SEN-CCS811 Air 1.8-3.6v (30mA)

// 1.8 128x160 rgb _tft lcd 3.3v

// SCK is fixed - D13
// SDA is fixed - D11
// CS  is defined in User_Setup.h, default is A2
// DC  is defined in User_Setup.h, default is A1
// RST is defined in User_Setup.h, default is RST

// DS3231 Clock 2.3-5.5v

// MP503 Gas sensor 5v, 3.3v?
#define MP503_A 8
#define MP503_B 7

// BMP/BME280 Humidity 1.7-3.6v

// MH-Z19B CO2 3.3-5.5v (average 60mA)
#define MHZ19B_TX 3
#define MHZ19B_RX 4

#define BUTTON_FRONT A3
#define BEEPER A0

#define JOYSTICK_1 12
#define JOYSTICK_2 2
#define JOYSTICK_3 6

#define LED_RED 5 // Not connected???
#define LED_GREEN 9 // Not connected???
#define LED_BLUE 10

#define PIN_BUTTERY_LEVEL A7

#endif //AIR_QUALITY_CLOCK_CONSTANTS_H
