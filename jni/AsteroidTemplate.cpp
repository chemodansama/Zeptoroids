/*
 * AsteroidTemplate.cpp
 *
 *  Created on: 10.08.2013
 *      Author: NullPointer
 */

#include "AsteroidTemplate.h"
#include <stdexcept>
#include <string>
#include <GLES/gl.h>
#include <Utils.h>

namespace {

float CrossProduct(float x0, float y0, float x1, float y1, float x2, float y2) {
    float ux = x1 - x0;
    float uy = y1 - y0;

    float tx = x2 - x0;
    float ty = y2 - y0;

    return ux * ty - tx * uy;
}

}

namespace zeptoroids {

AsteroidTemplate::AsteroidTemplate(const std::vector<float> &vertices)
        : vertices(vertices) {
}

bool AsteroidTemplate::IsInside(float x, float y) const {
    if (indices.size() <= 2) {
        return false;
    }

    GLushort i0 = indices[0];
    float x0 = vertices[i0 * 2 + 0];
    float y0 = vertices[i0 * 2 + 1];

    GLushort i1 = indices[1];
    float x1 = vertices[i1 * 2 + 0];
    float y1 = vertices[i1 * 2 + 1];

    for (int i = 2; i <= indices.size(); i++) {
        GLushort i2 = indices[i % indices.size()];
        float x2 = vertices[i2 * 2 + 0];
        float y2 = vertices[i2 * 2 + 1];

        bool b1 = CrossProduct(x0, y0, x1, y1, x, y) < 0.0f;
        bool b2 = CrossProduct(x1, y1, x2, y2, x, y) < 0.0f;
        bool b3 = CrossProduct(x2, y2, x0, y0, x, y) < 0.0f;

        if ((b1 == b2) && (b2 == b3)) {
            return true;
        }
        i1 = i2;
        x1 = x2;
        y1 = y2;
    }
    return false;
}

void AsteroidTemplate::Draw(float x, float y, float scale) const {
    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef(scale, scale, 1);
    glDrawElements(GL_LINE_LOOP, renderIndices.size(), GL_UNSIGNED_SHORT, &renderIndices[0]);
    glPopMatrix();
}

const BBox &AsteroidTemplate::GetBBox() const {
    return bbox;
}

} /* namespace zeptoroids */
