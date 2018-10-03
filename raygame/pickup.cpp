#include "pickup.h"

Rectangle pickup::getCollider()
{
    Rectangle rect;

    rect.x = position.x;
    rect.y = position.y;
    rect.width = texture.width;
    rect.height = texture.height;

    return rect;
}

void pickup::draw()
{
    if (!enabled) { return; }

    DrawTexture(texture, position.x, position.y, WHITE);
}
