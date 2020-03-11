#pragma once
#include "singletonBase.h"

class cameraManager : public singletonBase<cameraManager>
{
private:
	image* _camera;

	POINT _center;

	POINT _cameraXY;

public:
	cameraManager();
	~cameraManager();

	HRESULT init();
	void relaese();
	void update();
	void render(image* img);

	void setCameraCenter(POINT point);

	POINT getCameraCenter() { return _center; }
	POINT getCameraXY() { return _cameraXY; }

	HDC getCameraDC() { return _camera->getMemDC(); }

};