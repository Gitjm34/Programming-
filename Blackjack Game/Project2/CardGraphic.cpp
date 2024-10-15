#include "stdafx.h"
#include "CardGraphic.h"
#include "Card.h"

using namespace std;
using namespace Gdiplus;

CardGraphic::CardGraphic(string fileName) {
	GdiplusStartupInput gdiplusStartupInput;
	this->gdiplusToken = NULL; // ��ū NULL ����
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	this->pGraphics = new Graphics(GetDC(GetConsoleWindow()));
	this->pImage = nullptr;
	this->getFile(fileName);
}

CardGraphic::~CardGraphic() {
	delete pImage;
	delete pGraphics;
	GdiplusShutdown(gdiplusToken); // �̹��� ����
}

void CardGraphic::print(int x, int y, Card* card) {
	int m_x, m_y; 
	int card_x;
	int card_y;

	m_x = x + 20;
	m_y = y + 180;

	card_x = card->getNum() * 79;
	card_y = card->getSuit() * 110;

	if (this->pImage)
		pGraphics->DrawImage(pImage, Rect(m_x, m_y, 80, 100), card_x, card_y, 75, 100, UnitPixel);
	else
		cout << "File Read Error";
}

void CardGraphic::getFile(string fileName) {
	if (pImage != nullptr) {
		delete pImage;
		pImage = nullptr;
	}

	string addr;

	addr = ".\\res\\" + fileName; // �� ���� �̸�

	wstring waddr(addr.begin(), addr.end()); // image�Ķ���Ͱ� wstring�̹Ƿ� ����ȯ

	this->pImage = pGraphics ? new Image(waddr.c_str()) : NULL;
}