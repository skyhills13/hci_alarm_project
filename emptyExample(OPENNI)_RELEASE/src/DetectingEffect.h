#pragma once
class DetectingEffect
{
public:
	DetectingEffect(void);
	~DetectingEffect(void);

	void startEffect(float x, float y);
	void update();
	void display();

private:
	int dt;
	bool visible;
	float positionX;
	float positionY;
};

