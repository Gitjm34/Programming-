#include "stdafx.h"
#include "PersonalHitRequest.h"
#include "Card.h"
#include "User.h"

using namespace std;

PersonalHitRequest::PersonalHitRequest(int player, bool isReplay) {
	this->command_name = "PHR";
	this->requestedPlayerIndex = player;
	this->isReplay = isReplay;
}

void PersonalHitRequest::execute() {
	(*this->playerList)[this->requestedPlayerIndex]->addCard(this->cardDeck->back());
	this->cardDeck->pop_back();

	if ((*this->playerList)[this->requestedPlayerIndex]->getID() != AI || isReplay) {
		cout << endl << endl;
		cout << "-----------------------------------------" << endl;
		cout << "<블랙잭 프로그램>" << endl;
		cout << "-----------------------------------------" << endl;
		cout << "블랙잭 게임" << endl;
		cout << "-----------------------------------------" << endl;
		cout << (*this->playerList)[this->requestedPlayerIndex]->getName() << "님" << endl << endl;
		cout << "카드를 한 장 받았습니다." << endl;
		cout << "-----------------------------------------" << endl << "\n\n\n\n\n\n\n\n";

		for (u_int j = 0; j < (*this->playerList)[this->requestedPlayerIndex]->getUserCard().size(); j++) {
			Sleep(PRINT_DELAY);
			(*this->playerList)[this->requestedPlayerIndex]->getUserCard()[j]->CardPrint(100*j, 0);
		}

		cout << "현재 카드숫자 총합(최적화): " << (*this->playerList)[this->requestedPlayerIndex]->getCardScore() << endl;
		cout << "-----------------------------------------" << endl;
		if ((*this->playerList)[this->requestedPlayerIndex]->getCardScore() > 21) {
			cout << "패배하셨습니다." << endl;
		}
		cout << " 초 뒤 다음 화면으로 넘어갑니다.";
		for (int i = DELAY; i > 0; i--) {
			cout << "\r";
			cout << i;
			cout << "\t\t\t\t";
			Sleep(1000);
		}
		system("cls");
	}
	
}

void PersonalHitRequest::setIndex(int index) {
	this->requestedPlayerIndex = index;
}

void PersonalHitRequest::setReplay() {
	this->isReplay = true;
}
