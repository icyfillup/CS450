#if !defined(ARM_H)
#include "myMath.h"

struct Cube
{
    v3f pos;
    v3f dim;
    float size;
};

struct Cylinder
{
    v3f pos;
    float radius;
    float height;
};

struct Sphere
{
    v3f pos;
    v3f rotate;
    float radius;
};

struct Arm
{
    Cube platform;
    
    Sphere shoulder_joint;
    Cylinder upper_arm;
    Sphere elbow_joint;
    Cylinder lower_arm;
    Sphere wrist_joint;

    Cube hand;
    Sphere knuckle_joint[4];
    Cylinder upper_finger[4];
    Sphere middle_knuckle_joint[4];
    Cylinder lower_finger[4];
    Sphere fingerNail[4];

    Sphere thumb_knuckle_joint;
    Cylinder upper_thumb;
    Sphere thumb_middle_knuckle;
    Cylinder lower_thumb;
    Sphere thumbNail;

    float animationPhase[6];

    bool isSolid;
    bool isActive;
    bool isAnimating;
    bool animationComplete;
};

#define ARM_H
#endif
