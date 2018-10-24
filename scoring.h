#include "system.h"
#include "enums.h"


#ifndef SCORING_H
#define SCORING_H


/**
 * Returns the score as a string.
 * @Param	p1_score	the score of the player on this avr
 * 			p2_score	the score of the player on other avr
 * @Return	char*
 */
char* curr_score(uint8_t p1_score, uint8_t p2_score);


/**
 * Displays the current score on the LED matrix, relative to the
 * player on this avr. Displays when player presses the navswitch
 * to the right (relative to the rotation of the text).
 * @Param	choice		the paper, scissors or rock choice of this avr
 * 			p1_score	the current score of this avr
 * 			p2_score	the current score of other avr
 * @Return	void
 */
void p1_show_score(uint8_t p1_score, uint8_t p2_score);


/**
 * Returns the current round as a string.
 * @Param	p1_score	the current score of this avr
 * 			p2_score	the current score of other avr
 * 			draws		the number of draws had.
 * @Return	char*
 */
char* curr_round(uint8_t p1_score, uint8_t p2_score, uint8_t draws);


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
void p1_show_round(uint8_t p1_score, uint8_t p2_score, uint8_t draws);


/**
 * Calculates the winner of a round using generic rock, paper, scissors
 * rules i.e. rock beats scissors.
 * @Param	p1_choice	the current r/p/s selection of this avr
 * 			p2_choice	the current r/p/s selection of other avr
 * @Return	game_wdl    the result_t enum calculated i.e. WIN
 */
result_t get_outcome(selection_t p1_choice, selection_t p2_choice);


#endif
