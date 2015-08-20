#include <gl/Gl.h>
#include <gl/Glu.h>
#include <gl/glut.h>

#include "Arm.h"

inline void initArm(Arm &arm)
{
    for(int i = 0; i < 6; i++)
    {
        arm.animationPhase[i] = 0.0f;
    }
    
    arm.isSolid = true;
    arm.isActive = true;
    arm.isAnimating = false;
    arm.animationComplete = true;
    
    //platform
    arm.platform.pos = v3f{2.5, 0, 2.5};
    arm.platform.dim = v3f{5, 0.115f, 5};
    arm.platform.size = 1;

    //shoulder joint
    arm.shoulder_joint.pos = v3f{0, 2 + arm.platform.size * arm.platform.dim.height, 0};
    arm.shoulder_joint.radius = 0.175f;
    arm.shoulder_joint.rotate = v3f{0.0, 0.0f, 0.0f};

    //upper arm
    arm.upper_arm.pos = v3f{0, 0, 0};
    arm.upper_arm.height = 1.75f;
    arm.upper_arm.radius = arm.shoulder_joint.radius - 0.03f;

    //elbow joint
    arm.elbow_joint.pos = v3f{0, 0, arm.upper_arm.height};
    arm.elbow_joint.radius = arm.shoulder_joint.radius;
    arm.elbow_joint.rotate.x = 0.0f;

    //lower arm
    arm.lower_arm.pos = v3f{0, 0, 0};
    arm.lower_arm.height = 1.5f;
    arm.lower_arm.radius = arm.upper_arm.radius;

    //wrist joint
    arm.wrist_joint.pos = v3f{0, 0, arm.lower_arm.height};
    arm.wrist_joint.radius = arm.lower_arm.radius;
    arm.wrist_joint.rotate = {0.0f, 0.0f, 0.0f};

    //hand
    arm.hand.pos = v3f{0, 0, 0.75/2};
    arm.hand.dim = v3f{0.5, arm.wrist_joint.radius, 0.75};
    arm.hand.size = 1;

    //fingers - knuckles
    for(int i = 0; i < 4; i++)
    {
        arm.knuckle_joint[i].radius = (arm.hand.dim.width / 2) * 0.25;
        arm.knuckle_joint[i].pos = v3f{(arm.hand.dim.width / 2) * (0.75 - (0.50 * i)), 0, (arm.hand.dim.length / 2) * 0.75};
        arm.knuckle_joint[i].rotate = {0.0f, 0.0f, 0.0f};
    }

    //fingers - upper finger
    for(int i = 0; i < 4; i++)
    {
        arm.upper_finger[i].pos = v3f{0, 0, 0};
        arm.upper_finger[i].radius = arm.knuckle_joint[i].radius * 0.8;
        arm.upper_finger[i].height = arm.hand.dim.length / 2;
    }
    
    //fingers - middle knuckles
    for(int i = 0; i < 4; i++)
    {
        arm.middle_knuckle_joint[i].radius = (arm.hand.dim.width / 2) * 0.25;
        arm.middle_knuckle_joint[i].pos = v3f{0, 0, arm.upper_finger[i].height};
        arm.middle_knuckle_joint[i].rotate = {0.0f, 0.0f, 0.0f};
    }

    //fingers - lower finger
    for(int i = 0; i < 4; i++)
    {
        arm.lower_finger[i].pos = v3f{0, 0, 0};
        arm.lower_finger[i].radius = arm.upper_finger[i].radius;
        arm.lower_finger[i].height = arm.hand.dim.length / 2;
    }

    //fingernails
    for(int i = 0; i < 4; i++)
    {
        arm.fingerNail[i].radius = arm.middle_knuckle_joint[i].radius;
        arm.fingerNail[i].pos = v3f{0, 0, arm.lower_finger[i].height};
    }
    
    //thumb - knuckles
    for(int i = 0; i < 4; i++)
    {
        arm.knuckle_joint[i].radius = (arm.hand.dim.width / 2) * 0.25;
        arm.knuckle_joint[i].pos = v3f{(arm.hand.dim.width / 2) * (0.75 - (0.50 * i)), 0, (arm.hand.dim.length / 2) * 0.75};
        arm.knuckle_joint[i].rotate = {0.0f, 0.0f, 0.0f};
    }

    //thumb - knuckles
    arm.thumb_knuckle_joint.radius = (arm.hand.dim.width / 2) * 0.25;
    arm.thumb_knuckle_joint.pos = v3f{(-arm.hand.dim.width / 2) * 0.75, 0, (-arm.hand.dim.length / 2) / 2};
    arm.thumb_knuckle_joint.rotate = {0.0f, 0.0f, 0.0f};
    
    //upper thumb
    arm.upper_thumb.radius = arm.thumb_knuckle_joint.radius * 0.8;
    arm.upper_thumb.height = arm.hand.dim.length / 4;
    arm.upper_thumb.pos = v3f{0, 0, 0};

    //thumb middle knuckles
    arm.thumb_middle_knuckle.radius = arm.thumb_knuckle_joint.radius;
    arm.thumb_middle_knuckle.pos = v3f{0, 0, arm.upper_thumb.height};
    arm.thumb_middle_knuckle.rotate = {0.0f, 0.0f, 0.0f};
    
    //lower thumb
    arm.lower_thumb.radius = arm.upper_thumb.radius;
    arm.lower_thumb.height = arm.hand.dim.length / 4;
    arm.lower_thumb.pos = v3f{0, 0, 0};

    //thumbnails
    arm.thumbNail.radius = arm.thumb_middle_knuckle.radius;
    arm.thumbNail.pos = v3f{0, 0, arm.lower_thumb.height};

}


void drawPlatform(Arm &arm)
{
    glColor3f(0.0f, 1.0f, 0.0f); // earth is green
    glTranslatef(arm.platform.pos.x, arm.platform.pos.y, arm.platform.pos.z);
    
    glPushMatrix();
    glScalef(arm.platform.dim.width, arm.platform.dim.height, arm.platform.dim.length);
    (arm.isSolid) ? glutSolidCube(arm.platform.size) : glutWireCube(arm.platform.size);
    glPopMatrix();
}

void drawShoulderJoint(Arm &arm)
{
    glColor3f(0.0f, 0.0f, 1.0f);
    glTranslatef(arm.shoulder_joint.pos.x, arm.shoulder_joint.pos.y, arm.shoulder_joint.pos.z);
    glRotatef(arm.shoulder_joint.rotate.y, 0, 1, 0);
    glRotatef(arm.shoulder_joint.rotate.x, 1, 0, 0);
    glRotatef(arm.shoulder_joint.rotate.z, 0, 0, 1);
    
    glPushMatrix();
    (arm.isSolid) ? glutSolidSphere(arm.shoulder_joint.radius, 20, 8) : glutWireSphere(arm.shoulder_joint.radius, 20, 8);
    glPopMatrix();    
}

void drawUpperArm(Arm &arm)
{
    glColor3f(1.0f, 0.0f, 0.0f);
    glTranslatef(arm.upper_arm.pos.x, arm.upper_arm.pos.y, arm.upper_arm.pos.z);

    GLUquadricObj *qobj = gluNewQuadric();
    (arm.isSolid) ? gluQuadricDrawStyle(qobj, GLU_FILL) : gluQuadricDrawStyle(qobj, GLU_LINE);
    gluCylinder(qobj, arm.upper_arm.radius, arm.upper_arm.radius, arm.upper_arm.height, 20, 10);
}


void drawElbowJoint(Arm &arm)
{
    glColor3f(1.0f, 1.0f, 0.0f);
    glTranslatef(arm.elbow_joint.pos.x, arm.elbow_joint.pos.y, arm.elbow_joint.pos.z);
    glRotatef(arm.elbow_joint.rotate.x, 1, 0, 0);
    (arm.isSolid) ? glutSolidSphere(arm.elbow_joint.radius, 20, 8) : glutWireSphere(arm.elbow_joint.radius, 20, 8);
}

void drawLowerArm(Arm &arm)
{
    glColor3f(1.0f, 0.0f, 1.0f);
    glTranslatef(arm.lower_arm.pos.x, arm.lower_arm.pos.y, arm.lower_arm.pos.z);

    GLUquadricObj *qobj = gluNewQuadric();
    (arm.isSolid) ? gluQuadricDrawStyle(qobj, GLU_FILL) : gluQuadricDrawStyle(qobj, GLU_LINE);
    gluCylinder(qobj, arm.lower_arm.radius, arm.lower_arm.radius, arm.lower_arm.height, 20, 10);
}

void drawWristJoint(Arm &arm)
{
    glColor3f(0.0f, 1.0f, 1.0f);
    glTranslatef(arm.wrist_joint.pos.x, arm.wrist_joint.pos.y, arm.wrist_joint.pos.z);
    glRotatef(arm.wrist_joint.rotate.x, 1, 0, 0);
    glRotatef(arm.wrist_joint.rotate.z, 0, 0, 1);
    (arm.isSolid) ? glutSolidSphere(arm.wrist_joint.radius, 20, 8) : glutWireSphere(arm.wrist_joint.radius, 20, 8);
}

void drawHand(Arm &arm)
{
    glColor3f(1.0f, 1.0f, 1.0f); // earth is green
    glTranslatef(arm.hand.pos.x, arm.hand.pos.y, arm.hand.pos.z);

    glPushMatrix();
    glScalef(arm.hand.dim.width, arm.hand.dim.height, arm.hand.dim.length);
    (arm.isSolid) ? glutSolidCube(arm.hand.size) : glutWireCube(arm.hand.size);
    glPopMatrix();
}

void drawFingers(Arm &arm)
{
    for(int i = 0; i < 4; i++) 
    {
        glColor3f(0.25f, 0.75f, 0.5f);
        glPushMatrix();

        glTranslatef(arm.knuckle_joint[i].pos.x, arm.knuckle_joint[i].pos.y, arm.knuckle_joint[i].pos.z);
        glRotatef(arm.knuckle_joint[i].rotate.x, 1, 0, 0);
        (arm.isSolid) ? glutSolidSphere(arm.knuckle_joint[i].radius, 20, 8) : glutWireSphere(arm.knuckle_joint[i].radius, 20, 8);

        
        glTranslatef(arm.upper_finger[i].pos.x, arm.upper_finger[i].pos.y, arm.upper_finger[i].pos.z);
        GLUquadricObj *qobj = gluNewQuadric();
        (arm.isSolid) ? gluQuadricDrawStyle(qobj, GLU_FILL) : gluQuadricDrawStyle(qobj, GLU_LINE);
        gluCylinder(qobj, arm.upper_finger[i].radius, arm.upper_finger[i].radius, arm.upper_finger[i].height, 20, 10);        

        
        glTranslatef(arm.middle_knuckle_joint[i].pos.x, arm.middle_knuckle_joint[i].pos.y, arm.middle_knuckle_joint[i].pos.z);
        glRotatef(arm.middle_knuckle_joint[i].rotate.x, 1, 0, 0);
        (arm.isSolid) ? glutSolidSphere(arm.middle_knuckle_joint[i].radius, 20, 8) : glutWireSphere(arm.middle_knuckle_joint[i].radius, 20, 8);

        
        glTranslatef(arm.lower_finger[i].pos.x, arm.lower_finger[i].pos.y, arm.lower_finger[i].pos.z);
        qobj = gluNewQuadric();
        (arm.isSolid) ? gluQuadricDrawStyle(qobj, GLU_FILL) : gluQuadricDrawStyle(qobj, GLU_LINE);
        gluCylinder(qobj, arm.lower_finger[i].radius, arm.lower_finger[i].radius, arm.lower_finger[i].height, 20, 10);        

        
        glTranslatef(arm.fingerNail[i].pos.x, arm.fingerNail[i].pos.y, arm.fingerNail[i].pos.z);
        (arm.isSolid) ? glutSolidSphere(arm.fingerNail[i].radius, 20, 8) : glutWireSphere(arm.fingerNail[i].radius, 20, 8);
        
        glPopMatrix();
    }

    glTranslatef(arm.thumb_knuckle_joint.pos.x, arm.thumb_knuckle_joint.pos.y, arm.thumb_knuckle_joint.pos.z);
    glRotatef(-90, 0, 1, 0);
    glRotatef(arm.thumb_knuckle_joint.rotate.x, 1, 0, 0);
    (arm.isSolid) ? glutSolidSphere(arm.thumb_knuckle_joint.radius, 20, 8) : glutWireSphere(arm.thumb_knuckle_joint.radius, 20, 8);

    
    glTranslatef(arm.upper_thumb.pos.x, arm.upper_thumb.pos.y, arm.upper_thumb.pos.z);
    GLUquadricObj *qobj = gluNewQuadric();
    (arm.isSolid) ? gluQuadricDrawStyle(qobj, GLU_FILL) : gluQuadricDrawStyle(qobj, GLU_LINE);
    gluCylinder(qobj, arm.upper_thumb.radius, arm.upper_thumb.radius, arm.upper_thumb.height, 20, 10);        

    
    glTranslatef(arm.thumb_middle_knuckle.pos.x, arm.thumb_middle_knuckle.pos.y, arm.thumb_middle_knuckle.pos.z);
    glRotatef(arm.thumb_middle_knuckle.rotate.x, 1, 0, 0);
    (arm.isSolid) ? glutSolidSphere(arm.thumb_middle_knuckle.radius, 20, 8) : glutWireSphere(arm.thumb_middle_knuckle.radius, 20, 8);
    
    
    glTranslatef(arm.lower_thumb.pos.x, arm.lower_thumb.pos.y, arm.lower_thumb.pos.z);
    qobj = gluNewQuadric();
    (arm.isSolid) ? gluQuadricDrawStyle(qobj, GLU_FILL) : gluQuadricDrawStyle(qobj, GLU_LINE);
    gluCylinder(qobj, arm.lower_thumb.radius, arm.lower_thumb.radius, arm.lower_thumb.height, 20, 10);        

    
    glTranslatef(arm.thumbNail.pos.x, arm.thumbNail.pos.y, arm.thumbNail.pos.z);
    (arm.isSolid) ? glutSolidSphere(arm.thumbNail.radius, 20, 8) : glutWireSphere(arm.thumbNail.radius, 20, 8);
}


inline void drawArm(Arm &arm)
{
    drawPlatform(arm);
    drawShoulderJoint(arm);
    drawUpperArm(arm);
    drawElbowJoint(arm);
    drawLowerArm(arm);
    drawWristJoint(arm);
    drawHand(arm);
    drawFingers(arm);
}

inline void moveArm(Arm &arm, float length)
{
    if(!arm.isActive)
        {return;}

    float radians = (arm.shoulder_joint.rotate.y * PI) / 180;
    
    arm.shoulder_joint.pos.z += length * cos(radians);
    arm.shoulder_joint.pos.x += length * sin(radians);            
}

inline void rotateShoulder(Arm &arm, float rotate, int rotateAbout)
{
    if(!arm.isActive)
        {return;}

    arm.shoulder_joint.rotate.pos[rotateAbout] += rotate;

    if(arm.shoulder_joint.rotate.pos[0] < -90)
        {arm.shoulder_joint.rotate.pos[0] = -90;}
    else if(arm.shoulder_joint.rotate.pos[0] > 180)
        {arm.shoulder_joint.rotate.pos[0] = 180;}
}

inline void rotateElbow(Arm &arm, float rotate)
{
    if(!arm.isActive)
        {return;}

    arm.elbow_joint.rotate.x += rotate;
    
    if(arm.elbow_joint.rotate.x < -140)
        {arm.elbow_joint.rotate.x = -140;}
    else if(arm.elbow_joint.rotate.x > 0)
        {arm.elbow_joint.rotate.x = 0;}
}
    
inline void rotateKnuckle(Arm &arm, float rotate)
{
    if(!arm.isActive)
        {return;}

    for(int i = 0; i < 4; i++)
    {
        arm.knuckle_joint[i].rotate.x += rotate;
        if(arm.knuckle_joint[i].rotate.x < -90)
                {arm.knuckle_joint[i].rotate.x = -90;}
        else if(arm.knuckle_joint[i].rotate.x > 0)
                {arm.knuckle_joint[i].rotate.x = 0;}
    }

    arm.thumb_knuckle_joint.rotate.x += rotate;
    if(arm.thumb_knuckle_joint.rotate.x < -90)
                {arm.thumb_knuckle_joint.rotate.x = -90;}
    else if(arm.thumb_knuckle_joint.rotate.x > 0)
                {arm.thumb_knuckle_joint.rotate.x = 0;}
            
}

inline void rotateMiddleKnuckle(Arm &arm, float rotate)
{
    if(!arm.isActive)
        {return;}

    for(int i = 0; i < 4; i++)
    {
        arm.middle_knuckle_joint[i].rotate.x += rotate;
        if(arm.middle_knuckle_joint[i].rotate.x < -90)
                {arm.middle_knuckle_joint[i].rotate.x = -90;}
        else if(arm.middle_knuckle_joint[i].rotate.x > 0)
                {arm.middle_knuckle_joint[i].rotate.x = 0;}
    }

    arm.thumb_middle_knuckle.rotate.x += rotate;
    if(arm.thumb_middle_knuckle.rotate.x < -90)
                {arm.thumb_middle_knuckle.rotate.x = -90;}
    else if(arm.thumb_middle_knuckle.rotate.x > 0)
                {arm.thumb_middle_knuckle.rotate.x = 0;}
    
}

inline void toggleOnOff(Arm &arm)
{
    arm.isActive = !arm.isActive;
}

inline void toggleSolidWired(Arm &arm)
{
    arm.isSolid = !arm.isSolid;
}

inline void toggleAnimation(Arm &arm)
{
    arm.isAnimating = !arm.isAnimating;
    arm.animationComplete = false;
}

inline void drawAnimation(Arm &arm)
{
    if(arm.animationPhase[0] < 1)
    {
        arm.animationPhase[0] += 0.01f;
        arm.shoulder_joint.rotate.x = 0 + (180 - 0) * arm.animationPhase[0];
        arm.elbow_joint.rotate.x = 0 + (-140 - 0) * arm.animationPhase[0];
    }
    else if(arm.animationPhase[1] < 1)
    {
        arm.animationPhase[1] += 0.1f;
        arm.shoulder_joint.rotate.x = 180 + (0 - 180) * arm.animationPhase[1];
        arm.elbow_joint.rotate.x = -140 + (0 + 140) * arm.animationPhase[1];
    }
    else if(arm.animationPhase[2] < 1)
    {
        arm.animationPhase[2] += 0.01;
        arm.wrist_joint.rotate.z = 0 + (-90 - 0) * arm.animationPhase[2];
        arm.thumb_middle_knuckle.rotate.x = 0 + (-90 - 0) * arm.animationPhase[2];
        arm.thumb_knuckle_joint.rotate.x = 0 + (-90 - 0) * arm.animationPhase[2];
        arm.elbow_joint.rotate.x = 0 + (-140 - 0) * arm.animationPhase[2];
        arm.shoulder_joint.rotate.z = 0 + (-90 - 0) * arm.animationPhase[2];
        arm.shoulder_joint.rotate.y = 0 + (-180 - 0) * arm.animationPhase[2];
        for(int i = 0; i < 4; i++)
        {
            arm.knuckle_joint[i].rotate.x = 0 + (0 - 90) * arm.animationPhase[2];
            arm.middle_knuckle_joint[i].rotate.x = 0 + (0 - 90) * arm.animationPhase[2];
        }
    }
    else if(arm.animationPhase[3] < 1)
    {
        arm.animationPhase[3] += 0.05f;
        arm.shoulder_joint.rotate.z = -90 + (-180 + 90) * arm.animationPhase[3];
        arm.shoulder_joint.rotate.x = 0 + (240 - 0) * arm.animationPhase[3];
        arm.elbow_joint.rotate.x = -140 + (-45 + 140) * arm.animationPhase[3];
    }
    else if(arm.animationPhase[4] < 1)
    {
        arm.animationPhase[4] += 0.05f;
        arm.wrist_joint.rotate.z = -90 + (0 + 90) * arm.animationPhase[4];
        arm.elbow_joint.rotate.x = -45 + (-90 + 45) * arm.animationPhase[4];
        arm.shoulder_joint.rotate.x = 240 + (180 - 240) * arm.animationPhase[4];        
    }
    else if(arm.animationPhase[5] < 1)
    {
        arm.animationPhase[5] += 0.01;
        arm.shoulder_joint.rotate.z = -180 + (-270 + 180) * arm.animationPhase[5];
        arm.thumb_middle_knuckle.rotate.x = -90 + (0 + 90) * arm.animationPhase[5];
        arm.thumb_knuckle_joint.rotate.x = -90 + (0 + 90) * arm.animationPhase[5];
    }
    else
    {
        arm.isAnimating = false;
        arm.animationComplete = true;
    }
}
