/**
 * Code for displaying peripheral messages to the main rock, paper,
 * scissors game. Created for 2017 ENCE260 assignment.
 *
 * @Authors Kate Chamberlin (54384616), Jack Steel (94921224)
 * @Date 10 Oct 2017
 */


#include "system.h"
#include "tinygl.h"
#include "pacer.h"
#include "font3x5_1.h"
#include "font5x7_rps.h"
#include "enums.h"


#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H


/**
 * Display winning message on this AVR
 * @Params void
 * @Return void
 */
void disp_you_win(void);


/**
 * Display losing message on this AVR
 * @Params void
 * @Return void
 */
void disp_you_lose(void);


/**
 * Display game starting message on this AVR
 * @Params void
 * @Return void
 */
void disp_start(void);


/**
 * Display waiting message on this AVR
 * @Params void
 * @Return void
 */
void waiting_init(void);


/**
 * Updates clock image sequence on this AVR
 * @Params void
 * @Return void
 */
void waiting_update(void);


/**
 * Display the current rock, paper, scissors selection on this AVR
 * @Params selection the selection that will be displayed
 * @Return void
 */
void display_choice(selection_t selection);


/**
 * Configures the tinygl util to display either scrolling text or
 * pixel images of paper/scissors/rock.
 * @Params	configuration	the wanted configuration for displaying
 * @Return	void
 */
void configure_tinygl(tinygl_config configuration);


#endif
