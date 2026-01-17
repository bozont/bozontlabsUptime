#include <uptime.h>

void setup() {
  Serial.begin(115200);
}

void loop() {
  // Get the uptime tracker instance
  Uptime& uptime = Uptime::getInstance();
  // Call update() to be able to track millis() overflows
  uptime.update();
  // Print the current uptime
  Serial.print("Uptime: ");
  Serial.println(uptime.get_uptime_string());
  // Wait a bit
  delay(1000);
}
