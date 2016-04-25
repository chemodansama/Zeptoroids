/*
 * Asteroid.cpp
 *
 *  Created on: 10.08.2013
 *      Author: NullPointer
 */

#include "Asteroid.h"

#include <GLES/gl.h>
#include <math.h>
#include <memory>
#include "Utils.h"

namespace zeptoroids {

Asteroid::Asteroid(const AsteroidTemplate &_template, float x, float y,
        float scale, int compound, float vx, float vy)
        : template_(_template)
        , x(x)
        , y(y)
        , scale(scale)
        , compound(compound)
        , vx(vx), vy(vy) {
}

void Asteroid::Update(float w, float h) {
	x += vx;
	y += vy;

	x = Utils::CycleCoords(x, w);
	y = Utils::CycleCoords(y, h);
}

bool Asteroid::IsInside(float x, float y) const {
	return template_.IsInside((x - this->x) / scale, (y - this->y) / scale);
}

void Asteroid::Render(float w, float h) const {
	if (template_.GetBBox().Right() * scale + x > w) {
		template_.Draw(x - 2 * w, y, scale);
	} else if (template_.GetBBox().Left() * scale + x < -w) {
		template_.Draw(x + 2 * w, y, scale);
	}

	if (template_.GetBBox().Top() * scale + y > h) {
		template_.Draw(x, y - 2 * h, scale);
	} else if (template_.GetBBox().Bottom() * scale + y < -h) {
		template_.Draw(x, y + 2 * h, scale);
	}

	template_.Draw(x, y, scale);
}

std::unique_ptr<Asteroid> Asteroid::Spawn(const AsteroidTemplate &_template) {
	if (compound <= 0) {
		return 0;
	}

	float angle = Utils::Randf(-20 * M_PI / 180, 20 * M_PI / 180);
	float c = cos(angle);
	float s = sin(angle);
	float vvx = vx * c - vy * s;
	float vvy = vx * s + vy * c;

	return Utils::make_unique<Asteroid>(_template,
			x, y, scale / 2, compound - 1, vvx * 1.25f, vvy * 1.25f);
}

} /* namespace zeptoroids */
