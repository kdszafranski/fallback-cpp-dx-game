#pragma once
#include <list>
#include "textureManager.h"
#include "entity.h"

class Explosion 
{
    VECTOR2 position;
    TextureManager texture;
    std::list<Entity> particles;

public:
    // construction
    Explosion();
    ~Explosion();
    void spawnExplosion(Game* game, TextureManager* texture, VECTOR2 position);
    
    // lifecycle
    //void spawnExplosion(Vector2 position);
    void update(float deltaTime);
    void draw();
};

