
#ifndef DICE_H
#define DICE_H

#include <stdbool.h>

#ifdef DICE_IMPLEMENT
#define _DICEGAME_DEC_
#else
#define _DICEGAME_DEC_ extern
#endif

#define MAX_PLAYER 10
#define MIN_PLAYER 2



_DICEGAME_DEC_ bool isAllPlayerBet( void );
_DICEGAME_DEC_ void gameStart( void );
_DICEGAME_DEC_ void gameSetup( void );

#endif