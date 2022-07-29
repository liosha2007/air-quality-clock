//
// Created by liosha on 21.07.2022.
//

#include "states/mhz19/mhz19_draw.h"

namespace mhz19 {

    static State nextState = State::Draw;

    static uint32_t capturedTime = 0;
    static char co2String[11] = {0};

    uint16_t getColorDependingOnCO2(int16_t value);

    void draw() {
        IF_DEBUG(Serial.print("..");)
        switch (nextState) {
            case State::PreDraw:
                IF_DEBUG(Serial.println("CleanArea");)

                // Clean date
                if (co2String[0] != 0) {
                    st7735::it.setCursor(DRAW_MHZ19_DRAW_DATA_X, DRAW_MHZ19_DRAW_DATA_Y);
                    st7735::it.setTextSize(DRAW_MHZ19_DATA_SIZE);
                    st7735::it.setTextColor(SCREEN_BACKGROUND);
                    st7735::it.println(co2String);
                }

                nextState = State::Draw;
                eventBuffer.push(Event::DrawMHZ19);
                break;
            case State::Draw: {
                IF_DEBUG(Serial.println("Draw");)

                int16_t co2 = it.getCarbonDioxide();
                st7735::it.setTextSize(DRAW_MHZ19_DATA_SIZE);
                st7735::it.setTextColor(getColorDependingOnCO2(co2));

                st7735::it.setCursor(DRAW_MHZ19_DRAW_DATA_X, DRAW_MHZ19_DRAW_DATA_Y);
                if (co2 != -1) {
                    sprintf(co2String, "%02d", co2);
                } else {
                    sprintf(co2String, "%2s", "~");
                }
                st7735::it.println(co2String);

                st7735::it.setTextSize(DRAW_MHZ19_LABEL_SIZE);
                st7735::it.setCursor(DRAW_MHZ19_DRAW_LABEL_X, DRAW_MHZ19_DRAW_LABEL_Y);
                st7735::it.println("co2");

                capturedTime = millis();
                nextState = State::Delay;
                eventBuffer.push(Event::DrawMHZ19);
                break;
            }
            case State::Delay: {
                IF_DEBUG(Serial.println("Wait");)
                if (millis() - capturedTime < DRAW_MHZ19_DELAY_MS                       || !it.isReady()) {
                    eventBuffer.push(Event::DrawMHZ19);
                } else {
                    nextState = State::PreDraw;
                    eventBuffer.push(Event::DrawMHZ19);
                }
                break;
            }
            default:
                IF_DEBUG(Serial.println("__UNKNOWN__");)
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
