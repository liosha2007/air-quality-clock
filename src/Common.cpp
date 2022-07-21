//
// Created by liosha on 20.07.2022.
//

#include "Common.h"

const char *eventToString(Event event) {
    switch (event) {
        case Event::InitScreen:
            return "Event::InitScreen";
        case Event::InitDS3231:
            return "Event::InitDS3231";
        default:
            return "Event::___UNDEFINED___";
    }
}