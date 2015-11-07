//
// Created by alvaro on 7/11/15.
//

#include "XBoxController.h"


XBoxController::XBoxController() {

    Xbox = new XBOXRECV(&Usb);
}

int XBoxController::init() {
    return Usb.Init();
}

void XBoxController::next(uint8_t *data) {
    Usb.Task();
    if (Xbox->XboxReceiverConnected) {
        for (uint8_t i = 0; i < 4; i++) {
            if (Xbox->Xbox360Connected[i]) {
                data[0] = padFilter(Xbox->getAnalogHat(LeftHatX, i));
                data[1] = padFilter(Xbox->getAnalogHat(LeftHatY, i));
                data[2] = padFilter(Xbox->getAnalogHat(RightHatX, i));
                data[3] = padFilter(Xbox->getAnalogHat(RightHatY, i));
            }
        }
    }
}

int XBoxController::padFilter(int value) {
    if (value > -7700 && value < 6000)
        value = 0;
    return value;
}