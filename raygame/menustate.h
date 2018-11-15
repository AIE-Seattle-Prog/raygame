#pragma once

#include "gamestate.h"


class menustate : public gamestate
{
    bool readyForNext;

public:
    menustate()
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

        int xPos = GetScreenWidth() / 2 - MeasureText("Menu", fontSize) / 2;
        int yPos = GetScreenHeight() / 2 - fontSize / 2;
        DrawText("Menu", xPos, yPos, fontSize, DARKBLUE );
    }

    virtual GameStates next()
    {
        if(readyForNext) { return GameStates::WARIO; }
        else             { return GameStates::MENU; }
    }
};
