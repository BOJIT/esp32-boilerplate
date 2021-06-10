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

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

/*------------------------- Public Macros and Structs ------------------------*/

/** @brief Debug Levels */
#define DEBUG_OFF       0
#define DEBUG_ERRORS    1
#define DEBUG_WARNINGS  2
#define DEBUG_INFO      3

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

/**
 * @brief Internal function used to allocate memory for the error string.
 * @param debug_type level of debugging (handled by preprocessor).
 *
 * @retval true if message should be logged, false if not.
 */
bool debug_check_level(char debug_type);

/**
 * @brief Internal function used add debug message to the queue.
 * @param debug debug struct that is passed to the queue.
 */
void debug_send_message(debug_t debug);

/*------------------------------ Public Functions ----------------------------*/

/**
 * @brief Add debug message to output queue.
 * @param debug_type debug message type - see Debug Types.
 * @param __VA_ARGS__ printf-style arguments.
 */
#ifdef DEBUG_LEVEL
#if DEBUG_LEVEL >= DEBUG_ERRORS
    #define DEBUG_MESSAGE(debug_type, ...) do { \
            debug_t debug; \
            if(debug_check_level(debug_type)) { \
                debug.type = debug_type; \
                debug.message = NULL; \
                debug_send_message(debug); \
            } \
        } while(0)

        // (char*)pvPortMalloc(snprintf(NULL, 0, __VA_ARGS__));
        // sprintf(debug.message, __VA_ARGS__);
#else
    #define DEBUG_MESSAGE(debug_type, message)
#endif /* DEBUG_LEVEL >= DEBUG_ERRORS */
#else
    /* The existence of DEBUG_LEVEL is only checked here. */
    #error "No Debug Level Defined!!!"
#endif /* DEBUG_LEVEL */

/**
 * @brief Initialise the queues and tasks associated with the debug handler.
 * @param queue_length defines the length of the message queue. While the a long
 * message queue does not use up much memory, the dynamically allocated message
 * strings that the queue items point to do. Keep as low as possible.
 * @param init_func function pointer to a function that initialises the output
 * means that send_func uses to do the logging.
 * @param send_func function pointer to a function that sends one char in a
 * non-blocking manner.
 *
 * @retval pointer to handle of the task that was created to handle debugging.
 */
TaskHandle_t* debugInitialise(size_t queue_length, void (*init_func)(void),
                                                    void (*send_func)(char));

#endif /* __ESP32SERIAL__ */
