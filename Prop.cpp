#include "Prop.h"
#include "raymath.h"

Prop::Prop(Vector2 pos, Texture2D tex)
{
    // Code.
    worldPos = pos;
    texture = tex;
}

void Prop::Rander(Vector2 knightPos)
{
    Vector2 screenPos{Vector2Subtract(worldPos, knightPos)};
    DrawTextureEx(texture, screenPos, 0.f, scale, WHITE);
}

Rectangle Prop::getCollisionRec(Vector2 knightPos)
{
    Vector2 screenPos{Vector2Subtract(worldPos, knightPos)};
    return Rectangle{
        screenPos.x,
        screenPos.y,
        texture.width * localCollisionWidth,
        texture.height * localCollisionHeight};
}

void Prop::SetCollisionScale(float width, float height)
{
    localCollisionWidth = scale / width;
    localCollisionHeight = scale / height;
}

void Prop::Destroy()
{
    UnloadTexture(texture);
}