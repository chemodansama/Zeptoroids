/*
 * Bullets.h
 *
 *  Created on: 12.08.2013
 *      Author: NullPointer
 */

#ifndef BULLETS_H_
#define BULLETS_H_

#include <vector>
#include <GLES/gl.h>
#include <memory>

#include "Asteroid.h"
#include "Explosions.h"

namespace zeptoroids {

class Bullet {
public:
	Bullet(float x, float y, float angle, int stepsPerSecond);

	float GetX() const { return x; }
	float GetY() const { return y; }
	bool IsAlive(long currentTime) const;

	void Update(float w, float h);
private:
	float x;
	float y;
	float vx;
	float vy;
	long birthTime;
};

class Bullets {
private:
    std::list<std::unique_ptr<Bullet>> bullets;
    std::vector<GLfloat> vertices;
    std::vector<Bullet *> removed;

    void operator=(const Bullets &) = delete;
    Bullets(const Bullets &) = delete;

public:
	Bullets();

	void Add(float x, float y, float angle, int stepsPerSecond);
	void Remove(Bullet *);
	void Update(float w, float h);
	void Draw() const;

	auto begin() -> decltype(bullets.begin()) const { return bullets.begin(); }
	auto end() -> decltype(bullets.begin()) const { return bullets.end(); }
};

} /* namespace zeptoroids */
#endif /* BULLETS_H_ */
