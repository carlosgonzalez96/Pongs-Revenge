#include <conio.h>
#include <windows.h>
	#include <thread>         // std::this_thread::sleep_for
	#include <chrono>         // std::chrono::seconds
#include "ofApp.h"
#include "ball.h"
#include "paddle.h"
const int START_SCREEN = 0;
const int GAME_SCREEN = 1;
const int GAME_OVER_SCREEN = 2;

int gameState = START_SCREEN;
//--------------------------------------------------------------
void ofApp::setup(){
	ofSetBackgroundColor(0);
	compPaddleIcon.load("compPaddle.png");
	stars.load("starbg.jpg");
	paddleIcon.load("paddle.png");
	cntlIcon.load("cntl.png");
	titleIcon.load("title.png");
	gameoverIcon.load("gameover.png");
	round.loadFont("BAUHS93.ttf", 72);
	highscore.loadFont("BAUHS93.ttf", 30);
	arialblk.loadFont("ariblk.ttf", 50);
	arial.loadFont("arial.ttf",30);
	bleft.loadFont("arial.ttf", 50);
	epicMusic.loadSound("twofates.mp3");
	hit.loadSound("hit.wav");
	hit2.loadSound("hittwo.wav");
	blaster.loadSound("blaster.mp3");
	swing.loadSound("swing.wav");
	ball = new Ball(ofGetWidth() / 2, ofGetHeight() / 2, 15, ofRandom(-2, 2), ofRandom(-2, 2),0,0,3,ofColor(255));
	paddle = new Paddle(100, (ofGetHeight() / 2)- 100, 50,200, 0, ofColor(255, 0, 0));
	compPaddle = new CompPaddle(ofGetWidth() - 150, (ofGetHeight() / 2) - 100, 50, 200, 0, ofColor(21, 0, 255));
	projectile = new Ball(-100,-100, 10, 0, 0, 0, 0, 3,ofColor(255,0,0));
}

//--------------------------------------------------------------
void ofApp::update(){
	ofSetColor(225);
	if (gameState == GAME_SCREEN) {
		ball->moveBall();
		paddle->updatePlayerPaddle();
		ball->bounceOff(paddle->x, paddle->y, paddle->w, paddle->h);
		ball->bounceOffc(compPaddle->x, compPaddle->y, compPaddle->w, compPaddle->h);
		projectile->projectileMove();
		compPaddle->followBall(ball->y);
		//when the projctile touches the the computer paddle ...
		if ((projectile->x + projectile->r) >= (compPaddle->x)) {
			if (projectile->y < (compPaddle->y + compPaddle->h)) {
				if (projectile->y >(compPaddle->y)) {
					//when the projectile leaves the screen the projectile 'resets'
					projectile->x = -100;
					projectile->y = -100;
					ball->score++;
					compPaddle->deley(projectile->y);
				}
			}
		}
		
		//if statement that plays deflection sfx when ball hits human paddle
		if ((ball->x - ball->r) <= (paddle->x + paddle->w)) {
			if (ball->y < (paddle->y + paddle->h)) {
				if (ball->y >(paddle->y)) {
					hit.play();
				}
			}
		}
		//if statement that plays deflection sfx2 when ball hits computer paddle
		if ((ball->x + ball->r) >= (compPaddle->x)) {
			if (ball->y < (compPaddle->y + compPaddle->h)) {
				if (ball->y >(compPaddle->y)) {
					hit2.play();
				}
			}
		}
		//player can only shoot the freezing projectile every multiple of 10
		if (ball->score > 0) {
			if (ball->score % 3 == 0) {
				projectile->score += 1;
				projectile->bleft += 1;
			}
		}

		//When the ball touches the top & bottom boundery a sfx plays
		if (ball->y <= (ball->r + 150)) {
			swing.play();
		}
		else if (ball->y >= ofGetWindowHeight() - ball->r) {
			swing.play();
		}

		//

	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	stars.draw(0, 0,2000,2000);
	if (gameState == START_SCREEN) {
		drawStartScreen();
	}
	else if (gameState == GAME_SCREEN) {
		drawGameScreen();
//
	}
	else if (gameState == GAME_OVER_SCREEN) {
		drawGameOverScreen();
	}
}
void ofApp::drawStartScreen() {
	titleIcon.draw(ofGetWidth()/2-256, 50, 512,266);
	cntlIcon.draw((ofGetWidth() / 2) - 324, ofGetHeight() / 2 - 150, 648, 300);
	arialblk.drawString("PRESS 'SHIFT' TO PLAY", (ofGetWidth() / 2)-450, 800);
	highscore.drawString("Highest Score:0", (ofGetWidth() / 2)-150, (ofGetHeight() / 2)+350);
	epicMusic.play();
	epicMusic.setLoop(true);
}
void ofApp::drawGameScreen() {
	std::string scoreKeeper = "Score: ";
	scoreKeeper += ofToString(ball->score);
	round.drawString(scoreKeeper, (ofGetWidth() / 2) - 195, 100);
	ball->drawBall();
	paddle->drawPaddle(paddleIcon);
	compPaddle->drawCompPaddle(compPaddleIcon);

	ofFile file("HighScores.txt", ofFile::ReadWrite);
	file << ofToString(ball->score);
	file.close();

	std::string bulletsLeft = "Bullets Left: ";
	bulletsLeft += ofToString(projectile->bleft);
	bleft.drawString(bulletsLeft, 50,100);
	projectile->drawBall();

	//lives if there are no lives left change game screen to game over
	ofSetColor(225);
	if (ball->lives == 3) {
		ofDrawCircle((ofGetWidth()/2) + 500, 100, ball->r*2);
		ofDrawCircle((ofGetWidth() / 2) + 580, 100, ball->r * 2);
		ofDrawCircle((ofGetWidth() / 2) + 660, 100, ball->r * 2);
	}
	else if (ball->lives == 2) {
		ofDrawCircle((ofGetWidth() / 2) + 580, 100, ball->r * 2);
		ofDrawCircle((ofGetWidth() / 2) + 660, 100, ball->r * 2);
	}
	else if (ball->lives == 1) {
		ofDrawCircle((ofGetWidth() / 2) + 660, 100, ball->r * 2);
	}
	else if (ball->lives == 0) {
		gameState++;
	}

	//draws a boarder for the top
	ofDrawRectangle(0, 150, ofGetWidth(), 2);

}
void ofApp::drawGameOverScreen() {
	std::string scoreKeeper = "Score: ";
	scoreKeeper += ofToString(ball->score);
	gameoverIcon.draw((ofGetWidth()/2)-221.5,50, 443,278);
	arialblk.drawString(scoreKeeper, (ofGetWidth() / 2) - 150, (ofGetHeight() / 2) - 10);
	highscore.drawString("Highest Score:0", (ofGetWidth() / 2) - 150, (ofGetHeight() / 2) + 350);
	arial.drawString("PRESS 'R' TO PLAY AGIN", (ofGetWidth() / 2) - 250, (ofGetHeight() / 2) + 200);
	epicMusic.stop();
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == OF_KEY_SHIFT) {
		gameState = (gameState + 1) % 3;
	}

	if (gameState == GAME_SCREEN) {
		if (key == OF_KEY_UP) {
			paddle->movePaddleUp();
		}
		else if (key == OF_KEY_DOWN) {
			paddle->movePaddleDown();
		}
		if (key == 'r') {
			gameState--;
		}

		if (key == OF_KEY_ALT) {
			if (ball->score % 3 == 0) {
				if (projectile->score > 0) {
					projectile->x = paddle->x + paddle->w;
					projectile->y = paddle->y + paddle->h / 2;
					blaster.play();
				}
			}
			if (projectile->bleft < 0) {
				projectile->bleft = 0;
			}
			else if (projectile->bleft > 0) {
				projectile->bleft -= 1;
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
		
}


void ofApp::mouseMoved(int x, int y ){

}


void ofApp::mouseDragged(int x, int y, int button){

}


void ofApp::mousePressed(int x, int y, int button){

}


void ofApp::mouseReleased(int x, int y, int button){
	
}


void ofApp::mouseEntered(int x, int y){

}


void ofApp::mouseExited(int x, int y){

}


void ofApp::windowResized(int w, int h){

}


void ofApp::gotMessage(ofMessage msg){

}


void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
