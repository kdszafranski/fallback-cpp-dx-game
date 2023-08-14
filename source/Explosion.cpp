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
	// auto is a copy... need the ref to change values
	for (auto& part : particles) {
		part.update(deltaTime);
		float x = part.getX();
		x += deltaTime * part.getVelocity().x;
		float y = part.getY();
		y += deltaTime * part.getVelocity().y;
		part.setX(x);
		part.setY(y);
	}

	// remove.. like JS filter
	//for (std::list<Entity>::iterator it = particles.begin(); it != particles.end(); it++)
	//{
	//		it = particles.erase(it);
	//	}
	//}

	std::list<Entity>::iterator it = particles.begin();
	while (it != particles.end()) {
		if (it->getX() > GAME_WIDTH) {
			particles.erase(it++);
		} else {
			++it;
		}
	}


}



void Explosion::draw()
{
	for (auto part : particles) {
		part.draw();
	}
}

