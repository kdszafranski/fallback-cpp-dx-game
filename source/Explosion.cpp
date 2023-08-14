#include "Explosion.h"
#include <time.h>

bool xIsOffScreen(const int& value) {
	return value > GAME_WIDTH || value < 0;
}

bool yIsOffScreen(const int& value) {
	return value > GAME_HEIGHT || value < 0;
}

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
	//srand((unsigned)time(0));
	position = pos;
	partId++;
	int numberToSpawn = 0;

	numberToSpawn = rand() % 10 + 5;
	for (int i = 0; i < numberToSpawn; i++) {
		Entity particle;

		if (!particle.initialize(game, 16, 16, 3, texture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing explosion image"));

		particle.myId = partId;
		particle.setCurrentFrame(2);
		particle.setScale(0.25);
		particle.setActive(false); // no collisions
		particle.setPosition(position);
		particle.setVelocity(VECTOR2(rand() % 180, rand() % 180));

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
			particles.erase(it++);
		} else {
			it->update(deltaTime);
			float x = it->getX();
			x += deltaTime * it->getVelocity().x;
			float y = it->getY();
			y += deltaTime * it->getVelocity().y;

			it->setX(x);
			it->setY(y);
			
			++it;
		}
	}
}



void Explosion::draw()
{
	for (auto &part : particles) {
		part.draw();
	}
}

