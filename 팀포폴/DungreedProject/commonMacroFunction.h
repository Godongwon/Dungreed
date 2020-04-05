#pragma once

//==================================================
//commonMacroFunction(�ʿ��� �κ��� ���� �����ÿ�)
//==================================================

//����Ʈ
inline POINT PointMake(int x, int y)
{
	POINT pt = { x ,y };
	return pt;
}
//���׸��� �Լ�
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
//RECT�����(�»�� ����)
inline RECT RectMake(int x, int y, int width, int height)
{
	RECT rc = { x,y, x + width, y + height };
	return rc;
}
//RECT�����(�߽������� ����)
inline RECT RectMakeCenter(int x, int y, int width, int height)
{
	RECT rc = { x - width / 2, y - height / 2, x + width / 2, y + height / 2 };

	return rc;
}
//�簢�� �׸���
inline void RectangleMake(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, x + width, y + height);
}
inline void RectangleMake(HDC hdc, RECT rect)
{
	Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
}
//�簢�� �׸���(�߽���)
inline void RectangleMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2));
}
//�簢�� �׸���(Color)
inline void ColorRect(HDC hdc, RECT rc, COLORREF color)
{
	// �귯�� �����ϴ� �κ�
	HBRUSH rectBrush = (HBRUSH)CreateSolidBrush(color);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, rectBrush);
	// �簢�� �׸��� �Լ�
	Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
	// �귯�� �����ϴ� �κ�
	SelectObject(hdc, oldBrush);
	DeleteObject(rectBrush);
}
// �� �簢�� �׸��� (Color)
inline void ColorFrameRect(HDC hdc, RECT rc, COLORREF color = RGB(0, 0, 0))
{
	// �귯�� �����ϴ� �κ�
	HBRUSH rectBrush = (HBRUSH)CreateSolidBrush(color);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, rectBrush);
	// �簢�� �׸��� �Լ�
	FrameRect(hdc, &rc, rectBrush);
	// �귯�� �����ϴ� �κ�
	SelectObject(hdc, oldBrush);
	DeleteObject(rectBrush);
}
//���׸���
inline void EllipseMake(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x, y, x + width, y + height);
}
//���׸���(�߽���)
inline void EllipseMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2));

}
// ���� ��Ʈ �ٲ㼭 ����ϴ� �Լ�
inline void FontTextOut(HDC hdc, int drawX, int drawY, char * str, 
	int fontSize, char * fontName, COLORREF color = RGB(0, 0,0))
{
	// ������ ������ �ٲٴ� �κ�
	COLORREF oldTextColor = SetTextColor(hdc, color);
	// ������ ��Ʈ�� �ٲٴ� �κ�
	HFONT font = CreateFont(fontSize, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 
		0, 0, 0, 0, fontName);
	HFONT oldFont = (HFONT)SelectObject(hdc, font);
	// ����� �����ϰ� �ٲٴ� �κ�
	SetBkMode(hdc, TRANSPARENT);
	TextOut(hdc, drawX, drawY, str, strlen(str));
	// �ٲ�� ���� ������ �����ϴ� �κ�
	SetTextColor(hdc, oldTextColor);
	// ��Ʈ�� �����ϴ� �κ�
	SelectObject(hdc, oldFont);
	DeleteObject(font);
}
