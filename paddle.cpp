#include "paddle.h"
#include "ofMain.h"
#include "ball.h"
Paddle ::Paddle() {
}
Paddle::Paddle(float x, float y, float w, float h, float v, ofColor color) {
	this->w = w;
	this->h = h;
	this->x = x;
	this->y = y;
	this->v = v;
	this->color = color;
}
void Paddle::drawPaddle(ofImage paddleIcon) {
	ofSetColor(225);
	paddleIcon.draw(x, y, w, h);
}

//AI controls itself when the ball is lower than middle of the comp paddle
void Paddle::updatePlayerPaddle() {
	y += v;
	if ((y + h) >= ofGetHeight()) {
		v *= -0.6;
		y = ofGetHeight() - h;
	}
	else if (y <= (0 + 150)) {
		v *= -0.6;
		y =  (0 + 150);
	}
}
void Paddle::movePaddleDown() {
	v += 0.5;
}
void Paddle::movePaddleUp() {
	v -= 0.5;
}
