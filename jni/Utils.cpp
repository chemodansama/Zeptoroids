/*
 * Utils.cpp
 *
 *  Created on: 10.08.2013
 *      Author: NullPointer
 */

#include "Utils.h"
#include <sys/time.h>

namespace zeptoroids {

namespace Utils {

long GetTime(void) {
    struct timeval  now;
    gettimeofday(&now, NULL);
    return (long)(now.tv_sec * 1000 + now.tv_usec / 1000);
}

float CycleCoords(float coord, float bound) {
    if (coord > bound) {
        coord -= 2 * bound;
    } else if (coord < -bound) {
        coord += 2 * bound;
    }
    return coord;
}

}

} /* namespace zeptoroids */
