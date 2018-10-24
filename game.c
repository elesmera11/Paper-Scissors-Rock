/**
 * Main code for rock, paper, scissors game implemented on the UC Fun
 * Kit. Written for 2017 ENCE260 assignment.
 *
 * @Authors Kate Chamberlin (54384616), Jack Steel (94921224)
 * @Date 10 Oct 2017
 */

#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "button.h"
#include "tinygl.h"
#include "ir_uart.h"
#include "scoring.h"
#include "textDisplay.h"
#include "enums.h"
#include "pio.h"
#include "task.h"
#include "tweeter.h"
#include "mmelody.h"
#include <stdbool.h>


//====================================================================//
//=====================enumerations, constants========================//
//====================================================================//


//Connect piezo tweeter to outermost pins of UCFK4 P1 connector.
#define PIEZO_PIO PIO_DEFINE(PORT_D, 6)
#define PIEZO2_PIO PIO_DEFINE(PORT_D, 6)

//define polling rates in Hz.
#define TWEETER_TASK_RATE 5000
#define TUNE_TASK_RATE 100
#define TUNE_BPM_RATE 200
#define NAVSWITCH_TASK_RATE 50
#define GAME_TASK_RATE 100
#define DISPLAY_TASK_RATE 300
#define IR_RECEIVE_TASK_RATE 20
#define VOLUME 50

#define TEXT_SPEED 30
#define SCORE_DURATION (7 * 10 / TEXT_SPEED) * GAME_TASK_RATE

#define POINTS_WIN 3
#define RESET 0


//game states
typedef enum {
    STATE_INIT,
    STATE_SELECTING,
    STATE_WAITING,
    STATE_SHOWING_SCORE,
    STATE_ENDED
} state_t;


//initialise global variables
static tweeter_t tweeter;
static mmelody_t melody;
static mmelody_obj_t melody_info;
static tweeter_obj_t tweeter_info;
static uint8_t p1_score;
static uint8_t p2_score;
static uint8_t draws;
static selection_t selection;
static selection_t p2_choice;
static selection_t p1_choice;
static state_t game_state;
static bool showing_status;
static uint8_t counter;


//====================================================================//
//=======================peripheral functions=========================//
//====================================================================//


/**
 * reset each individual round
 */
static void reset_round(void)
{
    p1_choice = SELECTION_DUMMY;
    p2_choice = SELECTION_DUMMY;
    selection = SELECTION_PAPER;
    game_state = STATE_SELECTING;
    configure_tinygl(RPS_CONFIG);
    display_choice(selection);
}


/**
 * reset entire game
 */
static void reset(void)
{
    tinygl_clear();
    p1_score = RESET;
    p2_score = RESET;
    draws = RESET;
    showing_status = false;
    counter = 0;
    reset_round();
    game_state = STATE_INIT;
    configure_tinygl(TEXT_CONFIG);
    disp_start();
    mmelody_play(melody, "");
}


/**
 * initialise tweeter task
 */
static void tweeter_task_init(void)
{
    static tweeter_scale_t scale_table[] = TWEETER_SCALE_TABLE(TWEETER_TASK_RATE);
    tweeter = tweeter_init(&tweeter_info, TWEETER_TASK_RATE, scale_table);
    pio_config_set(PIEZO_PIO, PIO_OUTPUT_LOW);
}


/**
 * change pio settings dependent on tweeter task
 */
static void tweeter_task(__unused__ void *data)
{
    pio_output_set(PIEZO_PIO, tweeter_update(tweeter));
}


/**
 * initialise tune task
 */
static void tune_task_init(void)
{
    melody = mmelody_init(&melody_info, 
                          TUNE_TASK_RATE,
                          (mmelody_callback_t) tweeter_note_play, 
                          tweeter);
    mmelody_speed_set(melody, TUNE_BPM_RATE);
    mmelody_volume_set(melody, VOLUME);
}


/**
 * update tone dependent on tune task
 */
static void tune_task(__unused__ void *data)
{
    mmelody_update(melody);
}


/**
 * update the tinygl util
 */
static void display_task(__unused__ void *data)
{
    tinygl_update();
}


/**
 * receive serial data from the IR module
 */
static void ir_receive_task(__unused__ void *data)
{
    if (ir_uart_read_ready_p()) {
        p2_choice = ir_uart_getc();
    }
}


//====================================================================//
//===========================main functions===========================//
//====================================================================//


/**
 * main game task
 */
static void game_task(__unused__ void *data)
{
    navswitch_update();
    button_update();

    //if button is pushed, restart whole program.
    if (button_push_event_p(0)) {
        reset();
    }

    switch (game_state) {
        //if the player is choosing a paper/scissors/rock option
        case STATE_SELECTING:
            //if player holds right, display score
            if (navswitch_down_p(NAVSWITCH_NORTH)) {
                if (showing_status == 0) {
                    configure_tinygl(TEXT_CONFIG);
                    p1_show_score(p1_score, p2_score);
                    showing_status = true;
                    return;
                }
            //if player holds left, display round
            } else if (navswitch_down_p(NAVSWITCH_SOUTH)) {
                if (showing_status == 0) {
                    configure_tinygl(TEXT_CONFIG);
                    p1_show_round(p1_score, p2_score, draws);
                    showing_status = true;
                    return;
                }
            //else display current option
            } else if (showing_status == 1) {
                configure_tinygl(RPS_CONFIG);
                display_choice(selection);
                showing_status = false;
                return;
            }

            //loop the selection so can infinitely press up or down (navswitch)
            if (navswitch_push_event_p(NAVSWITCH_WEST)) {
                selection++;
                mmelody_play(melody, "E"); //play note when selection changes up
                if (selection > SELECTION_ROCK) {
                    selection = SELECTION_PAPER;
                }
                display_choice(selection);

            } else if (navswitch_push_event_p(NAVSWITCH_EAST)) {
                selection--;
                mmelody_play(melody, "C"); //play note when selection changes down
                if (selection < SELECTION_PAPER) {
                    selection = SELECTION_ROCK;
                }
                display_choice(selection);
            }

            //if this player selects an option, send it
            if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
                p1_choice = selection;
                configure_tinygl(TEXT_CONFIG);
                waiting_init();
                game_state = STATE_WAITING;
                if (ir_uart_write_ready_p()) {
                    ir_uart_putc(p1_choice);
                }
            }
            break;

        //if waiting for other player to select an option
        case STATE_WAITING:

            //read from ir receiver
            if (p2_choice == SELECTION_DUMMY) {
                waiting_update();
                return;
            }

            //both players have selected an option, calculate winner for round
            result_t outcome = get_outcome(p1_choice, p2_choice);

            //update scores accordingly and play correspoding sound
            if (outcome == RESULT_WIN) {
                mmelody_play(melody, "FA");
                p1_score++;
                outcome = RESET;
            } else if (outcome == RESULT_LOSS) {
                mmelody_play(melody, "AF");
                p2_score++;
                outcome = RESET;
            } else if (outcome == RESULT_DRAW) {
                draws++;
                outcome = RESET;
            }

            //reset the round
            reset_round();
            counter = 0;
            configure_tinygl(TEXT_CONFIG);
            p1_show_score(p1_score, p2_score);
            game_state = STATE_SHOWING_SCORE;

            //if one player has reached 3 points, change game state to ended
            if ((p1_score == POINTS_WIN) || (p2_score == POINTS_WIN)) {
                game_state = STATE_ENDED;
                configure_tinygl(TEXT_CONFIG);
                if (p1_score == POINTS_WIN) {
                    mmelody_play(melody, "CBAB   :");
                    disp_you_win();
                } else if (p2_score == POINTS_WIN) {
                    disp_you_lose();
                }
            }
            break;

        //while showing the overall score
        case STATE_SHOWING_SCORE:
            if (counter++ == SCORE_DURATION) {
                reset_round();
            }
            break;
        
        //opening state
        case STATE_INIT:
            //if the player starts, start
            if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
               reset_round();
            }
            break;
        
        //if the game has finished
        case STATE_ENDED:
            break;
	}
}


int main (void)
{
    //initialise tasks
    task_t tasks[] = {
        {.func = tweeter_task, .period = TASK_RATE / TWEETER_TASK_RATE, .data = 0},
        {.func = tune_task, .period = TASK_RATE / TUNE_TASK_RATE, .data = 0},
        {.func = display_task, .period = TASK_RATE / DISPLAY_TASK_RATE, .data = 0},
        {.func = game_task, .period = TASK_RATE / GAME_TASK_RATE, .data = 0},
        {.func = ir_receive_task, .period = TASK_RATE / IR_RECEIVE_TASK_RATE, .data = 0},
    };

    //all other initialisations
    system_init();
    ir_uart_init();
    button_init();
    navswitch_init();
    tweeter_task_init();
    tune_task_init();
    tinygl_init(DISPLAY_TASK_RATE);
    tinygl_text_speed_set(TEXT_SPEED);
    reset();

    //run tasks
    task_schedule(tasks, ARRAY_SIZE(tasks));

    return 0;
}
