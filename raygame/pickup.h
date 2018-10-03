#pragma once

#include "raylib.h"

class pickup
{
public:
    bool enabled;
    Vector2 position;
    int pointValue;
    Texture2D texture;

    Rectangle getCollider();

    void draw();
};
