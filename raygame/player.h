#pragma once

#include "raylib.h"

class player
{
public:
    Vector2 position;
    Texture2D texture;

    float speed;
    int score;

    Rectangle getCollider();

    void update();
    void draw();
};