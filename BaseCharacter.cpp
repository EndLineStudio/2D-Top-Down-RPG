#include "BaseCharacter.h"
#include "raymath.h"

BaseCharacter::BaseCharacter()
{
}

void BaseCharacter::Tick(float deltaTime)
{
    worldPosLastFrame = worldPos;

    // update animation frame
    runningTime += deltaTime;
    if (runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.f;
        if (frame > maxFrame)
            frame = 0;
    }

    if (Vector2Length(velocity) != 0.0)
    {
        // set worldPos = worldPos + velocity
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(velocity), speed));

        velocity.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
        texure = run;
    }
    else
    {
        texure = idle;
    }
    velocity = {};

    // draw the character
    Rectangle source{frame * Width, 0.f, rightLeft * Width, Height};
    Rectangle dest{getScreenPos().x, getScreenPos().y, scale * Width, scale * Height};
    DrawTexturePro(texure, source, dest, Vector2{}, 0.f, WHITE);
}

void BaseCharacter::undoMovement()
{
    worldPos = worldPosLastFrame;
}

Rectangle BaseCharacter::getCollisionRec()
{
    return Rectangle{
        getScreenPos().x,
        getScreenPos().y,
        Width * scale,
        Height * scale};
}

void BaseCharacter::Destroy()
{
    UnloadTexture(texure);
    UnloadTexture(idle);
    UnloadTexture(run);
}