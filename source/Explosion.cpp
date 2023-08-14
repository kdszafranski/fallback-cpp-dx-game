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
	//srand((unsigned)time(0));
	position = pos;
	partId++;
	if (partId > 1000) {
		partId = 0;
	}

	const int numberToSpawn = rand() % 10 + 16;
	for (int i = 0; i < numberToSpawn; i++) {
		Entity particle;

		if (!particle.initialize(game, 16, 16, 3, texture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing explosion image"));

		particle.myId = partId;
		if (rand() % 100 < 50) {
			// frame 2 or 3
			particle.setCurrentFrame(3);
			particle.setScale(0.5);
		} else {
			particle.setCurrentFrame(2);
			particle.setScale(0.25);
		}
		particle.setActive(false); // no collisions
		particle.setPosition(position);

		// set the direction
		float x = rand() % 90;
		float y = rand() % 90;
		// chance to flip around axis
		if (rand() % 100 < 50) x = -x;
		if (rand() % 100 < 50) y = -y;
		// set it in motion and speed it up
		particle.setVelocity({ x * 3, y * 3 });
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
	
	//D3DXCOLOR color = getRandomColor();

	for (auto &part : particles) {
		// produces a glitterly effect on each particle
		//float const amount = ((float)rand() / (RAND_MAX + 1));
		//color = { 0.75f, amount, 0.5f, 1 };
		part.draw(part.getColorFilter());
	}
}
