#ifndef _TEST_APP
#define _TEST_APP

#include "ofxOpenNI.h"
#include "ofMain.h"
#include "Ball.h"
#include "DetectingEffect.h"
#include <array>

#define MAX_DEVICES 2
#define MAX_NUMBER_OF_HAND 4
#define START_BALL_COUNT 15

class testApp : public ofBaseApp{

public:
    
	void setup();
	void update();
	void draw();
    void exit();
    
	void keyPressed  (int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);

	ofSoundPlayer soundPlayer;

private:
 
	void handEvent(ofxOpenNIHandEvent & event);

    
	Ball* ball[START_BALL_COUNT];
	ofxOpenNI openNIDevice;
    ofTrueTypeFont verdana;
    
	std::array<DetectingEffect*, MAX_NUMBER_OF_HAND> detectingEffectList;
	unsigned int detectingEffectIdx;
};

#endif
