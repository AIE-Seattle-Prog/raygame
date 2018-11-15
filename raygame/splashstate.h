#pragma once

#include "gamestate.h"

#include <cmath>

class splashstate : public gamestate
{
    float duration;
    float timeLimit;

public:
    splashstate()
    {
        duration = 0.0f;
        timeLimit = 3.0f;
    }

    virtual void tick(float deltaTime)
    {
        duration += deltaTime;
    }

    virtual void draw()
    {
        const int fontSize = 20;

        int xPos = GetScreenWidth() / 2 - MeasureText("TERREHBYTE GAMES", fontSize) / 2;
        int yPos = GetScreenHeight() * 0.5f + (sinf(duration * 4.0f) * (GetScreenHeight() * 0.3f));
        DrawText("TERREHBYTE GAMES", xPos, yPos, fontSize, DARKBLUE );
    }

    virtual GameStates next()
    {
        if(duration >= timeLimit) { return GameStates::MENU; }  
        return GameStates::SPLASH;
    }
};