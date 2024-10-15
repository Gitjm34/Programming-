#pragma once
#include "stdafx.h"

#pragma comment(lib, "Gdiplus.lib")

class Card;

class CardGraphic {
public:
	CardGraphic(std::string fileName); //GDI+ 초기화 및 파일이름 받아오기
	~CardGraphic(); //GDI+ 메모리 등 반환

	void print(int x, int y, Card* card); //x, y좌표에 해당하는 card출력
	void getFile(const std::string fileName); //fileName을 가지는 파일을 받아옴. 경로는 .\res\

private:
	ULONG_PTR gdiplusToken;
	Gdiplus::Graphics *pGraphics;
	Gdiplus::Image *pImage;
	
};