//
// Created by liosha on 04.01.2022.
//

#ifndef AIR_QUALITY_CLOCK_MAIN_H
#define AIR_QUALITY_CLOCK_MAIN_H

#include <Arduino.h>
//#include <avr/power.h>
#include "../lib/GyverButton/GyverButton.h"
#include "Constants.h"
#include "BME280.h"
#include "MHZ19.h"
#include "MP503.h"
#include "CCS811.h"
#include "Buttery.h"
#include "TripleLed.h"
#include "Screen.h"

void updateDateTime(bool);

#endif //AIR_QUALITY_CLOCK_MAIN_H
