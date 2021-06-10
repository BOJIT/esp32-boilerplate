#include "main.h"

Esp32Serial esp32serial(115200);

void setup()
{
    esp32serial.info("Hello One");
    esp32serial.warning("Hello Two");
    esp32serial.error("Hello Three");
    esp32serial.info("Hello Four");

    xTaskCreate(sensingTask, "sensing", 2048, NULL, 1, NULL);

}

// Unused Task - using FreeRTOS as Scheduler
void loop() {
    vTaskDelete(NULL);
}
