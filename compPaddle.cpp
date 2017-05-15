#include "compPaddle.h"
#include "ofMain.h"
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
CompPaddle::CompPaddle() {

}
CompPaddle::CompPaddle(int x, int y, int w, int h, int v,ofColor color) {
	this->w = w;
	this->h = h;
	this->x = x;
	this->y = y;
	this->v;
	this->color = color;
}
void CompPaddle::drawCompPaddle(ofImage compPaddleIcon) {
	ofSetColor(225);
	compPaddleIcon.draw(x, y, w, h);
}


void CompPaddle::followBall(float by) {
	if (by > (y + (h / 2))) {
		y+=2;
	}
	if (by < (y + (h / 2))) {
		y-=2;
	}

}

void CompPaddle::deley(float py) {
	if (py >(y + (h / 2))) {
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	if (py < (y + (h / 2))) {
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

}