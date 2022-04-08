
//#include <avr/power.h>

#include "main.h"

TripleLed led = TripleLed(LED_RED, LED_GREEN, LED_BLUE);

Screen screen = Screen(LCD_BRIGHTNESS, PHOTO_RESISTOR); // Screen brightness and photo resistor

GButton btn(BUTTON_FRONT, LOW_PULL); // Front button

GButton btnPrev(JOYSTICK_1, HIGH_PULL); // Joystick left
GButton btnNext(JOYSTICK_2, HIGH_PULL); // Joystick right
GButton btnSlct(JOYSTICK_3, HIGH_PULL); // Joystick center

// region CO2
#include <MHZ19_uart.h>
MHZ19_uart mhz19;
// endregion

// region Temperature, humidity and pressure
#include <Adafruit_BME280.h>
#define SEALEVELPRESSURE_HPA (1013.25)
Adafruit_BME280 bme;
// endregion

// region Time
#include <RTClib.h>
RTC_DS3231 rtc;
// TO UPDATE TIME, change to 1, push to Arduino, change back to 0 and repush
#define RESET_CLOCK 0
// endregion

// region Air quality
#include "MP503.h"
MP503 mp503 = MP503(MP503_A, MP503_B);
// endregion

void setup() {
//    clock_prescale_set(clock_div_16); // Change frequency

    Serial.begin(9600);

    // region Screen initialization
    screen.initialize();
    screen.drawLogo();
    // endregion

    // region Buttons
    btn.setTickMode(MANUAL);
    btnPrev.setTickMode(MANUAL);
    btnNext.setTickMode(MANUAL);
    btnSlct.setTickMode(MANUAL);
    // endregion

    // region Beeper
    pinMode(BEEPER, OUTPUT);
    // endregion

    // region Led
    led.initialize();
    // endregion

    // region CO2 (MHZ-19)
    screen.drawProgress(LoadingProgress::STAGE_1);
    uint8_t tryCount = 3;
    do {
        if (mhz19.getStatus() <= 0) {
            mhz19.begin(MHZ19B_TX, MHZ19B_RX);
            mhz19.setAutoCalibration(false);
            screen.drawProgressOk();
            break;
        } else {
            screen.drawProgressDot();
        }
        delay(500);
        tryCount--;
    } while (tryCount > 0);
    if (tryCount == 0) {
        screen.drawProgressFail();
    }
    // endregion

    // region Temperature, humidity and pressure (BME280)
    screen.drawProgress(LoadingProgress::STAGE_2);
    delay(50);
    if (bme.begin(&Wire)) {
        // Настройка BME280
        bme.setSampling(Adafruit_BME280::MODE_FORCED,
                        Adafruit_BME280::SAMPLING_X1, // Temperature
                        Adafruit_BME280::SAMPLING_X1, // pressure
                        Adafruit_BME280::SAMPLING_X1, // humidity
                        Adafruit_BME280::FILTER_OFF);
        screen.drawProgressOk();
    } else {
        screen.drawProgressFail();
    }
    // End

    // region Time
    screen.drawProgress(LoadingProgress::STAGE_3);
    if (RESET_CLOCK || rtc.lostPower()) {
        RTC_DS3231::adjust(DateTime(F(__DATE__), F(__TIME__)));
    }
    screen.drawProgressOk();
    // endregion

    // region Air quality
    screen.drawProgress(LoadingProgress::STAGE_4);
    mp503.initialize();
    screen.drawProgressOk();
    // endregion


    delay(500);
    screen.cleanScreen();
}

void loop() {

    // Battery
//    int value = analogRead(A7);
//    Serial.print("value = ");
//    Serial.println(map(value, 500, 680, 0, 5));
//    delay(500);



// Mp503
//    delay(3000);
//    uint8_t pollution = mp503.readPollution();
//
//    if (pollution == MP503::HEAVY_POLLUTION_AIR) {
//        Serial.println("High pollution! Force signal active.");
//    } else if (pollution == MP503::MIDDLE_POLLUTION_AIR) {
//        Serial.println("High pollution!");
//    } else if (pollution == MP503::SLIGHT_POLLUTION_AIR) {
//        Serial.println("Low pollution!");
//    } else if (pollution == MP503::CLEAN_AIR) {
//        Serial.println("Fresh air.");
//    }


//    // BME
    bme.takeForcedMeasurement();
    float dispTemp = bme.readTemperature();   // Температура
//    float dispHum = bme.readHumidity();       // Влажность
//    float dispPres = bme.readPressure() * 0.00750062f; // Давление
    int dispCO2 = mhz19.getPPM();           // CO2

    Serial.print("  dispTemp = ");
    Serial.print(roundTemperatureQuality(dispTemp));
//
//    Serial.print("  dispHum = ");
//    Serial.print(roundHumanityQuality(dispHum));
//
//    Serial.print("  dispPres = ");
//    Serial.print(roundPressureQuality(dispPres));
//
    Serial.print("  dispCO2 = ");
    Serial.println(dispCO2);
//    delay(1000);




// MHZ-19
    int mhzCO2 = mhz19.getPPM();
    Serial.print("  mhzCO2  = ");
    Serial.print(mhzCO2);
    int mhzTemp = mhz19.getTemperature();
    Serial.print("  mhzTemp  = ");
    Serial.println(mhzTemp);
    delay(1000);
}