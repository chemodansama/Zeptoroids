/*
 * Ui.h
 *
 *  Created on: 11.08.2013
 *      Author: NullPointer
 */

#ifndef UI_H_
#define UI_H_

#include <vector>
#include "VertexBuffer.h"
#include <GLES/gl.h>

namespace zeptoroids {

enum UiEvent {
    NONE,
    TURN_LEFT, TURN_LEFT_DONE,
    TURN_RIGHT, TURN_RIGHT_DONE,
    SHOOT, SHOOT_DONE,
    FORWARD, FORWARD_DONE
};

class Ui {
public:
    Ui();
    ~Ui();

    void Draw();
    void Resize(int w, int h);

    UiEvent HandlePointerDown(int pointerId, float sX, float sY);
    UiEvent HandlePointerUp(int pointerId);
    void HandlePointerDone();

    bool IsLeft() { return leftPointer >= 0; }
    bool IsRight() { return rightPointer >= 0; }
    bool IsShooting() { return shootPointer >= 0; }
    bool IsAccel() { return accelPointer >= 0; }
private:
    int leftPointer;
    int rightPointer;
    int shootPointer;
    int accelPointer;

    int sWidth;
    int sHeight;

    VertexBuffer vb;
    std::vector<GLushort> indices;
};

} /* namespace zeptoroids */
#endif /* UI_H_ */
