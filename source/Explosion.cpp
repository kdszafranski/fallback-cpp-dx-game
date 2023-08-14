#include "Explosion.h"
#include <time.h>

Explosion::Explosion()
{
	position = { 0,0 };
}

Explosion::~Explosion()
{
	particles.clear();
}

void Explosion::spawnExplosion(Game* game, TextureManager* texture, Vector2 pos)
{
	//srand((unsigned)time(0));
	position = pos;
	int numberToSpawn = 0;

	numberToSpawn = rand() % 10 + 5;
	Vector2 position = { GAME_WIDTH, rand() % GAME_HEIGHT };
	for (int i = 0; i < numberToSpawn; i++) {
		Entity particle;

		if (!particle.initialize(game, 32, 2, 3, texture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing explosion image"));
		
		particle.setCurrentFrame(2);
		particle.setActive(false); // no collisions
		particle.setPosition(position);
		particle.setVelocity(VECTOR2(rand() % 360, rand() % 360));

		particles.push_back(particle);
	}
}

void Explosion::update(float deltaTime)
{
	for (Entity part : particles) {
		float x = part.getX() + deltaTime * part.getVelocity().x;
		float y = part.getY() + deltaTime * part.getVelocity().y;
		part.update(deltaTime);
		part.setPosition(x, y);		
	}
}

void Explosion::draw()
{
	for (Entity part : particles) {
		part.draw();
	}
}

