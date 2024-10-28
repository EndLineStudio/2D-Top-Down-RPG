#include "Enemy.h"
#include "raymath.h"

Enemy::Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture)
{
    worldPos = pos;
    texure = idle_texture;
    idle = idle_texture;
    run = run_texture;
    Width = texure.width / maxFrame;
    Height = texure.height;
    speed = 2.5f;
}

Vector2 Enemy::getScreenPos()
{
    return Vector2Subtract(worldPos, target->GetWorldPos());
}

void Enemy::Tick(float deltaTime)
{
    if (!getAlive())
        return;

    // get toTarget
    velocity = Vector2Subtract(target->getScreenPos(), getScreenPos());
    if (Vector2Length(velocity) < redius || Vector2Length(velocity) > caseRadius)
        velocity = {};

    BaseCharacter::Tick(deltaTime);

    if (CheckCollisionRecs(target->getCollisionRec(), getCollisionRec()))
    {
        target->takeDamage(damagePerSec * deltaTime);
    }
}