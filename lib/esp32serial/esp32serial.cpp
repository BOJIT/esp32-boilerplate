/**
 * @file
 * @brief Functions for esp32-serial library
 *
 * @author @htmlonly &copy; @endhtmlonly 2021 James Bennion-Pedley
 *
 * @date 09 June 2021
 */

#include "esp32serial.h"

/*------------------------ Private Macros and Structs ------------------------*/


/** @brief Debug Types */
#define DEBUG_TYPE_INFO      'I'
#define DEBUG_TYPE_WARNINGS  'W'
#define DEBUG_TYPE_ERRORS    'E'

#define DEBUG_COLOUR_PREFIX "\u001b["
#define DEBUG_COLOUR_SUFFIX "m"
#define DEBUG_COLOUR_RESET  "\u001b[0m"

/** @brief Debug struct that is added to the message queue */
typedef struct {
    char type;
    char colour[2];
    TaskHandle_t task;
    char* message;
} debug_t;


//temp
QueueHandle_t dbgq;

/*------------------------------ Private Methods -----------------------------*/


void Esp32Serial::_debugHandler(void *args __attribute((unused)))
{
    debug_t debug;

    for(;;) {
        if(dbgq == 0) {
            Serial.println("NULLLL");
        }
        // char buffer[30];
        // sprintf(buffer, "%p\n", (void*)_debugQueue);
        // Serial.print(buffer);
        // Serial.println("Hey");
        // vTaskDelay(1000);
        /* Block until there is an item in the queue */
        xQueueReceive(dbgq, &debug, portMAX_DELAY);

        Serial.println(debug.type);

        // vTaskDelay(1000);
    }
}

int Esp32Serial::_debugSend(int type, char colour[2], va_list args)
{
    int err;
    debug_t debug;

    /* Populate debug message queue */
    debug.type = type;
    debug.colour[0] = colour[0];
    debug.colour[1] = colour[1];

    Serial.println(uxQueueSpacesAvailable(dbgq));

    switch(uxQueueSpacesAvailable(dbgq)) {
        case 0:
            err = -2;
            break;
        case 1:
        {
            debug.task = debugTask;
            xQueueSend(dbgq, &debug, 0);
            err = -1;
            break;
        }
        default:
            debug.task = xTaskGetCurrentTaskHandle();
            xQueueSend(dbgq, &debug, 0);
            err = 0;
            break;
    }
    return err;
}


/*------------------------------- Public Methods -----------------------------*/


Esp32Serial::Esp32Serial(const uint baud, size_t queue_length, bool colour)
{
    /* Initialise Serial communication */
    Serial.begin(baud);

    /* Initialise message queue */
    dbgq = xQueueCreate(queue_length, sizeof(debug_t));

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
        char colour[] = DEBUG_COLOUR_INFO;
        return _debugSend(DEBUG_TYPE_INFO, colour, arglist);
    #else
        return 0;
    #endif
}

int Esp32Serial::warning(...)
{
    #if DEBUG_LEVEL >= DEBUG_WARNING
        va_list arglist;
        char colour[] = DEBUG_COLOUR_INFO;
        return _debugSend(DEBUG_TYPE_WARNINGS, colour, arglist);
    #else
        return 0;
    #endif
}

int Esp32Serial::error(...)
{
    #if DEBUG_LEVEL >= DEBUG_ERROR
        va_list arglist;
        char colour[] = DEBUG_COLOUR_INFO;
        return _debugSend(DEBUG_TYPE_ERRORS, colour, arglist);
    #else
        return 0;
    #endif
}