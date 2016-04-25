/*
 * AsteroidTemplate.h
 *
 *  Created on: 10.08.2013
 *      Author: NullPointer
 */

#ifndef ASTEROIDTEMPLATE_H_
#define ASTEROIDTEMPLATE_H_

#include <vector>
#include <GLES/gl.h>
#include "BBox.h"

namespace zeptoroids {

class AsteroidTemplate {
public:
	AsteroidTemplate(const std::vector<float> &vertices,
			std::vector<GLushort> indices,
			std::vector<GLushort> renderVertices);

	void Draw(float x, float y, float scale) const;
	bool IsInside(float x, float y) const;

	const BBox &GetBBox() const;

private:
	const std::vector<float> &vertices;
	std::vector<GLushort> indices;
	std::vector<GLushort> renderIndices;

	BBox bbox;
};

} /* namespace zeptoroids */
#endif /* ASTEROIDTEMPLATE_H_ */
