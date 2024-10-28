#include "raylib.h"

class Prop
{
public:
    Prop(Vector2 pos, Texture2D tex);
    void Rander(Vector2 knightPos);
    Rectangle getCollisionRec(Vector2 knightPos);
    void SetCollisionScale(float width,float height);
    void Destroy();
private:
    Texture2D texture{};
    Vector2 worldPos{};
    float scale{2.f};
    float localCollisionWidth{};
    float localCollisionHeight{};
};
