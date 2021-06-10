/* Sensing Code - Continuous Loop */
#include "main.h"

void sensingTask(void *args __attribute((unused)))
{

    for(;;)
    {


        // Serial.write("\u001b[32m");
        // Serial.println("Hello World!");
        // Serial.write("\u001b[0m");

        esp32serial.warning("No %d", 10);

        esp32serial.error("Enter");

        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
}
