#include "Explosion.h"
#include <time.h>

Explosion::Explosion()
{
	position = { 0,0 };
	partId = 0;
}

Explosion::~Explosion()
{
	particles.clear();
}

void Explosion::spawnExplosion(Game* game, TextureManager* texture, VECTOR2 pos)
{
	srand((unsigned)time(0));
	position = pos;
	partId++;
	if (partId > 1000) {
		partId = 0;
	}

	const int numberToSpawn = rand() % 10 + 16;
	for (int i = 0; i < numberToSpawn; i++) {
		Entity particle;

		if (!particle.initialize(game, 16, 16, 4, texture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing explosion image"));

		particle.myId = partId;
		particle.setActive(false); // no collisions
		particle.setPosition(position); // starts at Block center

		if (rand() % 100 < 30) {
			// L shapes
			particle.setCurrentFrame(3);
			particle.setScale(0.75);
		} else {
			// squares
			particle.setCurrentFrame(2);
			particle.setScale(0.25);
		}

		// set the direction
		float x = rand() % 90;
		float y = rand() % 90;
		// chance to flip around each axis
		if (rand() % 100 < 50) x = -x;
		if (rand() % 100 < 50) y = -y;

		// set it in motion and speed it up
		particle.setVelocity({ x * 3, y * 3 });
		
		// apply one of the block colors for the duration of this particle
		particle.setColorFilter(particle.getRandomColor());

		particles.push_back(particle);
	}
}

void Explosion::update(float deltaTime)
{
	// iterator is just that, the number
	std::list<Entity>::iterator it = particles.begin();
	while (it != particles.end()) {
		if (it->getX() > GAME_WIDTH || it->getX() < 0 ||
			it->getY() > GAME_HEIGHT || it->getY() < 0
			) {
			// it++ here advances the iterator to the next one after the erasure
			// so we can erase the current item.. what if it's end()?
			particles.erase(it++);
		} else {
			it->update(deltaTime);
			float x = it->getX();
			x += deltaTime * it->getVelocity().x;
			float y = it->getY();
			y += deltaTime * it->getVelocity().y;
			it->setX(x);
			it->setY(y);

			// spin the L shapes
			if (it->getCurrentFrame() == 3) {
				it->setDegrees(it->getDegrees() + deltaTime * 360);
			}

			++it;
		}
	}
}

void Explosion::draw()
{
	for (auto& part : particles) {
		part.draw(part.getColorFilter());
	}
}

void Explosion::clearAllParticles()
{
	particles.clear();
}
