/* Sensing Code - Continuous Loop */
#include "main.h"

void sensingTask(void *args __attribute((unused)))
{

    for(;;){

        //DEBUG_MESSAGE(DEBUG_TYPE_INFO, "Hey");
        Serial.println("test");

        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
}
