#include <jni.h>
#include <GLES/gl.h>
#include <android/log.h>
#include "Game.h"
#include "Utils.h"

static zeptoroids::Game *game = 0;

#ifdef __cplusplus
extern "C" {
#endif

// =====================  ZrRenderer ===========================================

void init() {
    game = new zeptoroids::Game();
}

JNIEXPORT void JNICALL Java_org_zeptotest_zeptoroids_ZrRenderer_nativeInit
  (JNIEnv *, jclass)
{
    init();
}

JNIEXPORT void JNICALL Java_org_zeptotest_zeptoroids_ZrRenderer_nativeResize
  (JNIEnv *, jclass, jint w, jint h)
{
    game->Resize(w, h);
}

JNIEXPORT void JNICALL Java_org_zeptotest_zeptoroids_ZrRenderer_nativeRender
  (JNIEnv *, jclass)
{
    game->Render();
}

JNIEXPORT void JNICALL Java_org_zeptotest_zeptoroids_ZrRenderer_nativeDone
  (JNIEnv *, jclass)
{
    delete game;
    game = 0;
}

// =====================  ZrSurfaceView ========================================

JNIEXPORT void JNICALL Java_org_zeptotest_zeptoroids_ZrSurfaceView_nativePause
  (JNIEnv *, jclass)
{
}

JNIEXPORT void JNICALL Java_org_zeptotest_zeptoroids_ZrSurfaceView_nativeResume
  (JNIEnv *, jclass)
{
}

JNIEXPORT void JNICALL Java_org_zeptotest_zeptoroids_ZrSurfaceView_nativeTogglePauseResume
  (JNIEnv *, jclass)
{
}

// =====================  MainActivity =========================================

JNIEXPORT void JNICALL Java_org_zeptotest_zeptoroids_MainActivity_nativePointerDown
  (JNIEnv * env, jclass cls, jint pointerId, jfloat x, jfloat y)
{
    LOGI("pointerDown %d %f %f", pointerId, x, y);
    if (game) {
        game->HandlePointerDown(pointerId, x, y);
    }
}

JNIEXPORT void JNICALL Java_org_zeptotest_zeptoroids_MainActivity_nativePointerUp
  (JNIEnv * env, jclass cls, jint pointerId)
{
    LOGI("pointerUp %d", pointerId);
    if (game) {
        game->HandlePointerUp(pointerId);
    }
}

JNIEXPORT void JNICALL Java_org_zeptotest_zeptoroids_MainActivity_nativePointerDone
  (JNIEnv *, jclass)
{
    LOGI("pointerDone");
    if (game) {
        game->HandlePointerDone();
    }
}

#ifdef __cplusplus
}
#endif
