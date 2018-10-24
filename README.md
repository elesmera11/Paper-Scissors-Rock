# Paper-Scissors-Rock
Running "make program" while in the correct directory will compile
and run the program on the UCFK. If two UCFKs are connected to the 
computer, running the same command will start both UCFKs if they have
both been reset.

Authors: 
    Kate (elesmera11), Jack (jackodsteel) for ENCE260 (2017),
    and University of Canterbury Computer Science department.
Date: 
    12 Oct 2017

Modulues contained in this folder are:
    scoring.c               Modifies, displays and updates scores
    textDisplay.c           Displays any text/images

Which need the following header files:
    scoring.h
    textDisplay.h
    enums.h

Also needs the additional font:
    font5x7_rps.h

The main program is found in game.c

Note: For optimal trasmission, the closer the boards are together the 
better the signal will be transmitted.

Instructions:
    To beging playing, press the navswitch down.
    Move navswitch up/down until the desired option is displayed, then 
        press the navswitch to choose it.
    At any stage during the selection state you may hold the navswitch to 
        either side to display the score (right) or the round (left).
    Once the game is complete, pressing the button will restart the game.
