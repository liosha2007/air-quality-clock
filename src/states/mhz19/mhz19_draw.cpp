//
// Created by liosha on 21.07.2022.
//

#include "states/mhz19/mhz19_draw.h"

namespace mhz19 {

    enum : uint8_t {
        CleanArea = 1, Draw, Wait
    } nextState = Draw;

    static uint32_t capturedTime = 0;
    static char co2String[11] = {0};

    uint16_t getColorDependingOnCO2(int16_t value);

    void draw() {
        Serial.print("..");
        switch (nextState) {
            case CleanArea:
                Serial.println("CleanArea");

                // Clean date
                if (co2String[0] != 0) {
                    st7735::it.setCursor(DRAW_MHZ19_DRAW_DATA_X, DRAW_MHZ19_DRAW_DATA_Y);
                    st7735::it.setTextSize(DRAW_MHZ19_DATA_SIZE);
                    st7735::it.setTextColor(SCREEN_BACKGROUND);
                    st7735::it.println(co2String);
                }

                nextState = Draw;
                eventBuffer.push(Event::DrawMHZ19);
                break;
            case Draw: {
                Serial.println("Draw");

                int16_t co2 = it.getCarbonDioxide();
                st7735::it.setTextSize(DRAW_MHZ19_DATA_SIZE);
                st7735::it.setTextColor(getColorDependingOnCO2(co2));

                if (co2 != -1) {
                    st7735::it.setCursor(DRAW_MHZ19_DRAW_DATA_X, DRAW_MHZ19_DRAW_DATA_Y);
                    sprintf(co2String, "%02d", co2);
                    st7735::it.println(co2String);
                }

                st7735::it.setTextSize(DRAW_MHZ19_LABEL_SIZE);
                st7735::it.setCursor(DRAW_MHZ19_DRAW_LABEL_X, DRAW_MHZ19_DRAW_LABEL_Y);
                st7735::it.println("co2");

                capturedTime = millis();
                nextState = Wait;
                eventBuffer.push(Event::DrawMHZ19);
                break;
            }
            case Wait: {
                Serial.println("Wait");
                if (millis() - capturedTime < DRAW_MHZ19_DELAY_MS                       || !it.isReady()) {
                    eventBuffer.push(Event::DrawMHZ19);
                } else {
                    nextState = CleanArea;
                    eventBuffer.push(Event::DrawMHZ19);
                }
                break;
            }
            default:
                Serial.println("__UNKNOWN__");
                break;
        }
    }

    uint16_t getColorDependingOnCO2(int16_t value) {
        if (value <= 400) {
            return SCREEN_COLOR_GREEN;// GOOD
        } else if (value <= 1000) {
            return SCREEN_COLOR_GREENYELLOW; // NORMAL
        } else if (value <= 1500) {
            return SCREEN_COLOR_YELLOW; // WARNING
        } else if (value <= 2000) {
            return SCREEN_COLOR_ORANGE; //BAD
        } else {
            return SCREEN_COLOR_RED; // DANGEROUS
        }
    }
}
