//
// Created by alvaro on 6/11/15.
//

#ifndef ARDUINO_RADIO_CONTROLLER_CONFIGURATIONMANAGER_H
#define ARDUINO_RADIO_CONTROLLER_CONFIGURATIONMANAGER_H

#include "Arduino.h"

struct PayloadConfiguration {
    char name[20];
    char emitterAddress[5];
    char receiverAddress[5];
    unsigned char channel;
    unsigned char version;
    unsigned char payloadSize;
};

struct ConfigurationInfo {
    unsigned char totalConfigs;
    unsigned char configSize;
    int version;
};


class ConfigurationManager {
public:
    ConfigurationManager();
    ConfigurationInfo getConfigurationInfo();
    PayloadConfiguration getConfiguration(int number);
    void removeConfiguration(int number);
    int updateConfiguration(PayloadConfiguration conf, int number);
    int addConfiguration(PayloadConfiguration conf);
    void sync();
    void updateInfo(ConfigurationInfo i);
    void reset();
    void printInfo();

private:
    ConfigurationInfo info;
    void saveConfiguration(PayloadConfiguration conf, int number);
    int eepromIndex(int number);
};


#endif //ARDUINO_RADIO_CONTROLLER_CONFIGURATIONMANAGER_H
