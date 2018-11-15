#pragma once

#include "gamestate.h"
#include <string>

class wariostate : public gamestate
{
    float duration;
    float timeLimit;

    bool clicked;

public:

    wariostate()
    {
        duration = 0.0f;
        timeLimit = 4.0f;

        clicked = false;
    }

    virtual void tick(float deltaTime)
    {
        duration += deltaTime;
    }

    virtual void draw()
    {
        const int fontSize = 32;

        if(!clicked)
        {
            int xPos = GetScreenWidth() / 2 - MeasureText("Right Click the Thing", fontSize) / 2;
            int yPos = GetScreenHeight() / 2 - fontSize / 2;
            DrawText("Right Click the Thing", xPos, yPos, fontSize, DARKBLUE );
        }
        else
        {
            int xPos = GetScreenWidth() / 2 - MeasureText("Yaaaaaay", fontSize) / 2;
            int yPos = GetScreenHeight() / 2 - fontSize / 2;
            DrawText("Yaaaaaay", xPos, yPos, fontSize, DARKBLUE );
        }

        clicked = IsMouseButtonPressed(1) || clicked;

        // draw timer
        auto text = std::to_string(floor(timeLimit - duration));
        text = text.substr(0, text.find('.'));

        int xPos = GetScreenWidth() / 2 - MeasureText(text.c_str(), fontSize) / 2;
        int yPos = GetScreenHeight() * 0.9f;
        DrawText(text.c_str(), xPos, yPos, fontSize, DARKBLUE );
    }

    virtual GameStates next()
    {
        if(duration >= timeLimit) { return GameStates::END; }
        else                      { return GameStates::WARIO; }
    }
};