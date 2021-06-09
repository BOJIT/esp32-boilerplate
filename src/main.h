/* Using the patented 'OneBigHeaderFile' approach ;).
   This is a small enough project for it to be manageable */

#include <Arduino.h>

#include <FreeRTOS-Debug.h>

void sensingTask(void *args __attribute((unused)));