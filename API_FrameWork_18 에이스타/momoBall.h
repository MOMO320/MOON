#pragma once
#include "objectManager.h"

class momoBall : public objectManager
{
public:
	momoBall();
	~momoBall();

	HRESULT init(char * imgaeName , int bulletMax , float range);
	void release();
	void update();
	void render();

	void fire(float x, float y, float angle, float speed);
	void move();

	//ÃÑ¾Ë »èÁ¦
	void connectBullet(int addNum);
	void removeBullet(int arrNum);
	bool getFullobject() { return isFullObject; }
	void setFullobject(bool _isFull) { isFullObject = _isFull; }
	void setAni(bool _ani) { isAni = _ani; }


	vector<objectBullet> getVBall() { return m_vBullet; }
	vector<objectBullet>::iterator getVIBall() { return m_viBullet; }


private:
	vector<objectBullet> m_vBullet;
	vector<objectBullet>::iterator m_viBullet;

	const char* m_imageName;
	float m_range;
	int m_bulletMax;

	float time;
	float addDeley = 0.1f;
	float pastTime = 0;

	float objectPastTime = 0;
	float objectDeley = 0.5f;
	int ballCount = 0;

	bool isFullObject = false;
	bool isAni = false;


};

