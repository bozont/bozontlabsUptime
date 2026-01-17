#pragma once

#include <Arduino.h>

// Singleton class to track system uptime, handling millis() overflows
class Uptime {
public:
  static Uptime& getInstance() {
    static Uptime instance;
    return instance;
  }

  void update() {
    static uint32_t millis_prev = 0u;
    // Check if millis has overflowed
    if (millis() < millis_prev) {
      this->millis_overflows++;
    }
    millis_prev = millis();
  }

  uint64_t get_uptime_days() {
    uint64_t uptime_days = ((uint64_t)millis() + (this->millis_overflows * UINT32_MAX)) / (uint64_t)86400000;
    return uptime_days;
  }

  uint64_t get_uptime_hours() {
    uint64_t uptime_hours = ((uint64_t)millis() + (this->millis_overflows * UINT32_MAX)) / (uint64_t)3600000;
    return uptime_hours;
  }

  uint64_t get_uptime_minutes() {
    uint64_t uptime_minutes = ((uint64_t)millis() + (this->millis_overflows * UINT32_MAX)) / (uint64_t)60000;
    return uptime_minutes;
  }

  uint64_t get_uptime_seconds() {
    uint64_t uptime_seconds = ((uint64_t)millis() + (this->millis_overflows * UINT32_MAX)) / (uint64_t)1000;
    return uptime_seconds;
  }

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
