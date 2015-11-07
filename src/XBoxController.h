//
// Created by alvaro on 7/11/15.
//

#ifndef ARDUINO_RADIO_CONTROLLER_XBOXCONTROLLER_H
#define ARDUINO_RADIO_CONTROLLER_XBOXCONTROLLER_H

#include <XBOXRECV.h>
#include "Controller.h"


class XBoxController: public Controller {
public:
    XBoxController();
    int init();
    void next(uint8_t *data);
private:
    USB Usb;
    XBOXRECV *Xbox;
    int padFilter(int value);
};


#endif //ARDUINO_RADIO_CONTROLLER_XBOXCONTROLLER_H
