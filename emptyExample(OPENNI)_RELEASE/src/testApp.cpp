#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {
    ofSetLogLevel(OF_LOG_VERBOSE);
    openNIDevice.setup();
    openNIDevice.addImageGenerator();
    openNIDevice.addDepthGenerator();
    openNIDevice.setRegister(true);
    openNIDevice.setMirror(true);

    // setup the hand generator
    openNIDevice.addHandsGenerator();
	
    // add all focus gestures (ie., wave, click, raise arm)
    openNIDevice.addAllHandFocusGestures();
    
    // or you can add them one at a time
    //vector<string> gestureNames = openNIDevice.getAvailableGestures(); // you can use this to get a list of gestures
                                                                         // prints to console and/or you can use the returned vector
    
	//openNIDevice.addHandFocusGesture("Wave");
    
    openNIDevice.setMaxNumHands(MAX_NUMBER_OF_HAND);
    
    openNIDevice.start();
    
    verdana.loadFont(ofToDataPath("verdana.ttf"), 24);

	for ( int i = 0; i < START_BALL_COUNT ; ++i)
	{
		ball[i] = new Ball();
	}

	for (int i = 0; i < MAX_NUMBER_OF_HAND; ++i)
	{
		detectingEffectList[i] = new DetectingEffect();
	}

	detectingEffectIdx = 0;

	// hand event를 담당하는 리스너 등록
	ofAddListener(openNIDevice.handEvent, this, &testApp::handEvent);

	soundPlayer.loadSound("morningcall.mp3");
	soundPlayer.setLoop(true);
	soundPlayer.play();
}

//--------------------------------------------------------------
void testApp::update(){
    openNIDevice.update();
	int numberOfGoalInBall = 0;

	for(int i = 0; i < START_BALL_COUNT ; i++) {
		if (ball[i]->colorRed == 255) {
			numberOfGoalInBall ++;
		}
	}

	if (numberOfGoalInBall == START_BALL_COUNT) {
		soundPlayer.stop();
		openNIDevice.stop();
		ofBaseApp::exit();
		std::exit(1);
	}

}

//--------------------------------------------------------------
void testApp::draw(){
	ofSetColor(255, 255, 255);
	
    
    ofPushMatrix();
    // draw debug (ie., image, depth, skeleton)
    //openNIDevice.drawDebug();
	openNIDevice.drawImage();
	//openNIDevice.drawDepth();
    ofPopMatrix();
    
	ofPushMatrix();
	ofSetColor(255,123,155);
	ofRect(300.f, 0.f, 60, 60);
	ofPopMatrix();

    ofPushMatrix();
    // get number of current hands
    int numHands = openNIDevice.getNumTrackedHands();
    
    // iterate through users
    for (int i = 0; i < numHands; i++){
        
        // get a reference to this user
        ofxOpenNIHand & hand = openNIDevice.getTrackedHand(i);
        
        // get hand position
        ofPoint & handPosition = hand.getPosition();
        // do something with the positions like:
        
        // draw a rect at the position (don't confuse this with the debug draw which shows circles!!)
        ofSetColor(255,0,0);
        ofRect(handPosition.x, handPosition.y, 20, 20);
        
    }
    ofPopMatrix();

	// 손을 찾았을 때 그려지는 이펙트를 화면에 그림
	for (int i = 0; i < MAX_NUMBER_OF_HAND; ++i)
	{
		detectingEffectList[i]->display();
	}
    
    // draw some info regarding frame counts etc
	ofSetColor(0, 255, 0);
	string msg = " MILLIS: " + ofToString(ofGetElapsedTimeMillis()) + " FPS: " + ofToString(ofGetFrameRate()) + " Device FPS: " + ofToString(openNIDevice.getFrameRate());
    
	verdana.drawString(msg, 20, openNIDevice.getNumDevices() * 480 - 20);

	//ofPushMatrix();
	for( int i = 0; i < START_BALL_COUNT ; ++i ) {
		ofPushMatrix();	
		ball[i]->display();
		ofPopMatrix();
	}
	//ofPopMatrix();
}

//--------------------------------------------------------------
void testApp::handEvent(ofxOpenNIHandEvent & event){
    // show hand event messages in the console
    // ofLogNotice() << getHandStatusAsString(event.handStatus) << "for hand" << event.id << "from device" << event.deviceID;

	// 앞에서 등록한 리스너에 의해서 이벤트가 발생하면 불려지는 함수
	// hand에 관련된 모든 이벤트에 반응을 하므로 여기서 특정 이벤트의 경우를 판단해서 다른 작업을 할 수 있게 설정
	if (event.handStatus == HAND_TRACKING_STARTED)
	{
		// 새로운 손을 찾았을 경우 아래의 이펙트 표현
		detectingEffectList[detectingEffectIdx]->startEffect(event.position.x, event.position.y);
		detectingEffectIdx = (detectingEffectIdx + 1) % MAX_NUMBER_OF_HAND;
	}

	for(int i = 0; i < START_BALL_COUNT ; ++i){
		ball[i]->isCollided(event.position.x, event.position.y);
	}
}

//--------------------------------------------------------------
void testApp::exit(){
	openNIDevice.stop();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}