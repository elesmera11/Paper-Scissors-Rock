/**
 * Code for displaying peripheral messages to the main rock, paper,
 * scissors game. Created for 2017 ENCE260 assignment.
 *
 * @Authors Kate Chamberlin (54384616), Jack Steel (94921224)
 * @Date 10 Oct 2017
 */


#include "tinygl.h"
#include "textDisplay.h"
#include "font3x5_1.h"
#include "font5x7_rps.h"
#include "ir_uart.h"


#define MESSAGE_RATE 30


static uint8_t counter;
static char clockfaces[8] = {'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K'};
static uint8_t current_face;


/**
 * Display winning message on this AVR
 * @Params void
 * @Return void
 */
void disp_you_win(void)
{
    tinygl_clear();
    tinygl_text(" YOU WIN! USE BUTTON TO RESTART");
}


/**
 * Display losing message on this AVR
 * @Params void
 * @Return void
 */
void disp_you_lose(void)
{
    tinygl_clear();
    tinygl_text(" YOU LOSE! USE BUTTON TO RESTART");
}


/**
 * Display game starting message on this AVR
 * @Params void
 * @Return void
 */
void disp_start(void)
{
	tinygl_clear();
	tinygl_text(" START GAME WITH THE NAV SWITCH");
}


/**
 * Display clock image sequence on this AVR
 * @Params void
 * @Return void
 */
void waiting_init(void)
{
    configure_tinygl(RPS_CONFIG);
    current_face = 0;
    counter = 0;
    tinygl_draw_char(clockfaces[current_face], tinygl_point(0,0));
}


/**
 * Updates clock image sequence on this AVR
 * @Params void
 * @Return void
 */
void waiting_update(void)
{
    if (counter++ == 30) {
        counter = 0;
        current_face++;
        if (current_face > 7) {
            current_face = 0;
        }
        tinygl_draw_char(clockfaces[current_face], tinygl_point(0,0));
    }
}


/**
 * Display the current rock, paper, scissors selection on this AVR
 * @Params selection the selection that will be displayed
 * @Return void
 */
void display_choice(selection_t selection)
{
    if (selection == SELECTION_PAPER) {
        tinygl_draw_char('A', tinygl_point(0,0));
    } else if (selection == SELECTION_SCISSORS) {
        tinygl_draw_char('B', tinygl_point(0,0));
    } else if (selection == SELECTION_ROCK) {
        tinygl_draw_char('C', tinygl_point(0,0));
    }
}


/**
 * Configures the tinygl util to display either scrolling text or
 * pixel images of paper/scissors/rock.
 * @Param	configuration	the wanted configuration for displaying
 * @Return	void
 */
void configure_tinygl(tinygl_config configuration)
{
    if (configuration == RPS_CONFIG) {          //image configuration
        tinygl_clear();
        tinygl_text_speed_set(MESSAGE_RATE);
        tinygl_font_set(&font5x7_rps);
        tinygl_text_dir_set(TINYGL_TEXT_DIR_NORMAL);
        tinygl_text_mode_set(TINYGL_TEXT_MODE_STEP);
    } else if (configuration == TEXT_CONFIG) {  //text configuration
        tinygl_clear();
        tinygl_text_speed_set(MESSAGE_RATE);
        tinygl_font_set(&font3x5_1);
        tinygl_text_dir_set(TINYGL_TEXT_DIR_ROTATE);
        tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
    }
}
