/**
 * @file     font5x7_rps.h
 * @authors  J Steel and K Chamberlin
 * @date     13 Oct 2017
 * @defgroup font5x7_rps  This is a font used to represent images of a 
 * rock, paper, and scissors. Also has a clock face used for waiting.
 */

#ifndef FONT5X7_RPS_H_
#define FONT5X7_RPS_H_

#define FONT5X7_RPS_WIDTH 5
#define FONT5X7_RPS_HEIGHT 7
#define FONT5X7_RPS_OFFSET 65
#define FONT5X7_RPS_SIZE 11

#ifndef FONT_WIDTH
#define FONT_WIDTH 5
#endif
#ifndef FONT_HEIGHT
#define FONT_HEIGHT 7
#endif
#ifndef FONT_OFFSET
#define FONT_OFFSET 65
#endif
#ifndef FONT_SIZE_MAX
#define FONT_SIZE_MAX 11
#endif
#include "font.h"

static font_t font5x7_rps =
{
    .flags = 1, /* (packed)  */
    .width = 5,
    .height = 7,
    .offset = 65,
    .size = 11,
    .bytes = 5,
    .data =
    {
        /* A  */
        0xc0, 0x39, 0xe7, 0x1c, 0x00, 
        /* B  */
        0x51, 0x29, 0x42, 0xf6, 0x06, 
        /* C  */
        0xc0, 0xfd, 0xff, 0x1d, 0x00, 
        /* D  */
        0xc0, 0xc5, 0x1b, 0x1d, 0x00, 
        /* E  */
        0xc0, 0xcd, 0x1a, 0x1d, 0x00, 
        /* F  */
        0xc0, 0xd5, 0x1a, 0x1d, 0x00, 
        /* G  */
        0xc0, 0xe5, 0x1a, 0x1d, 0x00, 
        /* H  */
        0xc0, 0xc5, 0x1e, 0x1d, 0x00, 
        /* I  */
        0xc0, 0xc5, 0x9a, 0x1d, 0x00, 
        /* J  */
        0xc0, 0xc5, 0x5a, 0x1d, 0x00, 
        /* K  */
        0xc0, 0xc5, 0x3a, 0x1d, 0x00, 
    }
};
#endif  /* FONT5X7_RPS_H_  */
