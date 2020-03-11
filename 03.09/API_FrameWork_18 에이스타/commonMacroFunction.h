#pragma once

//==================================================
//commonMacroFunction(필요한 부분은 직접 만들어보시오)
//==================================================

//포인트
inline POINT PointMake(int x, int y)
{
	POINT pt = { x ,y };
	return pt;
}
//선그리는 함수
inline void LineMake(HDC hdc, int x1, int y1, int x2, int y2)
{
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
}
inline void LineMake(HDC hdc, POINT p1, POINT p2)
{
	MoveToEx(hdc, p1.x, p1.y, NULL);
	LineTo(hdc, p2.x, p2.y);
}
//RECT만들기(좌상단 기준)
inline RECT RectMake(int x, int y, int width, int height)
{
	RECT rc = { x,y, x + width, y + height };
	return rc;
}
//RECT만들기(중심점으로 부터)
inline RECT RectMakeCenter(int x, int y, int width, int height)
{
	RECT rc = { x - width / 2, y - height / 2, x + width / 2, y + height / 2 };

	return rc;
}
//사각형 그리기
inline void RectangleMake(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, x + width, y + height);
}
inline void RectangleMake(HDC hdc, RECT rect)
{
	Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
}
//사각형 그리기(중심점)
inline void RectangleMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2));
}
//원그리기
inline void EllipseMake(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x, y, x + width, y + height);
}
//원그리기(중심점)
inline void EllipseMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2));

}
inline void BeginSolidColor(HDC hdc, HBRUSH* brush, COLORREF color)
{
	*brush = CreateSolidBrush(color);
	*brush = (HBRUSH)SelectObject(hdc, *brush);

}

//투명 사각형 그리기
inline void AlphaRectangle(HDC hdc, int left, int top, int right, int bottom)
{
	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);

	Rectangle(hdc, left, top, right, bottom);

	SelectObject(hdc, oldBrush);
	DeleteObject(myBrush);
}

inline void printText(HDC _hdc, const char* _str, const char * _font, int _destX, int _destY,
	int _fontSize, COLORREF _fontColor, bool _isBgTransParent, COLORREF _bgColor)
{
	HFONT curFont, oldFont;
	COLORREF oldBkColor, oldFontColor;
	int len = strlen(_str);
	if (_fontColor != RGB(244, 244, 233))
		oldFontColor = SetTextColor(_hdc, _fontColor);
	if (_bgColor != RGB(255, 255, 255))
		oldBkColor = SetBkColor(_hdc, _bgColor);
	if (_isBgTransParent)
		SetBkMode(_hdc, TRANSPARENT);
	else
		SetBkMode(_hdc, OPAQUE);

	curFont = CreateFont(_fontSize, 0, 0, 0, FW_DONTCARE,
		FALSE, FALSE, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		FF_DONTCARE, _font
	);

	oldFont = (HFONT)SelectObject(_hdc, curFont);
	TextOut(_hdc, _destX, _destY, _str, len);
	SelectObject(_hdc, oldFont);

	DeleteObject(curFont);
	if (_fontColor != RGB(0, 0, 0))
		SetTextColor(_hdc, oldFontColor);
	if (_bgColor != RGB(255, 255, 255))
		SetBkColor(_hdc, oldBkColor);
	if (_isBgTransParent)
		SetBkMode(_hdc, OPAQUE);
}
