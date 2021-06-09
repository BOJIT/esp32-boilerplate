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

    xTaskCreate(sensingTask, "sensing", 1024, NULL, 1, NULL);

}

void loop() {} // Unused - using FreeRTOS as Scheduler