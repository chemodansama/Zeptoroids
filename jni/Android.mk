LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := Zeptoroids
LOCAL_SRC_FILES := zeptoroids.cpp \
	Utils.cpp \
	BBox.cpp \
	VertexBuffer.cpp \
	AsteroidTemplate.cpp \
	Asteroid.cpp \
	Ui.cpp \
	Spaceship.cpp \
	Explosions.cpp \
	Bullets.cpp \
	Game.cpp 
	
LOCAL_CPPFLAGS := -std=c++0x
	
LOCAL_LDLIBS := -lGLESv1_CM -llog

include $(BUILD_SHARED_LIBRARY)
