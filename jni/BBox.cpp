/*
 * BBox.cpp
 *
 *  Created on: 11.08.2013
 *      Author: NullPointer
 */

#include "BBox.h"

namespace zeptoroids {

BBox BBox::ComputeBBox(const std::vector<GLfloat> &vertices,
		const std::vector<GLushort> &indices) {
	if (indices.size() == 0) {
		return BBox(0, 0, 0, 0);
	}

	float maxx = vertices[indices[0] * 2];
	float maxy = vertices[indices[0] * 2 + 1];

	float minx = maxx;
	float miny = maxy;

	for (auto it = indices.begin(); it != indices.end(); ++it) {
		auto i = *it;
		float x = vertices[i * 2 + 0];
		float y = vertices[i * 2 + 1];

		maxx = maxx > x ? maxx : x;
		maxy = maxy > y ? maxy : y;

		minx = minx > x ? x : minx;
		miny = miny > y ? y : miny;
	}

	float ex = (maxx - minx) / 2;
	float ey = (maxy - miny) / 2;
	return BBox(minx + ex, miny + ey, ex, ey);
}

BBox::BBox()
        : x(0)
        , y(0)
        , ex(std::numeric_limits<float>::max())
        , ey(std::numeric_limits<float>::max()) {
}

} /* namespace zeptoroids */
