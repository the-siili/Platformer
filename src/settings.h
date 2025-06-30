#pragma once
#include <raylib.h>

#define MAX_ENTITIES 10000000



static const unsigned int WINDOW_FLAGS = FLAG_FULLSCREEN_MODE;



static const int SCREEN_HEIGHT = 600;
static const int SCREEN_WIDTH = 800;

//0 = unlimited, >0 = target
static const unsigned int TARGET_FPS = 0;

//how long between running FixedUpdate
static const float PHYSICS_TIME_STEP = 1.0/60.0;

