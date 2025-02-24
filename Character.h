#ifndef CHARACTER_H
#define CHARACTER_H

#include "raylib.h"
#include "BaseCharacter.h"

class Character : public BaseCharacter
{

public:
    Character(int winWidth, int winHeight);
    virtual void Tick(float deltaTime) override;
    virtual Vector2 getScreenPos() override;
    virtual void Destroy() override;

    Vector2 Input();
    void takeDamage(float damage);

private:
    int windowWidth{};
    int windowHeight{};
    Texture2D weapon{LoadTexture("characters/weapon_sword.png")};
    Rectangle weaponCollisionRec{};
    float health{100};
    int EnemyKillCount{0};

public:
    Rectangle getWeaponCollisionRec() { return weaponCollisionRec; }
    float getHealth() { return health; }
    void setEnemyKillCount(int killCount) { EnemyKillCount = killCount; }
    int getEnemyKillCount() { return EnemyKillCount; }
};

#endif