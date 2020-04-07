#pragma once
#include"gameNode.h"
class progressBar :public gameNode
{
private:

	RECT _rcProgress;		// ü�¹� ��Ʈ
	int _x, _y;
	int _width;				//���α���(��༮���� ������)

	image* _progressBarFront;		//ü�¹� ���̹���
	image* _progressBarBack;		//ü�¹� ���̹���

public:
	progressBar();
	~progressBar();

	HRESULT init(char* frontImage, char* backImage, float x, float y, int width, int height);
	HRESULT init(char* frontImage, char* backImage, float x, float y, int width, int height , float x2 , float y2 , int width2 , int height2);
	
	void release();
	void update(int _x , int _y);
	void render(int _x, int _y);
	void render(int _x, int _y , int _x2, int _y2);
	//������ ����
	void setGauge(float currentGauge, float maxGauge);

	void setX(int x) { _x = x; }
	void setY(int y) { _y = y; }

	RECT getRect() { return _rcProgress; }
};

