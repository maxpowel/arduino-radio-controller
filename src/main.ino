#include "Configuration.h"
#include "ConfigurationManager.h"

#include <SPI.h>
#include <NRF24.h>

#include "XBoxController.h"

NRF24 nrf24(8, 7);

XBoxController controller;

int payloadSize;
uint8_t data[32];

void setup() {

    ConfigurationManager conf;
    PayloadConfiguration pc = conf.getConfiguration(0);
    payloadSize = pc.payloadSize;

    Serial.begin(9600);

    if (controller.init() == -1) {
        Serial.print(F("\r\nController did not start"));
        while (1); //halt
    }
    Serial.print(F("\r\nController Started"));

    if (!nrf24.init()) {
        Serial.println("NRF24 init failed");
        while (1); //halt
    }
    Serial.print(F("\r\nNRF24 Started"));

    // Enable the EN_DYN_ACK feature so we can use noack
    nrf24.spiWriteRegister(NRF24_REG_1D_FEATURE, NRF24_EN_DYN_ACK);

    if (!nrf24.setChannel(pc.channel))
        Serial.println("setChannel failed");

    if (!nrf24.setThisAddress((uint8_t *) pc.emitterAddress, 5))
        Serial.println("setThisAddress failed");

    if (!nrf24.setTransmitAddress((uint8_t *) pc.receiverAddress, 5))
        Serial.println("setTransmitAddress failed");

    if (!nrf24.setPayloadSize(pc.payloadSize))
        Serial.println("setPayloadSize failed");

    if (!nrf24.setRF(NRF24::NRF24DataRate250kbps, NRF24::NRF24TransmitPower0dBm))
        Serial.println("setRF failed");


    // Enviar



    /*if (!nrf24.send((uint8_t*)&conf, sizeof(conf), true))
        Serial.println("send failed");
*/


    //  ConfigurationManager conf;
    //  ConfigurationInfo info = conf.getConfigurationInfo();
/*
    conf.reset();
    conf.sync();
    struct PayloadConfiguration pconf;
    strcpy( pconf.name, "Cuadricoptero");
    pconf.payloadSize = 4;
    conf.addConfiguration(pconf);
    strcpy( pconf.name, "Robocoche");
    pconf.payloadSize = 8;
    conf.addConfiguration(pconf);

    //conf.removeConfiguration(0);
    //conf.updateConfiguration(pconf,0);
    //pconf = conf.getConfiguration(0);


    conf.sync();
*/
    /*   for(int i = 0; i < info.totalConfigs; i++){
           PayloadConfiguration pc = conf.getConfiguration(i);
           Serial.println(pc.name);
           Serial.println(pc.payloadSize);
           Serial.println("--------");
       }
   */
    //struct PayloadConfiguration conf;
    //conf.version = 2;

    //
/*    int tam = EEPROM_SIZE;
    Serial.println("Tam es ");
    Serial.println(tam);
*/

    //eeprom_read_block((void*)&conf, (void*)0, sizeof(conf));

    //eeprom_write_block((const void*)&conf, (void*)0, sizeof(conf));
    //Serial.println(conf.version);


}







void loop() {
    controller.next(data);
    if (!nrf24.send(data, payloadSize, true))
        Serial.println("send failed");

}