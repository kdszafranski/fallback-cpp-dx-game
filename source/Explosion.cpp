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

	numberToSpawn = rand() % 10 + 10;
	for (int i = 0; i < numberToSpawn; i++) {
		Entity particle;

		if (!particle.initialize(game, 16, 16, 3, texture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing explosion image"));

		particle.myId = partId;
		particle.setCurrentFrame(2);
		particle.setScale(0.25);
		particle.setActive(false); // no collisions
		particle.setPosition(position);

		float x = rand() % 90;
		float y = rand() % 90;
		if (rand() % 100 < 50) {
			x = -x;
		}
		if (rand() % 100 < 50) {
			y = -y;
		}
		// set it in motion and speed it up
		particle.setVelocity({ x * 3, y * 3 });

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
	D3DXCOLOR color; 
	for (auto &part : particles) {
		float const amount = ((float)rand() / (RAND_MAX + 1));
		color = { 0.75f, amount, 0.5f, 1 };
		part.draw(color);
	}
}

