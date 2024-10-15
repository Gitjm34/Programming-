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
	void readUserFile(); //파일로부터 유저정보 받아옴
	void saveUserFile(); //유저정보들을 파일로 저장
	void readReplayFile(); //파일로부터 리플레이정보 받아옴
	void saveReplayFile(); //리플레이정보들을 파일로 저장

	void login(); //로그인 기능 수행. 중복로그인 방지
	void logout(); //로그아웃 기능 수행
	void newAccount(); //새 계정 추가(회원가입)
	void playGame(); //게임시작 함수. 게임전 초기화기능부터 각 리스트 초기화까지 진행함
	void showReplay(); //리플레이 실행. 벡터로 저장된 리플레이 정보들을 토대로 선택된 리플레이 실행
	void showUserInfo(); //유저정보 출력. 이름과 남은 점수로 출력됨

	void suffleDeck(); //덱 섞기함수. 메인덱을 섞어서 덱에 저장함, 게임실행시 덱을 사용
	void saveCommand(int betScore); //게임이 끝난 후 리플레이를 위해 사용된 커맨드들을 저장. 저장 시 베팅점수정보가 필요함

	void AISetting(); //AI게임 시 AI의 갯수 설정
	void settingOrder(); //게임 플레이순서 설정
	int bettingScore(); //베팅할 점수 설정
	void gameProcedure(); //주 게임 진행함수

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

