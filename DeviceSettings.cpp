#include "DeviceSettings.hpp"

#include <Arduino.h>

void print_led_cfg(const led_channel_t* cfg) {
	Serial.println("led config:");

	String txt = "\tsunrise " + String(cfg->sunrise.hour) + ":" + String(cfg->sunrise.minute) + ":" + String(cfg->sunrise.seconds);
	Serial.println(txt);

	txt = "\tsunset " + String(cfg->sunset.hour) + ":" + String(cfg->sunset.minute) + ":" + String(cfg->sunset.seconds);
	Serial.println(txt);

	txt = "\tday_power " + String(cfg->day_power);
	Serial.println(txt);

	txt = "\tnight_power " + String(cfg->night_power);
	Serial.println(txt);
}

void print_shutter_cfg(const shutter_t* cfg) {
	String txt = "";
	Serial.println("shutter config:");

	txt = "\topenup time " + String(cfg->openup_time.hour) + ":" + String(cfg->openup_time.minute) + ":" + String(cfg->openup_time.seconds);
	Serial.println(txt);

	txt = "\tcloseup time " + String(cfg->closeup_time.hour) + ":" + String(cfg->closeup_time.minute) + ":" + String(cfg->closeup_time.seconds);
	Serial.println(txt);

	txt = "\tshutter position " + String(cfg->position);
	Serial.println(txt);
}
