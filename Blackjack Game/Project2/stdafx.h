#pragma once
#include<iostream>
#include<vector>
#include<queue>
#include<string>
#include<fstream>
#include<Windows.h>
#include<ctime>
#include<stdlib.h>
#include<sstream>
#include<gdiplus.h>

#define INIT_SCORE 10000
#define INIT_CARD_NUM 2
#define MAX_CARD 51
#define AI -1

#define PLAYER_LIST *(vector<User*>*)
#define CARD_LIST *(vector<Card*>*)
#define COMMAND_LIST *(vector<Command*>*)
#define BETSCORE (int*)

#define DELAY 3
#define PRINT_DELAY 5

enum COMMAND { CHECK_LOSER, CHECK_WINNER, INITIAL_CARD_DISTRIBUTION, PERSONAL_HIT_REQUEST, PERSONAL_STOP_REQUEST, REPLAY };
enum REPLAY_MENU { PLAYER, DECK, COMMAND, SCORE };