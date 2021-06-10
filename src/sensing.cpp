/* Sensing Code - Continuous Loop */
#include "main.h"

void sensingTask(void *args __attribute((unused)))
{

    for(;;)
    {

        esp32serial.info("This is info - normal printf substitutions work: %u", 526);

        esp32serial.warning("This is a warning!");

        esp32serial.error("This is an error!");

        vTaskDelay(200 / portTICK_PERIOD_MS);
    }
}
