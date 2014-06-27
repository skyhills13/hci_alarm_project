#include "Ball.h"
#include "testApp.h"
#include <stdlib.h>
#include "ofGraphics.h"
#include <math.h>
#include "ofLog.h"

//int goalCount = 0;

Ball::Ball(void)
{
	//make it real random
	positionX = (float)(rand()%640);
	positionY = (float)(rand()%480);
	velocityX = 8.0f;
	velocityY = 8.0f;

	radius = 30;
	//initial color of the ball is perfect Green
	colorRed = 0;
	colorGreen = 255;

	//hitCount = 0;
}

Ball::~Ball(void)
{
}

/*
void Ball::setColor( int hitCount )
{
	colorRed = (int)( 255 * ( hitCount/MAX_HIT_COUNT ) );
	colorGreen = (int)( 255* ( 1-( hitCount/MAX_HIT_COUNT ) ) );
}
*/

void Ball::isCollided( float handX, float handY )
{
	double collisionRange = sqrt(pow((positionX-handX),2) + pow((positionY-handY),2));
	if(collisionRange <= radius)
	{
		velocityX+=2.f;
		velocityY+=2.f;
		velocityY = (-1) * velocityY;
		velocityX = (-1) * velocityX;
		
		/*
		if(hitCount < MAX_HIT_COUNT) 
		{
			hitCount+=1;	
			velocityX+=2;
			velocityY+=2;
			velocityY = (-1) * velocityY;
			//ofLog(OF_LOG_NOTICE,"hit count: %d", hitCount);
		}
		*/
	}
}


void Ball::checkGoalIn(float goalX, float goalY)
{
	double collisionRange = sqrt(pow((positionX-goalX),2) + pow((positionY-goalY),2));
	if (collisionRange <= radius)	
	{	
		positionX = 320.0f;
		positionY = 30.0f;
		velocityX = 0.0f;
		velocityY = 0.0f;
		colorGreen = 0;
		colorRed = 255;
	}
}

void Ball::display()
{
	update();

	ofSetColor(colorRed, colorGreen, 0);
	ofCircle(positionX, positionY, radius);
}

void Ball::update()
{
	checkGoalIn(320.0f, 20.0f);
	//if the speed is too fast, checkGoalIn does not work
	if( velocityX > 30.f
		|| velocityY > 30.f
		|| velocityX + velocityY > 50.f)
	{
		velocityX = 1.0f;
		velocityY = 1.0f;
	}
	positionX += velocityX;
	positionY += velocityY;
	//setColor(hitCount);
	
	if(positionX >= ofGetViewportWidth() || positionX <= 0) {
		velocityX = (-1) * velocityX;
	}
	if( positionY >= ofGetViewportHeight() || positionY <= 0) {
		velocityY = (-1) * velocityY;
	}
	//isCollided(handX, handY);
}


