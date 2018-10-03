#include "player.h"

Rectangle player::getCollider()
{
    Rectangle rect;

    rect.x = position.x;
    rect.y = position.y;
    rect.width = texture.width;
    rect.height = texture.height;

    return rect;
}

void player::update()
{
    if (IsKeyDown('W'))
    {
        position.y -= speed;
    }
    if (IsKeyDown('S'))
    {
        position.y += speed;
    }
    if (IsKeyDown('A'))
    {
        position.x -= speed;
    }
    if (IsKeyDown('D'))
    {
        position.x += speed;
    }
}

void player::draw()
{
    DrawTexture(texture, position.x, position.y, WHITE);
}
