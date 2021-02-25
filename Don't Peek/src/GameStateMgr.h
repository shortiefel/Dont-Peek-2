#pragma once

#ifndef GAME_STATE_MGR_H
#define GAME_STATE_MGR_H

//---------HEADERS--------

#include "AEEngine.h"
#include "GameStateList.h"


///-------------------EXTERNS----------------

extern unsigned int gGameStateInit;
extern unsigned int gGameStateCurr;
extern unsigned int gGameStatePrev;
extern unsigned int gGameStateNext;

////---------------------------------------------

extern void (*GameStateLoad)();
extern void (*GameStateInit)();
extern void (*GameStateUpdate)();
extern void (*GameStateDraw)();
extern void (*GameStateFree)();
extern void (*GameStateUnload)();

/////-----------------FUNCTION PROTOTYPES---------------

// call this at the beginning and AFTER all game states are added to the manager
void GameStateMgrInit(unsigned int gameStateInit);

// update is used to set the function pointers
void GameStateMgrUpdate();

#endif
