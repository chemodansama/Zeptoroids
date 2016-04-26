/*
 * BBox.h
 *
 *  Created on: 11.08.2013
 *      Author: NullPointer
 */

#ifndef BBOX_H_
#define BBOX_H_

#include <vector>
#include <limits>
#include <GLES/gl.h>

namespace zeptoroids {

class BBox {
public:
    static BBox ComputeBBox(const std::vector<GLfloat> &vertices,
            const std::vector<GLushort> &indices);

    BBox(float x, float y, float ex, float ey) : x(x), y(y), ex(ex), ey(ey) {}
    BBox();

    float GetX() const { return x; }
    float GetY() const { return y; }
    float GetEX() const { return ex; }
    float GetEY() const { return ey; }

    float Left() const { return x - ex; }
    float Right() const { return x + ex; }
    float Top() const { return y + ey; }
    float Bottom() const { return y - ey; }
private:
    // center
    float x;
    float y;

    // extents
    float ex;
    float ey;
};

} /* namespace zeptoroids */
#endif /* BBOX_H_ */
