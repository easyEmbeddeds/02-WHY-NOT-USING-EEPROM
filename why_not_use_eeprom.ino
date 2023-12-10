/*
 Name:		why_not_use_eeprom.ino
 Created:	26.04.2023 21:41:54
 Author:	DarthSidious
*/

#include <Arduino.h>
#include <EEPROM.h>

#include "DeviceSettings.hpp"

led_channel_t led_channel_1_write = {
  .sunrise = { .hour = 7, .minute = 30, .seconds = 25 },
  .sunset = { .hour = 20, .minute = 45, .seconds = 13 },
  .day_power = 120,
  .night_power = 1,
};  /// base led channel configuration to save in EEPROM

shutter_t shutter_1_write = {
  .openup_time = { .hour = 7, .minute = 45, .seconds = 20 },
  .closeup_time = { .hour = 21, .minute = 10, .seconds = 45 },
  .position = UP,
};  /// base shutter configuration to save in EEPROM

led_channel_t led_channel_1_read;
shutter_t shutter_1_read;

uint32_t reboot_cntr = 0;

void update_reboot_counter(void) {
  /// create pointer to reboot counter
  uint8_t* ptr = (uint8_t*)&reboot_cntr;

  /// read 4 following bytes from EEPROM and write as reboot_cntr
  for (uint8_t i = 0; i < sizeof(reboot_cntr); i++) {
    *(ptr + i) = EEPROM.read(i);
  }

  Serial.println("Rebot counter is " + String(reboot_cntr));

  /// update reboot_cntr
  reboot_cntr++;

  /// write each byte of reboot_cntr as 4 following bytes into EEPROM
  for (uint8_t i = 0; i < sizeof(reboot_cntr); i++) {
    EEPROM.write(i, *(ptr + i));
  }
}

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(115200);
  Serial.println("Hello YouTube");

  /// read and update reboot counter
  update_reboot_counter();

  /// write to eeprom led channel configuration
  /// set offset
  uint16_t offset = sizeof(reboot_cntr);

  /// set pointer to led_channel_1_write
  uint8_t* ptr = (uint8_t*)&led_channel_1_write;

  /// write each byte of led_channel_1_write as following bytes into EEPROM
  for (uint8_t i = 0; i < sizeof(led_channel_1_write); i++) {
    EEPROM.write(offset + i, *(ptr + i));
  }

  /// read led channel configuration from EEPROM and save to structure led_channel_1_read
  ptr = (uint8_t*)&led_channel_1_read;
  for (uint8_t i = 0; i < sizeof(led_channel_1_read); i++) {
    *(ptr + i) = EEPROM.read(offset + i);
  }

  /// update offset of size of led_channel_1_read
  offset += sizeof(led_channel_1_read);

  /// set pointer to shutter_1_write
  ptr = (uint8_t*)&shutter_1_write;

  /// write each byte of shutter_1_write as following bytes into EEPROM
  for (uint8_t i = 0; i < sizeof(shutter_1_write); i++) {
    EEPROM.write(offset + i, *(ptr + i));
  }

  /// read shutter configuration from EEPROM and save to structure shutter_1_read
  ptr = (uint8_t*)&shutter_1_read;
  for (uint8_t i = 0; i < sizeof(shutter_1_read); i++) {
    *(ptr + i) = EEPROM.read(offset + i);
  }

  print_led_cfg(&led_channel_1_write);
  print_led_cfg(&led_channel_1_read);

  int compare_result = memcmp(&led_channel_1_write, &led_channel_1_read, sizeof(led_channel_1_read));
  Serial.println(compare_result == 0 ? "Led configurations are the same" : "ERROR: Led configurations are different");

  print_shutter_cfg(&shutter_1_write);
  print_shutter_cfg(&shutter_1_read);

  compare_result = memcmp(&shutter_1_write, &shutter_1_read, sizeof(shutter_1_read));
  Serial.println(compare_result == 0 ? "Shutter configurations are the same" : "ERROR: Shutter configurations are different");
}


// the loop function runs over and over again until power down or reset
void loop() {
}
