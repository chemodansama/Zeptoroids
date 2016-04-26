/*
 * Utils.h
 *
 *  Created on: 10.08.2013
 *      Author: NullPointer
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <android/log.h>
#include <stdlib.h>
#include <memory>

#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, "ZrTag", __VA_ARGS__)

template <typename T, size_t N>
static T* begin(T(&arr)[N]) { return &arr[0]; }

template <typename T, size_t N>
static T* end(T(&arr)[N]) { return &arr[0] + N; }

template <typename T, size_t N>
static size_t length(T(&arr)[N]) { return N; }

namespace zeptoroids {

namespace Utils {
    long GetTime(void);
    float CycleCoords(float coord, float bound);
    static float Randf(float min, float max) {
        return (max - min) * rand() / RAND_MAX + min;
    }

    template <typename T, typename ... Args>
    std::unique_ptr<T> make_unique(Args&& ... args) {
        return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
    }
};

} /* namespace zeptoroids */
#endif /* UTILS_H_ */
