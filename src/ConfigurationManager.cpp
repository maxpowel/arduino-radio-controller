//
// Created by alvaro on 6/11/15.
//

#include "ConfigurationManager.h"


ConfigurationManager::ConfigurationManager(){
    eeprom_read_block((void*)&info, (void*)0, sizeof(info));
}


ConfigurationInfo ConfigurationManager::getConfigurationInfo() {
    return info;
}

void ConfigurationManager::removeConfiguration(int number) {
    for (int i = number; i < info.totalConfigs - 1; i++) {
        PayloadConfiguration temp = getConfiguration(i + 1);
        /*Serial.print("Copiando de " );
        Serial.print(i + 1);
        Serial.print(" a ");
        Serial.print(i);
        Serial.print(" ");
        Serial.println(temp.name);*/
        saveConfiguration(temp, i);
    }
    info.totalConfigs--;
}

int ConfigurationManager::updateConfiguration(PayloadConfiguration conf, int number) {
    if (number <= info.totalConfigs) {
        saveConfiguration(conf, number);
        return 1;
    } else {
        return 0;
    }
}


void ConfigurationManager::saveConfiguration(PayloadConfiguration conf, int number) {
    int index = eepromIndex(number);
    /*Serial.println("escribien en ");
    Serial.println(number);
    Serial.println(index);*/
    eeprom_write_block((void*)&conf, (void*) index, sizeof(conf));
}

int ConfigurationManager::addConfiguration(PayloadConfiguration conf) {
    saveConfiguration(conf, info.totalConfigs);
    info.totalConfigs++;
    return info.totalConfigs;
}


PayloadConfiguration ConfigurationManager::getConfiguration(int number){
    struct PayloadConfiguration conf;
    int index = eepromIndex(number);
    /*Serial.println("leyendo de ");
    Serial.println(index);*/
    eeprom_read_block((void*)&conf, (void*) index, sizeof(conf));
    return conf;
}

void ConfigurationManager::sync() {
    eeprom_write_block((void*)&info, (void*)0, sizeof(info));
}

void ConfigurationManager::updateInfo(ConfigurationInfo i) {
    info = i;
}

void ConfigurationManager::reset() {
    info.totalConfigs = 0;
    info.version = 0;
    info.configSize = sizeof(PayloadConfiguration);
}

void ConfigurationManager::printInfo() {
    Serial.print("Total configs: ");
    Serial.println(info.totalConfigs);
    Serial.print("Version: ");
    Serial.println(info.version);
    Serial.print("Config size: ");
    Serial.println(info.configSize);
}

int ConfigurationManager::eepromIndex(int num) {
    return sizeof(info) + num * sizeof(PayloadConfiguration);
}