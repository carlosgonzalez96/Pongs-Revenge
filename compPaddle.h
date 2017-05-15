#pragma once
#include "ofMain.h"
class CompPaddle {
public:
	int w;
	int h;
	int x;
	int y;
	int v;
	ofColor color;
	CompPaddle();
	CompPaddle(int x, int y, int w, int h, int v, ofColor color);
	void drawCompPaddle(ofImage compPaddleIcon);
	void followBall(float by);
	void deley(float py);
};