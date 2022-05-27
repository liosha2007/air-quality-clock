
//#include <avr/power.h>

#include "main.h"
#include "DS3231.h"

TripleLed led = TripleLed(LED_RED, LED_GREEN, LED_BLUE);
Screen screen;

//GButton btn(BUTTON_FRONT, LOW_PULL); // Front button
//
//GButton btnPrev(JOYSTICK_1, HIGH_PULL); // Joystick left
//GButton btnNext(JOYSTICK_2, HIGH_PULL); // Joystick right
//GButton btnSlct(JOYSTICK_3, HIGH_PULL); // Joystick center

MHZ19 mhz(MHZ19B_TX, MHZ19B_RX);    // CO2
BME280 bme;                         // Temperature, humidity and pressure
DS3231 time;                     // Time
MP503 mp = MP503(MP503_A, MP503_B); // Air quality
CCS811 ccs;                         // Air quality
Buttery buttery(PIN_BUTTERY_LEVEL);

void drawDotOnScreen(uint8_t progress) {
    screen.drawProgressDot();
}

__attribute__((unused)) void setup() {
    Serial.begin(9600);

    led.initialize();

    screen.initialize();
    screen.drawLogo();

//    btn.setTickMode(MANUAL);
//    btnPrev.setTickMode(MANUAL);
//    btnNext.setTickMode(MANUAL);
//    btnSlct.setTickMode(MANUAL);

    pinMode(BEEPER, OUTPUT);
    buttery.initialize();

    // region CO2 (MHZ-19)
    screen.drawProgress(LoadingProgress::STAGE_1);
    delay(50);
    if (mhz.initialize(3, drawDotOnScreen)) {
        screen.drawProgressOk();
    } else {
        screen.drawProgressFail();
        delay(500);
    }
    // endregion

    // region Temperature, humidity and pressure (BME280)
    screen.drawProgress(LoadingProgress::STAGE_2);
    delay(50);
    if (bme.initialize(3, drawDotOnScreen)) {
        screen.drawProgressOk();
    } else {
        screen.drawProgressFail();
        delay(500);
    }
    // endregion

    // region Time
    screen.drawProgress(LoadingProgress::STAGE_3);
    delay(50);
    if (time.initialize(3, drawDotOnScreen)) {
        screen.drawProgressOk();
    } else {
        screen.drawProgressFail();
        delay(500);
    }
    // endregion

    // region Air quality
    screen.drawProgress(LoadingProgress::STAGE_4);
    delay(50);
    if (mp.initialize()) {
        screen.drawProgressOk();
    } else {
        screen.drawProgressFail();
        delay(500);
    }
    // endregion

    // region CCS-811 Air quality
    screen.drawProgress(LoadingProgress::STAGE_5);
    delay(50);
    if (ccs.initialize(3, drawDotOnScreen)) {
        screen.drawProgressOk();
    } else {
        screen.drawProgressFail();
        delay(500);
    }
    // endregion

    delay(500);
    screen.cleanScreen();

    tone(BEEPER, 3000, 500);
}

__attribute__((unused)) void loop() {

    uint32_t timeInMillis = millis();

    int butteryValue = buttery.readLevel(timeInMillis);
    screen.drawButtery(butteryValue, BUTTERY_MIN, BUTTERY_MAX);

    DateTime dateTime = time.readDateTime(timeInMillis);
    screen.drawDateTime(dateTime);

    uint8_t pollutionValue = mp.readPollution(timeInMillis);

    if (pollutionValue == MP503::HEAVY_POLLUTION_AIR) {
        screen.drawPollution(8, 8);
    } else if (pollutionValue == MP503::MIDDLE_POLLUTION_AIR) {
        screen.drawPollution(4, 8);
    } else if (pollutionValue == MP503::SLIGHT_POLLUTION_AIR) {
        screen.drawPollution(2, 8);
    } else if (pollutionValue == MP503::CLEAN_AIR) {
        screen.drawPollution(1, 4);
    }

    // BME280
    float tempValue = bme.readTemperature(timeInMillis);
    uint8_t humidityValue = bme.readHumidity(timeInMillis);
    uint16_t pressureValue = bme.readPressure(timeInMillis);

    screen.drawTemperature(tempValue);
    screen.drawHumidity(humidityValue);
    screen.drawPressure(pressureValue);

    int16_t co2Value = mhz.readCo2(timeInMillis);
    screen.drawCO2(co2Value);

//    uint16_t ccsCO2 = ccs.readCo2(timeInMillis);
    uint16_t ccsTVOC = ccs.readTvoc(timeInMillis); // <0.3 | 0.3-1 | 1-3 | 3-10 | 10-25
    screen.drawTVOC(ccsTVOC);



//    /*!
//     * @brief Set baseline
//     * @param get from getBaseline.ino
//     */
//    ccs.writeBaseLine(0x847B);
//    //delay cannot be less than measurement cycle
//    //delay(1000);
//    delay(1000);
//    Serial.println("");
}
