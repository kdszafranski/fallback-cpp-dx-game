#pragma once
#include <list>
#include "textureManager.h"
#include "entity.h"

class Explosion 
{
    int partId;
    VECTOR2 position;
    TextureManager texture;
    std::list<Entity> particles;

public:
    // construction
    Explosion();
    ~Explosion();
    void spawnExplosion(Game* game, TextureManager* texture, VECTOR2 position);
    
    // lifecycle
    void update(float deltaTime);
    void draw();
    void clearAllParticles();

    // accessor
    int getParticleCount() { return particles.size(); }
};

