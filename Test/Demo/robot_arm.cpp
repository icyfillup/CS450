/*
Benjamin Isani Evans
302396593 :)

*/
#include "robot_arm.h"
#include <windows.h>  //suitable when using Windows 95/98/NT
#include <gl/Gl.h>
#include <gl/Glu.h>
#include <gl/glut.h>

RobotArm::RobotArm(){
	init();
}

void RobotArm::draw(){
	if (!active){
		jointColor.r = 1;
		jointColor.g = 0;
		jointColor.b = 0;
	}
	else{
		jointColor.r = 1;
		jointColor.g = 0;
		jointColor.b = 1;
	}
	glTranslated(pos.x,pos.y, pos.z);
	drawUpperArm();
	drawLowerArm();
}

void RobotArm::drawUpperArm()const{
	if (!wireFrame){

	
	//base
	glPushMatrix();
	glScaled(base.width, base.height, base.depth);
	glColor3f(armColor.r, armColor.g, armColor.b);
	glutSolidCube(1);
	glPopMatrix();

	//shoulder rotation 
	glRotated(shoulder.rot.y, 0, 1, 0);

	//draw shoulder joint 
	glTranslated(shoulder.pos.x, shoulder.pos.y, shoulder.pos.z);
	glPushMatrix();
	glColor3f(jointColor.r, jointColor.g, jointColor.b);
	glutSolidSphere(shoulder.size, 20, 8);
	glPopMatrix();

	//upper arm raise
	glRotated(shoulder.rot.z, 0, 0, 1);

	//draw upper arm 
	glTranslated(upperArm.pos.x, upperArm.pos.y, upperArm.pos.z);
	glPushMatrix();
	glScaled(upperArm.width, upperArm.height, upperArm.depth);
	glColor3f(armColor.r, armColor.g, armColor.b);
	glutSolidCube(1);
	glPopMatrix();

	//draw elbow
	glTranslated(elbow.pos.x, elbow.pos.y, elbow.pos.z);
	glPushMatrix();
	glColor3f(jointColor.r, jointColor.g, jointColor.b);
	glutSolidSphere(elbow.size, 20, 8);
	glPopMatrix();

	}
	else{

		//base
		glPushMatrix();
		glScaled(base.width, base.height, base.depth);
		glColor3f(armColor.r, armColor.g, armColor.b);
		glutWireCube(1);
		glPopMatrix();

		//shoulder rotation 
		glRotated(shoulder.rot.y, 0, 1, 0);

		//draw shoulder joint 
		glTranslated(shoulder.pos.x, shoulder.pos.y, shoulder.pos.z);
		glPushMatrix();
		glColor3f(jointColor.r, jointColor.g, jointColor.b);
		glutWireSphere(shoulder.size, 20, 8);
		glPopMatrix();

		//upper arm raise
		glRotated(shoulder.rot.z, 0, 0, 1);

		//draw upper arm 
		glTranslated(upperArm.pos.x, upperArm.pos.y, upperArm.pos.z);
		glPushMatrix();
		glScaled(upperArm.width, upperArm.height, upperArm.depth);
		glColor3f(armColor.r, armColor.g, armColor.b);
		glutWireCube(1);
		glPopMatrix();

		//draw elbow
		glTranslated(elbow.pos.x, elbow.pos.y, elbow.pos.z);
		glPushMatrix();
		glColor3f(jointColor.r, jointColor.g, jointColor.b);
		glutWireSphere(elbow.size, 20, 8);
		glPopMatrix();
	}
}

void RobotArm::drawLowerArm()const{

	if (!wireFrame){
		glPushMatrix();
		//raise lower arm 
		glRotated(elbow.rot.z, 0, 0, 1);

		//draw lower arm 
		glTranslated(lowerArm.pos.x, lowerArm.pos.y, lowerArm.pos.z);
		glPushMatrix();
		glScaled(lowerArm.width, lowerArm.height, lowerArm.depth);
		glColor3f(armColor.r, armColor.g, armColor.b);
		glutSolidCube(1);
		glPopMatrix();

		//draw wrsit
		glTranslated(wrist.pos.x, wrist.pos.y, wrist.pos.z);
		glPushMatrix();
		glColor3f(jointColor.r, jointColor.g, jointColor.b);
		glutSolidSphere(wrist.size, 20, 8);
		glPopMatrix();

		//raise hand
		glRotated(wrist.rot.z, 0, 0, 1);

		//draw hand 
		glTranslated(hand.pos.x, hand.pos.y, hand.pos.z);
		glPushMatrix();
		glScaled(hand.width, hand.height, hand.depth);
		glColor3f(armColor.r, armColor.g, armColor.b);
		glutSolidCube(1);
		glPopMatrix();

		glPushMatrix();
		//draw knuckle joints
		for (int i = 0; i < fingerCount; i++)
		{
			Joint k = knuckles[i];
			Finger f = fingers[i];
			glPushMatrix();
			glTranslated(0, k.pos.y, k.pos.z);
			glPushMatrix();
			glTranslated(0, 0, f.pos.z);
			glRotated(k.rot.z, 0, 0, 1);
			glTranslated(f.pos.x, f.pos.y, 0);
			glScaled(f.width, f.height, f.depth);
			glColor3f(armColor.r, armColor.g, armColor.b);
			glutSolidCube(1);
			glPopMatrix();
			glColor3f(jointColor.r, jointColor.g, jointColor.b);
			glutSolidSphere(k.size, 20, 8);
			glPopMatrix();
		}
		//draw thumb 
		glPushMatrix();
		glTranslated(thumbKnuckle.pos.x, thumbKnuckle.pos.y, thumbKnuckle.pos.z);
		glPushMatrix();
		glTranslated(thumb.pos.x, thumb.pos.y, 0);
		glRotated(thumbKnuckle.rot.y, 0, 1, 0);
		glTranslated(0, 0, thumb.pos.z);
		glScaled(thumb.width, thumb.height, thumb.depth);
		glColor3f(armColor.r, armColor.g, armColor.b);
		glutSolidCube(1);
		glPopMatrix();
		glColor3f(jointColor.r, jointColor.g, jointColor.b);
		glutSolidSphere(thumbKnuckle.size, 20, 8);
		glPopMatrix();

		glPopMatrix();

		glPopMatrix();
	}
	else{
		glPushMatrix();
		//raise lower arm 
		glRotated(elbow.rot.z, 0, 0, 1);

		//draw lower arm 
		glTranslated(lowerArm.pos.x, lowerArm.pos.y, lowerArm.pos.z);
		glPushMatrix();
		glScaled(lowerArm.width, lowerArm.height, lowerArm.depth);
		glColor3f(armColor.r, armColor.g, armColor.b);
		glutWireCube(1);
		glPopMatrix();

		//draw wrsit
		glTranslated(wrist.pos.x, wrist.pos.y, wrist.pos.z);
		glPushMatrix();
		glColor3f(jointColor.r, jointColor.g, jointColor.b);
		glutWireSphere(wrist.size, 20, 8);
		glPopMatrix();

		//raise hand
		glRotated(wrist.rot.z, 0, 0, 1);

		//draw hand 
		glTranslated(hand.pos.x, hand.pos.y, hand.pos.z);
		glPushMatrix();
		glScaled(hand.width, hand.height, hand.depth);
		glColor3f(armColor.r, armColor.g, armColor.b);
		glutWireCube(1);
		glPopMatrix();

		glPushMatrix();
		//draw knuckle joints
		for (int i = 0; i < fingerCount; i++)
		{
			Joint k = knuckles[i];
			Finger f = fingers[i];
			glPushMatrix();
			glTranslated(0, k.pos.y, k.pos.z);
			glPushMatrix();
			glTranslated(0, 0, f.pos.z);
			glRotated(k.rot.z, 0, 0, 1);
			glTranslated(f.pos.x, f.pos.y, 0);
			glScaled(f.width, f.height, f.depth);
			glColor3f(armColor.r, armColor.g, armColor.b);
			glutWireCube(1);
			glPopMatrix();
			glColor3f(jointColor.r, jointColor.g, jointColor.b);
			glutWireSphere(k.size, 20, 8);
			glPopMatrix();
		}
		//draw thumb 
		glPushMatrix();
		glTranslated(thumbKnuckle.pos.x, thumbKnuckle.pos.y, thumbKnuckle.pos.z);
		glPushMatrix();
		glTranslated(thumb.pos.x, thumb.pos.y, 0);
		glRotated(thumbKnuckle.rot.y, 0, 1, 0);
		glTranslated(0, 0, thumb.pos.z);
		glScaled(thumb.width, thumb.height, thumb.depth);
		glColor3f(armColor.r, armColor.g, armColor.b);
		glutWireCube(1);
		glPopMatrix();
		glColor3f(jointColor.r, jointColor.g, jointColor.b);
		glutWireSphere(thumbKnuckle.size, 20, 8);
		glPopMatrix();

		glPopMatrix();

		glPopMatrix();
	}
}


void RobotArm::init(){

	base = { 1, .1, 1, {0,0,0,} };
	shoulder = { .145, { 0, .1, 0 }, { 0, 0, 0 } };
	float armHeight = 1;
	upperArm = { .2, armHeight, .1, {0,armHeight/2,0} };
	elbow = { .145, {0,armHeight/2,0}, { 0, 0, 0 } };
	lowerArm = { armHeight,.2,.1 ,{armHeight/2, 0,0} };
	wrist = {.145, {armHeight/2,0,0}, {0,0,0} };
	hand = { .1, .5, .7, {.145,0,0} };
	float knuckleSize = .1;
	float knuckleSpacing = .2;
	knuckles[0] = { knuckleSize, { 0, (hand.height / 2), (hand.depth / 2) - (knuckleSize / 2)}, { 0, 0, 0 } };
	knuckles[1] = { knuckleSize, { 0, (hand.height / 2), -(hand.depth / 2) + (knuckleSize / 2) }, { 0, 0, 0 } };
	knuckles[2] = { knuckleSize, { 0, (hand.height / 2), (hand.depth / 2) - (knuckleSize / 2)- knuckleSpacing }, { 0, 0, 0 } };
	knuckles[3] = { knuckleSize, { 0, (hand.height / 2), -(hand.depth / 2) + (knuckleSize / 2) + knuckleSpacing}, { 0, 0, 0 } };
	thumbKnuckle = { knuckleSize, { 0, -(hand.height / 2)+(knuckleSize/2), -(hand.depth / 2) + (knuckleSize / 2) }, { 0, 0, 0 } };
	float fingerWidth = .1;
	float fingerHeight = .5;
	float fingerDepth = .1;
	float thumbDepth = .35;

	fingers[0] = { fingerWidth, fingerHeight, fingerDepth, { 0, fingerHeight/2, 0 } };
	fingers[1] = { fingerWidth, fingerHeight, fingerDepth, { 0, fingerHeight/2, 0 } };
	fingers[2] = { fingerWidth, fingerHeight, fingerDepth, { 0, fingerHeight/2, 0 } };
	fingers[3] = { fingerWidth, fingerHeight, fingerDepth, { 0, fingerHeight/2, 0 } };
	fingers[4] = { fingerWidth, fingerHeight, fingerDepth, { 0, fingerHeight/2, 0 } };
	thumb = { fingerWidth,fingerDepth,thumbDepth,{0,0, -(thumbDepth/2)} };
	armColor = { .50f, .50f, 0.5f };
	pos = { 0, 0, 0 };
	active = true;
	wireFrame = false;
	isAnimating = false;
	t = 0;
}

void RobotArm::animate(){

	if (isAnimating || !active)return;
	isAnimating= true;
	active = false;
	t = 0;
	TweenFrame frame1 = TweenFrame(shoulder, elbow, wrist, thumbKnuckle.rot.y);
	TweenFrame frame2 = TweenFrame(ANIMATION_STEP_RATE*10);
	TweenFrame frame3 = TweenFrame(ANIMATION_STEP_RATE * 5);
	TweenFrame frame4 = TweenFrame(ANIMATION_STEP_RATE * 5);

	frame1.setTargetShoulderRotationAngle(0);
	frame1.setTargetLowerArmRaiseRotationAngle(-45);
	frame1.setTargetUpperArmRaiseRotationAngle(45);
	frame1.setTargetWristRotationAngle(-45);
	frame1.setTargetFingerCurlAngle(-90);

	frame2.setTargetShoulderRotationAngle(0);
	frame2.setTargetLowerArmRaiseRotationAngle(45);
	frame2.setTargetUpperArmRaiseRotationAngle(-45);
	frame2.setTargetWristRotationAngle(-90);
	frame2.setTargetFingerCurlAngle(-145);

	frame3.setTargetShoulderRotationAngle(0);
	frame3.setTargetLowerArmRaiseRotationAngle(10);
	frame3.setTargetUpperArmRaiseRotationAngle(-10);
	frame3.setTargetWristRotationAngle(-35);
	frame3.setTargetFingerCurlAngle(-100);

	frame4.setTargetShoulderRotationAngle(0);
	frame4.setTargetLowerArmRaiseRotationAngle(0);
	frame4.setTargetUpperArmRaiseRotationAngle(0);
	frame4.setTargetWristRotationAngle(-10);
	frame4.setTargetFingerCurlAngle(-45);

	tweenFrames.push_back(frame1);
	tweenFrames.push_back(frame2);
	tweenFrames.push_back(frame3);
	tweenFrames.push_back(frame4);/**/
}

void RobotArm::updateAnimation(){
	if (!isAnimating)return;
	//t += ANIMATION_STEP_RATE;
	t += tweenFrames[0].step;
    if (t >= 1){
		tweenFrames.erase(tweenFrames.begin());
		//tweenFrames.pop_back();
		t = 0;

		if (tweenFrames.size() == 0)
		{
			std::cout << "hello";
			isAnimating = false;
			active = true;
			t = 0;
			return;
		}
		else{//prepare the next frame using the current positon for tweening

			tweenFrames[0].prepareFrame(shoulder, elbow, wrist, thumbKnuckle.rot.y);

		}
	
	}
	//shoulder rotation 
	shoulder.rot.y = tweenFrames[0].getShoulderRotation(t);
	//lower arm lift 
	elbow.rot.z = tweenFrames[0].getLowerArmRotation(t);
	//upper arm lif 
	shoulder.rot.z = tweenFrames[0].getUpperArmRotation(t);
	//hand raise 
	wrist.rot.z = tweenFrames[0].getWristRotation(t);
	//finger open/close 
	float angle = tweenFrames[0].getFingerCurl(t);
	for (int i = 0; i < fingerCount; i++){
		knuckles[i].rot.z = angle;
	}
	thumbKnuckle.rot.y = angle;




}

void RobotArm::reset(){
	init();
}
