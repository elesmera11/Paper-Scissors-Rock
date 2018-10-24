/**
 * Defines the common enums used within the other game classes.
 * Created for 2017 ENCE260 assignment.
 *
 * @Authors Kate Chamberlin (54384616), Jack Steel (94921224)
 * @Date 10 Oct 2017
 */

#ifndef ENUMS
#define ENUMS


/**
 * Different selections for rock, paper, scissors.
 */
typedef enum {
    SELECTION_DUMMY,
    SELECTION_PAPER,
    SELECTION_SCISSORS,
    SELECTION_ROCK
} selection_t;


/**
 * Game results
 */
typedef enum {
    RESULT_LOSS,
    RESULT_DRAW,
    RESULT_WIN
} result_t;


/**
 * tinygl configurations
 */
typedef enum {
    RPS_CONFIG,
    TEXT_CONFIG
} tinygl_config;

#endif
