/*
 * Spaceship.h
 *
 *  Created on: 11.08.2013
 *      Author: NullPointer
 */

#ifndef SPACESHIP_H_
#define SPACESHIP_H_

#include <vector>
#include <list>
#include <GLES/gl.h>

#include "BBox.h"
#include "Asteroid.h"

namespace zeptoroids {

class Spaceship {
public:
	Spaceship(const std::vector<GLfloat> &vertices,
			const std::vector<GLushort> &indices,
			const std::vector<GLushort> &flame,
			float scale);

	void Draw(float w, float h);
	void Update(int stepsPerSec, float w, float h);

	bool HasCollision(const Asteroid *asteroid);

	void TurnLeft();
	void TurnRight();
	void TurnStopLeft();
	void TurnStopRight();

    bool HasInvulnerability();

	void Forward();
	void Stop();

	float GetX() { return x; }
	float GetY() { return y; }
	float GetAngle() { return angle; }

private:
	const std::vector<GLfloat> &vertices;
	const std::vector<GLushort> &indices;
	const std::vector<GLushort> &flame;

	float x;
	float y;
	float angle;

	float scale;

	bool turnLeft;
	bool turnRight;
	bool forward;

	float velocity;
	long birthTime;

	BBox bbox;

	void DrawAt(float x, float y);
};

} /* namespace zeptoroids */
#endif /* SPACESHIP_H_ */
