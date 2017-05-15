#pragma once
#include "ball.h"
#include "paddle.h"
#include "compPaddle.h"
#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		Ball* ball;
		Ball* projectile;
		Paddle* paddle;
		CompPaddle* compPaddle;
		void setup();
		void update();
		void draw();
		ofTrueTypeFont round;
		ofTrueTypeFont arial;
		ofTrueTypeFont arialblk;
		ofTrueTypeFont highscore;
		ofTrueTypeFont bleft;
		ofImage paddleIcon;
		ofImage compPaddleIcon;
		ofImage cntlIcon;
		ofImage titleIcon;
		ofImage stars;
		ofImage gameoverIcon;
		ofSoundPlayer epicMusic;
		ofSoundPlayer hit;
		ofSoundPlayer hit2;
		ofSoundPlayer blaster;
		ofSoundPlayer swing;

		void drawStartScreen();
		void drawGameScreen();
		void drawGameOverScreen();
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
};
