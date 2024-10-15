#include "stdafx.h"
#include "CheckWinner.h"
#include "User.h"
#include "UserScoreInfo.h"

using namespace std;

CheckWinner::CheckWinner(int betScore) {
	this->command_name = "CW";
	this->betScore = betScore;
}

void CheckWinner::execute() {
	string dummy;
	int scoreSum = 0;
	vector<User*> winner;
	vector<User*> loser;

	while (!this->scorePQ->empty()) {
		int score;

		score = this->scorePQ->top().getScore();
		if(score != -1){
			if (winner.size() == 0) {
				winner.push_back(this->scorePQ->top().getUser());
				this->scorePQ->pop();
			}
			else if (winner[0]->getCardScore() == this->scorePQ->top().getScore()) {
				winner.push_back(this->scorePQ->top().getUser());
				this->scorePQ->pop();
			}
			else {
				loser.push_back(this->scorePQ->top().getUser());
				this->scorePQ->pop();
			}
		}
		else {
			loser.push_back(this->scorePQ->top().getUser());
			this->scorePQ->pop();
		}
	}

	for (User* user : loser) {
		user->changeScore(-betScore);
		scoreSum += betScore;
	}
	if(winner.size())
		scoreSum /= winner.size();
	for (User* user : winner) {
		user->changeScore(scoreSum);
	}

	cout << endl << endl;
	cout << "-----------------------------------------" << endl;
	cout << "<���� ���α׷�>" << endl;
	cout << "-----------------------------------------" << endl;
	cout << "���� ���" << endl;
	cout << "���� ����: " << betScore << endl;
	cout << "-----------------------------------------" << endl;
	cout << "����" << endl;
	cout << "�̸�\tī�����\t�� ����" << endl << endl;

	for (User* user : winner) {
		cout << user->getName() << "\t" << user->getCardScore() << "\t\t" << user->getScore() << " (+" << scoreSum << ")"<< endl;
	}

	cout << "-----------------------------------------" << endl;
	cout << "����" << endl;
	cout << "�̸�\tī�����\t�� ����" << endl << endl;

	for (User* user : loser) {
		cout << user->getName() << "\t" << user->getCardScore() << "\t\t" << user->getScore() << " (-" << betScore << ")" << endl;
	}

	cout << "-----------------------------------------" << endl;
	cout << "����Ͻ÷��� �ƹ� Ű�� �Է��Ͽ� �ֽʽÿ�." << endl;
	cin >> dummy;
	system("cls");
}