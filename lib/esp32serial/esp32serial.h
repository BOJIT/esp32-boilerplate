/**
 * @file
 * @brief headers for esp32serial library
 *
 * @author @htmlonly &copy; @endhtmlonly 2021 James Bennion-Pedley
 *
 * @date 09 June 2021
 */

#ifndef __ESP32SERIAL__
#define __ESP32SERIAL__

#include <stdlib.h>
#include <stdbool.h>

/*------------------------- Public Macros and Structs ------------------------*/

/** @brief Debug Levels */
#define DEBUG_OFF       0
#define DEBUG_ERRORS    1
#define DEBUG_WARNINGS  2
#define DEBUG_INFO      3

/** @brief Debug Level Colours (overrideable) */
#ifndef DEBUG_U

/*----------------------------- Private Functions ----------------------------*/

class Esp32Serial {
private:
    QueueHandle_t _debugQueue;

    bool _colour;

    void _debugHandler(void *args __attribute((unused)));

    static void _debugWrapper(void* param) {
        static_cast<Esp32Serial*>(param)->_debugHandler(param);
    }

    int _debugSend(int code, ...);

public:
    TaskHandle_t debugTask;

    Esp32Serial(const uint baud, size_t queue_length = 10, bool colour = false);
    ~Esp32Serial(void);

    int info(...);
    int warning(...);
    int error(...);

};

#endif /* __ESP32SERIAL__ */
