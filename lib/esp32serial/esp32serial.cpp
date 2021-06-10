/**
 * @file
 * @brief Functions for esp32-serial library
 *
 * @author @htmlonly &copy; @endhtmlonly 2021 James Bennion-Pedley
 *
 * @date 09 June 2021
 */

#include "esp32serial.h"

# include <Arduino.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

/*------------------------ Private Macros and Structs ------------------------*/

/** @brief Debug Types */
#define DEBUG_TYPE_INFO     'I'
#define DEBUG_TYPE_WARNING  'W'
#define DEBUG_TYPE_ERROR    'E'

/** @brief Debug struct that is added to the message queue */
typedef struct {
    char type;
    TaskHandle_t task_handle;
    char* message;
} debug_t;

/*----------------------------- Private Functions ----------------------------*/

void Esp32Serial::_debugHandler(void *args __attribute((unused)))
{

}

int _debugSend(int type, va_list args)
{

}

/*------------------------------ Public Functions ----------------------------*/

Esp32Serial::Esp32Serial(const uint baud, size_t queue_length, bool colour)
{
    /* Initialise Serial communication */
    Serial.begin(baud);

    /* Configure colour settings */
    _colour = colour;

    /* Initialise message queue */
    _debugQueue = xQueueCreate(queue_length, sizeof(debug_t));

    /* Create debug task and pass handle back to the user application */
    xTaskCreate(_debugWrapper, "debug", 8192, NULL, 1, &debugTask);
}

Esp32Serial::~Esp32Serial(void)
{
    // TODO free entire queue messages

    vQueueDelete(_debugQueue);

    vTaskDelete(debugTask);

    Serial.end();
}

int Esp32Serial::info(...)
{
    #if DEBUG_LEVEL >= DEBUG_INFO
        va_list arglist;
        return _debugSend(DEBUG_TYPE_INFO, arglist);
    #else
        return 0;
    #endif
}

int Esp32Serial::warning(...)
{
    #if DEBUG_LEVEL >= DEBUG_WARNING
        va_list arglist;
        return _debugSend(DEBUG_TYPE_WARNING, arglist);
    #else
        return 0;
    #endif
}

int Esp32Serial::error(...)
{
    #if DEBUG_LEVEL >= DEBUG_ERROR
        va_list arglist;
        return _debugSend(DEBUG_TYPE_ERROR, arglist);
    #else
        return 0;
    #endif
}