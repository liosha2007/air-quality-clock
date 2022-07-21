//
// Created by liosha on 18.07.2022.
//

#ifndef AIR_QUALITY_CLOCK_CYCLEBUFFER_H
#define AIR_QUALITY_CLOCK_CYCLEBUFFER_H

#include <stdint-gcc.h>
#include "Common.h"

template <class T>
class CycleBuffer {
public:
    explicit CycleBuffer(uint8_t _size);

    ~CycleBuffer();

    void push(T item);

    T pull();

    bool hasEvents();

    uint8_t eventCount();

private:
    T* _buffer;
    uint8_t _size;
    uint8_t _count;
    uint8_t _head;
    uint8_t _tail;
};

#endif //AIR_QUALITY_CLOCK_CYCLEBUFFER_H
