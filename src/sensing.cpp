/* Sensing Code - Continuous Loop */
#include "main.h"

void sensingTask(void *args __attribute((unused)))
{

    for(;;)
    {

        esp32serial.info("Printf - Debug %u", 526);

        vTaskDelay(200 / portTICK_PERIOD_MS);
    }
}
