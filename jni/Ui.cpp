/*
 * Ui.cpp
 *
 *  Created on: 11.08.2013
 *      Author: NullPointer
 */

#include "Ui.h"

#include <math.h>

#include "Utils.h"

namespace zeptoroids {

Ui::Ui() : sWidth(480), sHeight(320), leftPointer(-1), rightPointer(-1),
        shootPointer(-1), accelPointer(-1) {
    std::vector<GLfloat> circle;
    circle.push_back(0);
    circle.push_back(0);
    indices.push_back(0);
    for (int i = 0; i <= 64; i++) {
        float angle = i / 64.0f * 2 * M_PI;
        circle.push_back(cos(angle));
        circle.push_back(sin(angle));

        indices.push_back(i + 1);
    }

    vb.Bind(GL_ARRAY_BUFFER);
    glBufferData(GL_ARRAY_BUFFER, circle.size() * sizeof(GLfloat), &circle[0],
            GL_STATIC_DRAW);
    VertexBuffer::Unbind(GL_ARRAY_BUFFER);
}

Ui::~Ui() {
}

void Ui::Draw() {
    vb.Bind(GL_ARRAY_BUFFER);
    glVertexPointer(2, GL_FLOAT, 0, 0);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrthof(0, sWidth, 0, sHeight, -1, 1);
    glMatrixMode(GL_MODELVIEW);

    // turn left area
    glPushMatrix();
    glTranslatef(50, 50, 0);
    glScalef(50, 50, 1);

    glColor4f(1, leftPointer >= 0 ? 0 : 1, 1, 1);

    glDrawElements(GL_TRIANGLE_FAN, indices.size(), GL_UNSIGNED_SHORT,
            &indices[0]);

    glPopMatrix();

    // turn right area
    glPushMatrix();
    glTranslatef(150, 50, 0);
    glScalef(50, 50, 1);

    glColor4f(1, rightPointer >= 0 ? 0 : 1, 1, 1);

    glDrawElements(GL_TRIANGLE_FAN, indices.size(), GL_UNSIGNED_SHORT,
            &indices[0]);

    glPopMatrix();

    // shoot area
    glPushMatrix();
    glTranslatef(sWidth - 50, 50, 0);
    glScalef(50, 50, 1);

    glColor4f(1, shootPointer >= 0 ? 0 : 1, 1, 1);

    glDrawElements(GL_TRIANGLE_FAN, indices.size(), GL_UNSIGNED_SHORT,
            &indices[0]);

    glPopMatrix();

    // accelerate area
    glPushMatrix();
    glTranslatef(sWidth - 50, 150, 0);
    glScalef(50, 50, 1);

    glColor4f(1, accelPointer >= 0 ? 0 : 1, 1, 1);

    glDrawElements(GL_TRIANGLE_FAN, indices.size(), GL_UNSIGNED_SHORT,
            &indices[0]);

    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
}

UiEvent Ui::HandlePointerDown(int pointerId, float sX, float sY) {
    float dx = sX - 50;
    float dy = sY - 50;
    if (dx * dx + dy * dy < 50 * 50) {
        leftPointer = pointerId;
        return TURN_LEFT;
    }

    dx = sX - 150;
    dy = sY - 50;
    if (dx * dx + dy * dy < 50 * 50) {
        rightPointer = pointerId;
        return TURN_RIGHT;
    }

    dx = sX - (sWidth - 50);
    dy = sY - 50;
    if (dx * dx + dy * dy < 50 * 50) {
        shootPointer = pointerId;
        return SHOOT;
    }

    dx = sX - (sWidth - 50);
    dy = sY - 150;
    if (dx * dx + dy * dy < 50 * 50) {
        accelPointer = pointerId;
        return FORWARD;
    }

    return NONE;
}

UiEvent Ui::HandlePointerUp(int pointerId) {
    if (pointerId == leftPointer) {
        leftPointer = -1;
        return TURN_LEFT_DONE;
    }

    if (pointerId == rightPointer) {
        rightPointer = -1;
        return TURN_RIGHT_DONE;
    }

    if (pointerId == shootPointer) {
        shootPointer = -1;
        return SHOOT_DONE;
    }

    if (pointerId == accelPointer) {
        accelPointer = -1;
        return FORWARD_DONE;
    }

    return NONE;
}

void Ui::Resize(int w, int h) {
    sWidth = w;
    sHeight = h;
}

void Ui::HandlePointerDone() {
    shootPointer = -1;
    leftPointer = -1;
    rightPointer = -1;
    accelPointer = -1;
}

} /* namespace zeptoroids */
