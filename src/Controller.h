//
// Created by alvaro on 7/11/15.
//

#ifndef ARDUINO_RADIO_CONTROLLER_CONTROLLER_H
#define ARDUINO_RADIO_CONTROLLER_CONTROLLER_H

#include "Arduino.h"
class Controller {
public:
    virtual int init();
    virtual void next(uint8_t *data);
};


#endif //ARDUINO_RADIO_CONTROLLER_CONTROLLER_H
