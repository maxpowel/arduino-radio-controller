#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
// Mega
#define EEPROM_SIZE 4096
#endif

#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega16U4__)
// UNO y Leonardo
#define EEPROM_SIZE 1024
#endif

#if defined(__AVR_ATmega168__)
// Los mas viejos
#define EEPROM_SIZE 512
#endif

#if !defined(EEPROM_SIZE)
#define EEPROM_SIZE -1
#endif
