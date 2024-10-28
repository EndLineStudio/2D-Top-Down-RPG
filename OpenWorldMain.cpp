#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Enemy.h"
#include "Prop.h"
#include <string>

int main()
{
    const int WindowWidth{512};
    const int WindowHeight{512};
    int count{};
    bool IsGameOver{false};

    InitWindow(WindowWidth, WindowHeight, "Top-Down RPG");

    Texture2D Map = LoadTexture("nature_tileset/EmptyMap.png");
    Vector2 mapPos{0.0, 0.0};
    const float mapScale{2.0f};

    // Create player character
    Character Knight{WindowWidth, WindowHeight};
    // create enemy character
    Enemy goblin{
        Vector2{800.f, 900.f},
        LoadTexture("characters/goblin_idle_spritesheet.png"),
        LoadTexture("characters/goblin_run_spritesheet.png"),
    };

    Enemy goblin1{
        Vector2{900.f, 200.f},
        LoadTexture("characters/goblin_idle_spritesheet.png"),
        LoadTexture("characters/goblin_run_spritesheet.png"),
    };

    Enemy slime{
        Vector2{300.f, 1100.f},
        LoadTexture("characters/slime_idle_spritesheet.png"),
        LoadTexture("characters/slime_run_spritesheet.png"),
    };

    Enemy slime1{
        Vector2{1000.f, 500.f},
        LoadTexture("characters/slime_idle_spritesheet.png"),
        LoadTexture("characters/slime_run_spritesheet.png"),
    };

    Enemy *enemies[]{
        &goblin,
        &slime,
        &goblin1,
        &slime1};

    for (auto enemy : enemies)
    {
        enemy->SetTarget(&Knight);
        count++;
    }

    Prop props[11]{
        Prop{Vector2{1100.f, 1200.f}, LoadTexture("nature_tileset/BigRock.png")},
        Prop{Vector2{630.f, 310.f}, LoadTexture("nature_tileset/Boul.png")},
        Prop{Vector2{-30.f, -210.f}, LoadTexture("nature_tileset/Tree.png")},
        Prop{Vector2{0.f, 130.f}, LoadTexture("nature_tileset/Table.png")},
        Prop{Vector2{0.f, 255.f}, LoadTexture("nature_tileset/Table.png")},
        Prop{Vector2{0.f, 390.f}, LoadTexture("nature_tileset/Table.png")},
        Prop{Vector2{1300.f, 520.f}, LoadTexture("nature_tileset/Water_Well.png")},
        Prop{Vector2{80.f, 480.f}, LoadTexture("nature_tileset/statue.png")},
        Prop{Vector2{1100.f, 100.f}, LoadTexture("nature_tileset/statueWithground.png")},
        Prop{Vector2{200.f, 1150.f}, LoadTexture("nature_tileset/grave.png")},
        Prop{Vector2{700.f, 950.f}, LoadTexture("nature_tileset/TreserBox.png")}};
    props[0].SetCollisionScale(1.2f, 2.f);
    props[1].SetCollisionScale(1.2f, 2.f);
    props[2].SetCollisionScale(2.f, 1.2f);
    props[3].SetCollisionScale(1.f, 1.f);
    props[4].SetCollisionScale(1.f, 1.f);
    props[5].SetCollisionScale(1.f, 1.5f);
    props[6].SetCollisionScale(1.f, 2.f);
    props[7].SetCollisionScale(1.5f, 1.5f);
    props[8].SetCollisionScale(1.f, 1.f);
    props[9].SetCollisionScale(1.f, 1.f);
    props[10].SetCollisionScale(1.f, 2.f);

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        mapPos = Vector2Scale(Knight.GetWorldPos(), -1.f);

        // draw the map.
        DrawTextureEx(Map, mapPos, 0.0, mapScale, WHITE);

        // draw the props
        for (auto prop : props)
        {
            prop.Rander(Knight.GetWorldPos());
        }

        if (!Knight.getAlive() || IsGameOver) // character is not alive case
        {
            DrawText("GAME OVER !", WindowWidth / 4, WindowHeight / 2, 40, RED);
            EndDrawing();
            continue;
        }
        else // character is alive case
        {
            std::string KnightsHealth = "Health: ";
            KnightsHealth.append(std::to_string(Knight.getHealth()), 0, 5);
            DrawText(KnightsHealth.c_str(), 10.f, 10.f, 30, RED);
        }

        // Character tick function
        Knight.Tick(GetFrameTime());
        // check map bounds
        if (Knight.GetWorldPos().x < -220.f ||
            Knight.GetWorldPos().y < -250.f ||
            Knight.GetWorldPos().x + WindowWidth - 220.f > Map.width * mapScale ||
            Knight.GetWorldPos().y + WindowHeight - 100.f > Map.height * mapScale)
        {
            Knight.undoMovement();
        }
        // check props collisions
        for (auto prop : props)
        {
            if (CheckCollisionRecs(prop.getCollisionRec(Knight.GetWorldPos()), Knight.getCollisionRec()))
            {
                Knight.undoMovement();
            }
        }

        for (auto enemy : enemies)
        {
            enemy->Tick(GetFrameTime());
        }

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            for (auto enemy : enemies)
            {
                if (CheckCollisionRecs(enemy->getCollisionRec(), Knight.getWeaponCollisionRec()))
                {
                    enemy->SetAlive(false);
                    Knight.setEnemyKillCount(Knight.getEnemyKillCount() + 1);
                }
            }
        }
        
        if (count == Knight.getEnemyKillCount())
        {
            IsGameOver = true;
        }
        

        EndDrawing();
    }

    for (auto prop : props)
    {
        prop.Destroy();
    }

    UnloadTexture(Map);
    Knight.Destroy();
    CloseWindow();
}
