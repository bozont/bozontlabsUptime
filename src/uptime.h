/*
MIT License

bozontlabsUptime - Uptime tracking library for Arduino devices
Copyright (c) 2026 Tamas Jozsi

Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation
files (the "Software"), to deal in the Software without
restriction, including without limitation the rights to use,
copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following
conditions:

This permission notice shall be included in all copies or
substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.
*/

#pragma once

#include <Arduino.h>

// Singleton class to track system uptime, handling millis() overflows
class Uptime {
public:
  static Uptime& getInstance() {
    static Uptime instance;
    return instance;
  }

  // Updates the uptime tracker and checks for millis() overflows
  void update() {
    static uint32_t millis_prev = 0u;
    // Check if millis has overflowed
    if (millis() < millis_prev) {
      this->millis_overflows++;
    }
    millis_prev = millis();
  }

  // Returns the days since last reset
  uint64_t get_uptime_days() {
    uint64_t uptime_days = ((uint64_t)millis() + (this->millis_overflows * UINT32_MAX)) / (uint64_t)86400000;
    return uptime_days;
  }

  // Returns the hours since last reset
  uint64_t get_uptime_hours() {
    uint64_t uptime_hours = ((uint64_t)millis() + (this->millis_overflows * UINT32_MAX)) / (uint64_t)3600000;
    return uptime_hours;
  }

  // Returns the minutes since last reset
  uint64_t get_uptime_minutes() {
    uint64_t uptime_minutes = ((uint64_t)millis() + (this->millis_overflows * UINT32_MAX)) / (uint64_t)60000;
    return uptime_minutes;
  }

  // Returns the seconds since last reset
  uint64_t get_uptime_seconds() {
    uint64_t uptime_seconds = ((uint64_t)millis() + (this->millis_overflows * UINT32_MAX)) / (uint64_t)1000;
    return uptime_seconds;
  }

  // Returns a human-readable uptime string like '5d 7h 24m 12s'
  String get_uptime_string() {
    uint64_t up_days = this->get_uptime_days();
    uint64_t up_hours = this->get_uptime_hours() % 24;
    uint64_t up_minutes = this->get_uptime_minutes() % 60;
    uint64_t up_seconds = this->get_uptime_seconds() % 60;

    String up_str = "";
    up_str += String((unsigned long)up_days) + "d ";
    up_str += String((unsigned long)up_hours) + "h ";
    up_str += String((unsigned long)up_minutes) + "m ";
    up_str += String((unsigned long)up_seconds) + "s";
    return up_str;
  }

  // Returns the milliseconds since last reset
  uint64_t get_uptime_milliseconds() {
    return (uint64_t)millis() + (this->millis_overflows * UINT32_MAX);
  }

private:
  uint64_t millis_overflows;

  Uptime()
      : millis_overflows(0u) {}

  Uptime(const Uptime&) = delete;
  Uptime& operator=(const Uptime&) = delete;
};
