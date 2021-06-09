#include "main.h"

// Debugging Wrappers
void serial_init(void)
{
    Serial.begin(115200);
}
void serial_send(char c)
{
    Serial.write(c);
}

void setup()
{
    debugInitialise(10, serial_init, serial_send);
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
