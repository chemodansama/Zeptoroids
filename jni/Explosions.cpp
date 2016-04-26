/*
 * Explosions.cpp
 *
 *  Created on: 12.08.2013
 *      Author: NullPointer
 */

#include "Explosions.h"

#include <math.h>

#include <algorithm>
#include "Utils.h"

namespace zeptoroids {

void Explosions::Draw() {
    glVertexPointer(2, GL_FLOAT, 0, &vertices[0]);
    glDrawArrays(GL_POINTS, 0, vertices.size() / 2);
}

void Explosions::Update() {
    vertices.clear();
    for (auto it = points.begin(), vit = velocities.begin();
            it != points.end(); ++it, ++vit) {
        (*it) += *vit;
        vertices.push_back(*it);
    }

    long time = Utils::GetTime();
    while (!births.empty() && births.front() + 10000 < time) {
        births.pop_front();
        for (int i = 0; i < N * 2; i++) {
            points.pop_front();
            velocities.pop_front();
        }
    }
}

void Explosions::AddExplosion(float x, float y) {
    for (int i = 0; i < N; i++) {
        float v = Utils::Randf(2, 6) / stepsPerSec;
        float a = Utils::Randf(0, 2 * M_PI);
        velocities.push_back(cos(a) * v);
        velocities.push_back(sin(a) * v);
        points.push_back(x);
        points.push_back(y);
    }
    births.push_back(Utils::GetTime());
}

} /* namespace zeptoroids */
