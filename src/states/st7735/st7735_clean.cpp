//
// Created by liosha on 22.07.2022.
//

#include "states/st7735/st7735_clean.h"

namespace st7735 {

    void clean(void (*finishCallback)()) {
        Serial.print("..");

        it.fillScreen(SCREEN_BACKGROUND);

        finishCallback();
    }
}
