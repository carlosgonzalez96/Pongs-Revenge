#include "ball.h"
#include "ofMain.h"
Ball::Ball() {

}
Ball::Ball(float x, float y, int r, float xV, float yV, int score, int bleft, int lives, ofColor color) {
	this->x = x;
	this->y = y;
	this->r = r;
	this->xV = xV;
	this->yV = yV;
	this->score = score;
	this->bleft = bleft;
	this->lives = lives;
	this->color = color;
}
void Ball::drawBall() {
	ofSetColor(color);
	ofDrawCircle(x, y, 2*r);
	ofSetCircleResolution(100);
}

//resets ball with diffrent velocity and position
void Ball::resetBall() {
	x = ofGetWidth() / 2;
	y = ofGetHeight() / 2;
	xV = ofRandom(0, 2);
	yV = ofRandom(0, 2);
}

void Ball::moveBall() {
	x += xV;
	y += yV;

	//if the ball goes beyond the player paddle reset ball
	//otherwise if the ball goes beyond comp paddle gain 100 points and reset ball
	if (x <= r) {
		x = r;
		xV *= -1;
		--lives;
		//if the score is more than 0 then lose a point otherwise keep at 0
		if (score == -1) {
			score = 0;
		}
		else if (score > 0) {
			score -= 1;
			
		}
		resetBall();
	}
	else if (x >= ofGetWindowWidth() - r) {
		score += 100; 
		resetBall();
		
	}
	//bounderies limit the ball can go to from top to bottom
	if (y <= (150 + r)) {
		y = (150 + r);
		yV *= -1;
	}
	else if (y >= ofGetWindowHeight() - r) {
		y = ofGetWindowHeight() - r;
		yV *= -1;
	}
}

//ball bounces off the player paddle and increases score by 1/increases velocity by .5
void Ball::bounceOff(float px, float py, float pw, float ph) {
	if ((x - r) <= (px + pw)) {
		if (y < (py + ph)) {
			if (y > (py)) {
				xV *= -1;
				xV += .5;
				++score;
			}
		}
	}
}

//ball bounces off the computer paddle
void Ball::bounceOffc(float cx, float cy, float cw, float ch) {
	if ((x + r) >= (cx)) {
		if (y < (cy + ch)) {
			if (y > (cy)) {
				xV *= -1;
			}
		}
	}
}

//moves the bullet with a speed of 5
void Ball::projectileMove() {
	x += 5; 
}
