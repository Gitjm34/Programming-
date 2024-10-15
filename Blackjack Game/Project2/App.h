#pragma once
#include "stdafx.h"

class GameCommandInvoker;
class Command;
class User;
class Card;
class UserScoreInfo;

class App
{
public:
	App();//
	~App();//

	void run();//

private:
	void readUserFile(); //���Ϸκ��� �������� �޾ƿ�
	void saveUserFile(); //������������ ���Ϸ� ����
	void readReplayFile(); //���Ϸκ��� ���÷������� �޾ƿ�
	void saveReplayFile(); //���÷����������� ���Ϸ� ����

	void login(); //�α��� ��� ����. �ߺ��α��� ����
	void logout(); //�α׾ƿ� ��� ����
	void newAccount(); //�� ���� �߰�(ȸ������)
	void playGame(); //���ӽ��� �Լ�. ������ �ʱ�ȭ��ɺ��� �� ����Ʈ �ʱ�ȭ���� ������
	void showReplay(); //���÷��� ����. ���ͷ� ����� ���÷��� �������� ���� ���õ� ���÷��� ����
	void showUserInfo(); //�������� ���. �̸��� ���� ������ ��µ�

	void suffleDeck(); //�� �����Լ�. ���ε��� ��� ���� ������, ���ӽ���� ���� ���
	void saveCommand(int betScore); //������ ���� �� ���÷��̸� ���� ���� Ŀ�ǵ���� ����. ���� �� �������������� �ʿ���

	void AISetting(); //AI���� �� AI�� ���� ����
	void settingOrder(); //���� �÷��̼��� ����
	int bettingScore(); //������ ���� ����
	void gameProcedure(); //�� ���� �����Լ�

private:
	std::vector<User*> userList;
	
	std::vector<User*> playerList;
	std::vector<User*> alivePlayerList;
	std::vector<std::vector<User*> > playerListForReplay;

	std::vector<Card*> mainDeck;
	std::vector<Card*> deck;
	std::vector<std::vector<Card*> > shuffledDeckForReplay;

	std::priority_queue<UserScoreInfo, std::vector<UserScoreInfo>, std::less<UserScoreInfo> > scorePQ;
	std::vector<int> betScoreForReplay;
	
	std::vector<std::vector<Command*> > replayLog;
	GameCommandInvoker *gci;
};

