#pragma once

#define MAX_HIT_COUNT 5

class Ball
{
public:
	Ball(void);
	~Ball(void);

	void setColor(int hitCount);
	void isCollided(float posX, float posY);
	void checkGoalIn(float goalX, float goalY);


	void display();
	void update();

	float positionX;
	float positionY;
	//velocity is basically constant
	float velocityX;
	float velocityY;
	
	int radius;
	int colorRed;
	int colorGreen;
	//int colorBlue;

	int hitCount;
	//static int mersigi;

};

//extern int goalCount;