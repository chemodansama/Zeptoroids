/*
 * Bullets.cpp
 *
 *  Created on: 12.08.2013
 *      Author: NullPointer
 */

#include "Bullets.h"

#include <math.h>
#include <algorithm>

#include "Utils.h"

namespace {

constexpr float V = 10;
constexpr long LIFETIME = 2000;

}

namespace zeptoroids {

Bullets::Bullets() {
}

void Bullets::Add(float x, float y, float angle, int stepsPerSecond) {
    bullets.emplace_back(new Bullet(x, y, angle, stepsPerSecond));
}

Bullet::Bullet(float x, float y, float angle, int stepsPerSecond)
        : x(x), y(y), birthTime(Utils::GetTime()) {
    double c = cos(angle * M_PI / 180);
    double s = sin(angle * M_PI / 180);

    vx = V / stepsPerSecond * c;
    vy = V / stepsPerSecond * s;
}

bool Bullet::IsAlive(long currentTime) const {
    return currentTime < birthTime + LIFETIME;
}

void Bullets::Remove(Bullet *b) {
    removed.push_back(b);
}

void Bullets::Update(float w, float h) {
    long time = Utils::GetTime();

    while (!bullets.empty() && !bullets.front()->IsAlive(time)) {
        bullets.pop_front();
    }

    vertices.clear();
    for (auto it = bullets.begin(); it != bullets.end();) {
        auto &b = *it;
        if (std::find(removed.begin(), removed.end(), b.get()) != removed.end()) {
            it = bullets.erase(it);
        } else {
            b->Update(w, h);
            vertices.push_back(b->GetX());
            vertices.push_back(b->GetY());
            ++it;
        }
    }
    removed.clear();
}

void Bullets::Draw() const {
    glPointSize(3);
    glVertexPointer(2, GL_FLOAT, 0, &vertices[0]);
    glDrawArrays(GL_POINTS, 0, vertices.size() / 2);
    glPointSize(1);
}

void Bullet::Update(float w, float h) {
    x += vx;
    y += vy;

    x = Utils::CycleCoords(x, w);
    y = Utils::CycleCoords(y, h);
}

} /* namespace zeptoroids */

