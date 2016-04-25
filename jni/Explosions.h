/*
 * Explosions.h
 *
 *  Created on: 12.08.2013
 *      Author: NullPointer
 */

#ifndef EXPLOSIONS_H_
#define EXPLOSIONS_H_

#include <vector>
#include <list>
#include <GLES/gl.h>

namespace zeptoroids {

class Explosions {
public:
	Explosions(int stepsPerSec) : stepsPerSec(stepsPerSec) {}
	void AddExplosion(float x, float y);
	void Draw();
	void Update();
private:
	// points per explosion
	static const int N = 32;

	std::vector<GLfloat> vertices;
	std::list<GLfloat> points;
	std::list<GLfloat> velocities;
	std::list<long> births;

	int stepsPerSec;

	void operator=(const Explosions &);
	Explosions(const Explosions &);
};

} /* namespace zeptoroids */
#endif /* EXPLOSIONS_H_ */
