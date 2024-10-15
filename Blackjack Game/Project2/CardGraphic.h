#pragma once
#include "stdafx.h"

#pragma comment(lib, "Gdiplus.lib")

class Card;

class CardGraphic {
public:
	CardGraphic(std::string fileName); //GDI+ �ʱ�ȭ �� �����̸� �޾ƿ���
	~CardGraphic(); //GDI+ �޸� �� ��ȯ

	void print(int x, int y, Card* card); //x, y��ǥ�� �ش��ϴ� card���
	void getFile(const std::string fileName); //fileName�� ������ ������ �޾ƿ�. ��δ� .\res\

private:
	ULONG_PTR gdiplusToken;
	Gdiplus::Graphics *pGraphics;
	Gdiplus::Image *pImage;
	
};