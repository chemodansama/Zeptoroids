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
#include <memory>
#include <utility>
#include "BBox.h"
#include "Utils.h"

namespace zeptoroids {

class AsteroidTemplate {
public:
    template <typename T, typename V>
    static std::unique_ptr<AsteroidTemplate> Create(const std::vector<float> &vertices,
            T&& indices, V&& renderIndices);

    void Draw(float x, float y, float scale) const;
    bool IsInside(float x, float y) const;

    const BBox &GetBBox() const;

private:
    const std::vector<float> &vertices;
    std::vector<GLushort> indices;
    std::vector<GLushort> renderIndices;

    BBox bbox;

    AsteroidTemplate(const std::vector<float> &vertices);
};

template <typename T, typename V>
std::unique_ptr<AsteroidTemplate> AsteroidTemplate::Create(
        const std::vector<float> &vertices,
        T&& indices, V&& renderIndices) {
    std::unique_ptr<AsteroidTemplate> r { new AsteroidTemplate(vertices) };

    r->indices = std::forward<T>(indices);
    r->renderIndices = std::forward<V>(renderIndices);
    r->bbox = BBox::ComputeBBox(r->vertices, r->renderIndices);

    return r;
}

} /* namespace zeptoroids */
#endif /* ASTEROIDTEMPLATE_H_ */
