#include "raylib.h"
#include "BaseCharacter.h"
#include "Character.h"

class Enemy : public BaseCharacter
{
public:
    Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture);
    virtual void Tick(float deltaTime) override;
    virtual Vector2 getScreenPos() override;

private:
    Character *target{};
    float damagePerSec{10.f};
    float redius{25.f};
    float caseRadius{200.f};

public:
    void SetTarget(Character *character) { target = character; }
};
