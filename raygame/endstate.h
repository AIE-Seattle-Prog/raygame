#pragma once

#include "gamestate.h"

class endstate : public gamestate
{
    bool readyForNext;

public:
    endstate()
    {
        readyForNext = false;
    }

    virtual void tick(float deltaTime)
    {
        readyForNext = IsMouseButtonPressed(0) || readyForNext;
    }

    virtual void draw()
    {
        const int fontSize = 32;

        int xPos = GetScreenWidth() / 2 - MeasureText("End", fontSize) / 2;
        int yPos = GetScreenHeight() / 2 - fontSize / 2;
        DrawText("End", xPos, yPos, fontSize, DARKBLUE );
    }

    virtual GameStates next()
    {
        if(!readyForNext) { return GameStates::END; }  
        return GameStates::MENU;
    }
};