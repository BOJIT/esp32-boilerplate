/* Using the patented 'OneBigHeaderFile' approach ;).
   This is a small enough project for it to be manageable */

#include <Arduino.h>

#include <esp32serial.h>

extern Esp32Serial log;

void sensingTask(void *args __attribute((unused)));
