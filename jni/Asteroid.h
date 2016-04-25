/*
 * Asteroid.h
 *
 *  Created on: 10.08.2013
 *      Author: NullPointer
 */

#ifndef ASTEROID_H_
#define ASTEROID_H_

#include <memory>
#include "AsteroidTemplate.h"

namespace zeptoroids {

class Asteroid {
public:
	Asteroid(const AsteroidTemplate &_template, float x, float y, float scale,
			int compound, float vx, float vy);

	bool IsInside(float x, float y) const;
	void Update(float w, float h);
	void Render(float w, float h) const;

	int GetScore() { return 200 * scale; }

	std::unique_ptr<Asteroid> Spawn(const AsteroidTemplate&);
private:
	const AsteroidTemplate &template_;
	float x;
	float y;
	float vx;
	float vy;
	float scale;
	int compound;
};

} /* namespace zeptoroids */
#endif /* ASTEROID_H_ */
