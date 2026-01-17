# bozontlabsUptime

Uptime tracking library for Arduino devices.

Tracks uptime based on `millis()` and handles `millis()` overflows which enables users to track uptimes beyond 50 days (up to about 584 million years).

## Usage

The library provides a singleton `Uptime` class for which the instance can be acquired with:

 - `Uptime& uptime = Uptime::getInstance();`

Periodically call the `update()` function to enable the library to track `millis()` overflows:

 - `uptime.update();`

Use the library's provided functions to get the current uptime of your device:

 - `uptime.get_uptime_days()` - returns the days since last reset
 - `uptime.get_uptime_hours()` - returns the hours since last reset
 - `uptime.get_uptime_minutes()` - returns the minutes since last reset
 - `uptime.get_uptime_seconds()` - returns the seconds since last reset
 - `uptime.get_uptime_milliseconds()` - returns the milliseconds since last reset
 - `uptime.get_uptime_string()` - returns a human-readable uptime string like `5d 7h 24m 12s`
