#include "DetectingEffect.h"
#include "ofMain.h"

#define phase_1 20
#define	phase_2 40

DetectingEffect::DetectingEffect(void)
{
	dt = 0;
	visible = false;
	positionX = 0.0f;
	positionY = 0.0f;
}


DetectingEffect::~DetectingEffect(void)
{
}

void DetectingEffect::startEffect(float x, float y){
	dt = 0;
	positionX = x;
	positionY = y;
	visible = true;
}

void DetectingEffect::update(){
	++dt;

	// check to init instance
	if (dt >= 60)
	{
		dt = 0;
		visible = false;
	}
}

void DetectingEffect::display()
{
	if (!visible)
	{
		return;
	}

	update();

	ofSetColor(30, 153, 197);
	ofEllipse(positionX, positionY, 10, 10);

	if (dt >= phase_1){
		ofSetColor(196, 15, 132);
		ofEllipse(positionX, positionY, dt - phase_1, dt - phase_1);
	}

	if (dt >= phase_2){
		ofSetColor(204, 232, 36);
		ofEllipse(positionX, positionY, dt - phase_2, dt - phase_2);
	}
}