#pragma once

#include <stdint.h>

typedef struct {
	uint8_t hour;
	uint8_t minute;
	uint8_t seconds;
} time_t;

typedef struct {
	time_t sunrise;       ///< sunrise time
	time_t sunset;        ///< sunset time
	uint8_t day_power;    ///< lamp power in day
	uint8_t night_power;  ///< lamp power in night
} led_channel_t;

typedef enum {
	UP = 0,
	MIDDLE,
	DOWN
} position_t;  /// shutter position

typedef struct {
	time_t openup_time;   ///< shutter open time
	time_t closeup_time;  ///< shutter close time
	position_t position;  ///< shutter position
} shutter_t;

void print_led_cfg(const led_channel_t* cfg);
void print_shutter_cfg(const shutter_t* cfg);
