/*
Benjamin Isani Evans
302396593 :)

*/
#ifndef ROBOTARM_H
#define ROBOTARM_H
#define ELBOW_ROT_MAX_Z 75
#define ELBOW_ROT_MIN_Z -75
#define SHOULDER_ROT_MAX_Z 75
#define SHOULDER_ROT_MIN_Z -75
#define WRIST_ROT_MAX_Z 45
#define WRIST_ROT_MIN_Z -45
#define HAND_OPEN_SPEED 1
#define HAND_CLOSE_MIN -135
#define ANIMATION_STEP_RATE .001
#include <vector>
#include <iostream>

struct Position{
	float x, y, z;
};
struct Rotation{
	float x, y, z;
};
struct Joint{
	float size;
	Position pos;
	Rotation rot;
};

struct Limb{
	float width;// x
	float height;// y
	float depth;//z
	Position pos;
};

struct Color{
	float r, g, b;
};
struct Base{
	float width, height, depth;
	Position pos;
};
struct Finger{
	float width, height, depth;
	Position pos;
};

class TweenFrame{

public:

	TweenFrame(){
		step = ANIMATION_STEP_RATE;
	}
	TweenFrame(float newTween){
		step = newTween;
	}
	TweenFrame(const Joint& shoulder, const Joint& elbow, const Joint& wrist, float hand)
	{
		prepareFrame(shoulder, elbow, wrist, hand);
		step = ANIMATION_STEP_RATE;
	}

	void prepareFrame(const Joint& shoulder, const Joint& elbow, const Joint& wrist, float hand){
		handCurl = hand;
		this->shoulder = shoulder.rot;
		this->elbow = elbow.rot;
		this->wrist = wrist.rot;
	}

	float getShoulderRotation(float t){
		return shoulder.y*(1 - t) + targetShoulderRotation*t;
	}
	//lower arm lift 
	float getLowerArmRotation(float t){
		return elbow.z*(1 - t) + targetLowerArmRaise*t;
	}
	//upper arm lift
	float getUpperArmRotation(float t){
		return shoulder.z*(1 - t) + targetUpperArmRaise*t;
	}
	//hand raise 
	float getWristRotation(float t){
		return wrist.z*(1 - t) + targetWristRotation*t;
	}
	//finger open/close 
	float getFingerCurl(float t){
		return handCurl*(1 - t) + targetFingerCurl*t;
	}

	void setTargetShoulderRotationAngle(float angle){
		targetShoulderRotation = angle;
	}
	void setTargetLowerArmRaiseRotationAngle(float angle){
		targetLowerArmRaise = angle;
	}
	void setTargetUpperArmRaiseRotationAngle(float angle){
		targetUpperArmRaise = angle;
	}
	void setTargetWristRotationAngle(float angle){
		targetWristRotation = angle;
	}
	void setTargetFingerCurlAngle(float angle){
		targetFingerCurl = angle;
	}
	float step;
	private :
		Rotation shoulder, elbow, wrist;
		float handCurl, targetShoulder;
		//target positions
		float targetShoulderRotation, targetFingerCurl, targetWristRotation, targetUpperArmRaise, targetLowerArmRaise;
		
};



class RobotArm {
	public:
		RobotArm();
		void reset();
		void draw();
		void animate();
		void updateAnimation();
		void openHand(){
			for (int i = 0; i < fingerCount; i++){
				knuckles[i].rot.z += HAND_OPEN_SPEED;

				if (knuckles[i].rot.z > 0)knuckles[i].rot.z = 0;
				

			}
			thumbKnuckle.rot.y += HAND_OPEN_SPEED;
			if (thumbKnuckle.rot.y > 0)thumbKnuckle.rot.y = 0;
		}
		void closeHand(){
			for (int i = 0; i < fingerCount; i++){
				knuckles[i].rot.z -= HAND_OPEN_SPEED;
				if (knuckles[i].rot.z < HAND_CLOSE_MIN)knuckles[i].rot.z = HAND_CLOSE_MIN;
			}

			thumbKnuckle.rot.y -= HAND_OPEN_SPEED;
			if (thumbKnuckle.rot.y < HAND_CLOSE_MIN)thumbKnuckle.rot.y = HAND_CLOSE_MIN;
		}
		void liftHand(float angle){
			wrist.rot.z += angle;
			if (wrist.rot.z > WRIST_ROT_MAX_Z) wrist.rot.z = WRIST_ROT_MAX_Z;
			else if (wrist.rot.z < WRIST_ROT_MIN_Z) wrist.rot.z = WRIST_ROT_MIN_Z;
		}
	
		Position getPosition()const {
			Position p = {pos.x, pos.y, pos.z};
			return p;
		}
		void setActive(bool state){
			active = state;
		}
		bool isActivated()const {
			return active;
		}
		void rotateShoulder(float angle){
			shoulder.rot.y += angle;
		}
		void raiseUpperArm(float angle){
			shoulder.rot.z += angle;
			if (shoulder.rot.z > SHOULDER_ROT_MAX_Z) shoulder.rot.z = SHOULDER_ROT_MAX_Z;
			else if (shoulder.rot.z < SHOULDER_ROT_MIN_Z) shoulder.rot.z = SHOULDER_ROT_MIN_Z;
		}
		void raiseLowerArm(float angle){
			elbow.rot.z += angle;
			if (elbow.rot.z > ELBOW_ROT_MAX_Z) elbow.rot.z = ELBOW_ROT_MAX_Z;
			else if (elbow.rot.z < ELBOW_ROT_MIN_Z) elbow.rot.z = ELBOW_ROT_MIN_Z;
		}
		void incrementZ(float dz){
			pos.z += dz;
		}
		bool isWireFrame(){
			return wireFrame;
		}
		void setWireFrame(bool state){
			wireFrame = state;
		}

		
   private:
	   const static int fingerCount = 4;
	   float t;
	   Joint elbow, shoulder, wrist;
	   Limb upperArm, lowerArm;
	   Position pos;
	   Color jointColor;
	   Color armColor;
	   bool active, wireFrame;
	   Base base, hand;
	   Finger fingers[fingerCount];
	   Finger thumb;
	   Joint knuckles[fingerCount];
	   Joint thumbKnuckle;
	   std::vector < TweenFrame > tweenFrames ;
	   bool isAnimating;
	   void drawLowerArm()const;
	   void drawUpperArm()const;
	   void init();
	 
};
#endif
