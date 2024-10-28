// ifdef is used to define the class only one time and use that for all
// this is mostly use when we inhearite one class into multiple place
#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H
#include "raylib.h"

class BaseCharacter
{
public:
    BaseCharacter();
    virtual void Tick(float deltaTime);
    virtual Vector2 getScreenPos() = 0;
    virtual void Destroy();

    void undoMovement();
    Rectangle getCollisionRec();

protected:
    Texture2D texure{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D idle{texure};
    Texture2D run{LoadTexture("characters/knight_run_spritesheet.png")};
    Vector2 worldPos{};
    Vector2 worldPosLastFrame{};

    // 1 : facing right, -1 : facing left
    float rightLeft{1.f};
    // Animation variables
    float runningTime{};
    int frame{};
    int maxFrame{6};
    float updateTime{1.f / 12.f};
    float speed{4.f};
    float Width{};
    float Height{};
    float scale{4.0f};
    Vector2 velocity{};

private:
    bool alive{true};

public:
    Vector2 GetWorldPos() { return worldPos; }
    bool getAlive() { return alive; }
    void SetAlive(bool isAlive) { alive = isAlive; }
};

#endif