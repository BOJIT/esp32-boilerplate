#include "main.h"

Esp32Serial esp32serial(115200);

void setup()
{

    xTaskCreate(sensingTask, "sensing", 2048, NULL, 1, NULL);

}

// Unused Task - using FreeRTOS as Scheduler
void loop() {
    vTaskDelete(NULL);
}
