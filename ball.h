#pragma once
#include "ofMain.h"
class Ball{
public:
	float x;
	float y;
	int r;
	float xV;
	float yV;
	int score;
	int bleft;
	int lives;
	ofColor color;
	Ball();
	Ball(float x, float y, int r, float xV, float yV, int score, int bleft, int lives, ofColor color);
	void drawBall();
	void moveBall();
	void bounceOff(float px, float py, float pw, float ph);
	void bounceOffc(float cx, float cy, float cw, float ch);
	void resetBall();
	void projectileMove();
};