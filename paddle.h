#pragma once
#include "ball.h"
#include "ofMain.h"
class Paddle {
public:
	float w;
	float h;
	float x;
	float y;
	float v;
	ofColor color;
	Paddle();
	Paddle(float x, float y, float w, float h, float v, ofColor color);
	void drawPaddle(ofImage paddleIcon);
	void updatePlayerPaddle();
	void movePaddleDown();
	void movePaddleUp();
};