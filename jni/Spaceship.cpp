/*
 * Spaceship.cpp
 *
 *  Created on: 11.08.2013
 *      Author: NullPointer
 */

#include "Spaceship.h"

#include <GLES/gl.h>
#include <math.h>

#include "Utils.h"

namespace {
    // invulnerability time in msec since spawn time.
    const static long INVULTIME = 2000;
}

namespace zeptoroids {

Spaceship::Spaceship(const std::vector<GLfloat> &vertices,
        const std::vector<GLushort> &indices,
        const std::vector<GLushort> &flame,
        float scale)
        : vertices(vertices)
        , indices(indices)
        , flame(flame)
        , x(0)
        , y(0)
        , scale(scale)
        , turnLeft(false)
        , turnRight(false)
        , forward(false)
        , angle(0)
        , velocity(0)
        , bbox(BBox::ComputeBBox(vertices, indices))
        , birthTime(Utils::GetTime()) {
}

void Spaceship::Draw(float w, float h) {
    long time = Utils::GetTime();
    if (birthTime + INVULTIME > time && time / 250 % 2 == 0) {
        return;
    }

    DrawAt(x, y);

    if (bbox.Right() * scale + x > w) {
        DrawAt(x - 2 * w, y);
    } else if (bbox.Left() * scale + x < -w) {
        DrawAt(x + 2 * w, y);
    }

    if (bbox.Top() * scale + y > h) {
        DrawAt(x, y - 2 * h);
    } else if (bbox.Bottom() * scale + y < -h) {
        DrawAt(x, y + 2 * h);
    }
}

void Spaceship::TurnLeft() {
    turnLeft = true;
}

void Spaceship::TurnRight() {
    turnRight = true;
}

void Spaceship::TurnStopLeft() {
    turnLeft = false;
}

bool Spaceship::HasCollision(const Asteroid *asteroid) {
    for (int i = 0; i < indices.size(); i++) {
        int index = indices[i];
        float x = vertices[index * 2 + 0];
        float y = vertices[index * 2 + 1];
        if (asteroid->IsInside(this->x + x * scale, this->y + y * scale)) {
            return true;
        }
    }
    return false;
}

void Spaceship::Update(int stepsPerSec, float w, float h) {
    if (turnLeft) {
        angle += 4;
    }

    if (turnRight) {
        angle -= 4;
    }

    if (forward) {
        velocity = 6.0f / stepsPerSec;
    }

    if (velocity > 0) {
        float s = static_cast<float>(sin(angle * M_PI / 180));
        float c = static_cast<float>(cos(angle * M_PI / 180));
        x += velocity * c;
        y += velocity * s;
        velocity *= 0.96f;
        if (velocity < 0.001f) {
            velocity = 0;
        }

        x = Utils::CycleCoords(x, w);
        y = Utils::CycleCoords(y, h);
    }
}

bool Spaceship::HasInvulnerability() {
    return birthTime + INVULTIME > Utils::GetTime();
}

void Spaceship::TurnStopRight() {
    turnRight = false;
}

void Spaceship::Forward() {
    forward = true;
}

void Spaceship::Stop() {
    forward = false;
}

void Spaceship::DrawAt(float x, float y) {
    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef(scale, scale, 1);
    glRotatef(angle - 90, 0, 0, 1);
    glDrawElements(GL_LINES, indices.size(), GL_UNSIGNED_SHORT, &indices[0]);

    if (forward && Utils::GetTime() / 100 % 2 == 0) {
        glDrawElements(GL_LINES, flame.size(), GL_UNSIGNED_SHORT, &flame[0]);
    }

    glPopMatrix();
}

} /* namespace zeptoroids */
