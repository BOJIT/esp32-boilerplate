#include "main.h"

Esp32Serial log(115200);

void setup()
{
    log.info('Hello World');
    // Serial.begin(115200);
    // Serial.write("\u001b[31m");
    // Serial.println("Hello World!");
    // Serial.write("\u001b[0m");

    xTaskCreate(sensingTask, "sensing", 1024, NULL, 1, NULL);

}

// Unused Task - using FreeRTOS as Scheduler
void loop() {
    vTaskDelete(NULL);
}
