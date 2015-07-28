#ifndef SETTING_H
#define SETTING_H

#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 500

#define WORLD_WIDTH 100
#define WORLD_HEIGHT 100

#define PI 3.141592f

#define RADIUS 2.5f

#define DEBUG 0
#define debugPrint(word) (std::cout << (word) << std::endl)

#include <math.h>   // included for random number generation
#include <ctime>
#include <iostream>

// world corners: left, right, bottom, top

struct GLfloatPoint2D
{
    float x, y;
};

struct GLfloatColor3f
{
    float r, g, b;
};

#endif
