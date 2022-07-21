//
// Created by liosha on 18.07.2022.
//

#include "CycleBuffer.h"

template<class T>
CycleBuffer<T>::CycleBuffer(uint8_t size) : _buffer(new T[size]), _size(size), _count(0), _head(0), _tail(0) {
}

template<class T>
CycleBuffer<T>::~CycleBuffer() {
    delete[] _buffer;
}

template<class T>
void CycleBuffer<T>::push(T item) {
    this->_buffer[this->_tail] = item;
    this->_tail++;
    if (this->_count < _size) { // Otherwise some element was lost
        this->_count++;
    }
    if (this->_tail == this->_size) {
        this->_tail = 0;
    }
}

template<class T>
T CycleBuffer<T>::pull() {
    if (this->_count == 0) {
        return T();
    }
    T item = this->_buffer[this->_head];
    this->_head++;
    this->_count--;

    if (this->_head == this->_size) {
        this->_head = 0;
    }

    return item;
}

template<class T>
bool CycleBuffer<T>::hasEvents() {
    bool hasEvents = this->_count > 0;
    if (hasEvents) {
    }
    return hasEvents;
}

template<class T>
uint8_t CycleBuffer<T>::eventCount() {
    return this->_count;
}

template
class CycleBuffer<Event>;