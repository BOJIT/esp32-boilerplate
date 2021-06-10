/* Sensing Code - Continuous Loop */
#include "main.h"

void sensingTask(void *args __attribute((unused)))
{

    for(;;){

        log.warning('No %d', 10);

        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
}
