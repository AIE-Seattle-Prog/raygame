#include "gamestate.h"

#include "splashstate.h"
#include "menustate.h"
#include "wariostate.h"
#include "endstate.h"

#include <cassert>

void setupGameState(gamestate *&ptr, GameStates newState)
{
    switch(newState)
    {
        case GameStates::NONE:  ptr = new gamestate();  break;
        case GameStates::SPLASH: ptr = new splashstate(); break;
        case GameStates::MENU:  ptr = new menustate();  break;
        case GameStates::WARIO: ptr = new wariostate(); break;
        case GameStates::END:   ptr = new endstate();   break;
        default: assert(false && "Invalid state specified.");
    }
}