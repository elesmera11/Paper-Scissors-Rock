/**
 * Code for displaying peripheral messages for rounds and scoring to the
 * main rock, paper, scissors game. Created for 2017 ENCE260 assignment.
 *
 * @Authors Kate Chamberlin (54384616), Jack Steel (94921224)
 * @Date 10 Oct 2017
 */


#include "system.h"
#include "pacer.h"
#include "tinygl.h"
#include "scoring.h"
#include "navswitch.h"
#include "textDisplay.h"
#include <stdio.h>


/**
 * Returns the score as a string.
 * @Param	p1_score	the score of the player on this avr
 * 			p2_score	the score of the player on other avr
 * @Return	char*
 */
char* curr_score(uint8_t p1_score, uint8_t p2_score)
{
    //local inits
    char* score_str = " n:n";

    //formatting number of rounds into string
    sprintf(score_str, " %d:%d", p1_score, p2_score);

    return score_str;
}


/**
 * Displays the current score on the LED matrix, relative to the
 * player on this avr. Displays when player presses the navswitch
 * to the right (relative to the rotation of the text).
 * @Param	choice		the paper, scissors or rock choice of this avr
 * 			p1_score	the current score of this avr
 * 			p2_score	the current score of other avr
 * @Return	void
 */
void p1_show_score(uint8_t p1_score, uint8_t p2_score)
{
    tinygl_text(curr_score(p1_score, p2_score));
}


/**
 * Returns the current round as a string.
 * @Param	p1_score	the current score of this avr
 * 			p2_score	the current score of other avr
 * 			draws		the number of draws had.
 * @Return	char*
 */
char* curr_round(uint8_t p1_score, uint8_t p2_score, uint8_t draws)
{
    //local inits
    char* round_str = " ROUND n";
    uint8_t total_score = p1_score + p2_score + draws;

    //formatting number of rounds into string
    sprintf(round_str, " ROUND %d", total_score + 1);

    return round_str;
}


/**
 * Displays the current round on the LED matrix. Displays when player
 * presses the navswitch to the left (relative to the rotation of
 * the text).
 * @Param	choice		the paper, scissors or rock choice of this avr
 * 			p1_score	the current score of this avr
 * 			p2_score	the current score of other avr
 * 			draws		the number of draws had
 * @Return	void
 */
void p1_show_round(uint8_t p1_score, uint8_t p2_score, uint8_t draws)
{
    tinygl_text(curr_round(p1_score, p2_score, draws));
}


/**
 * Calculates the winner of a round using generic rock, paper, scissors
 * rules i.e. rock beats scissors.
 * @Param	p1_choice	the current r/p/s selection of this avr
 * 			p2_choice	the current r/p/s selection of other avr
 * @Return	game_wdl    the result_t enum calculated i.e. WIN
 */
result_t get_outcome(selection_t p1_choice, selection_t p2_choice)
{
    int8_t result = p1_choice - p2_choice;
    switch (result) {
    case 0:
        return(RESULT_DRAW);
    case 1:
    case -2:
        return(RESULT_WIN);
    case -1:
    case 2:
        return(RESULT_LOSS);
    default:
        return RESULT_DRAW;
    }
}
