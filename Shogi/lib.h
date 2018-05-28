#pragma once
#ifndef LIB_H
#define LIB_H

#include<SFML/Graphics.hpp>
#include"FileMapping.h"
#include"Types.h"
#include"GUI.h"
#include<iostream>
#include<sstream>
#include<time.h>
#include<Windows.h>
using namespace std;
#define CHESSWIDTH 51
#define CHESSHEIGHT 74 
#define SLOTWIDTH 79
#define SLOTHEIGHT 94
#define BOARD_SIZE 35
#define PIECES_INGAME_AMOUNT 12
#define DEBUG_MODE false
#define NEEDSCRSHOT false
#define TURNSTR_FONTSIZE 25
#define PVSPEED 1.5 //sec
enum IndicatorType {
	GAMEMODE = 1, ACK, MOVELIST, DOMOVE, AIPV, GAMEOVER, RESTART
};
enum GAMEMODE {
	PlayervsAI,AIvsPlayer,PlayervsPlayer,AIvsAI,AIvsOtherAI
};
enum Win {
	NOONEWIN = -1,WHITEWIN,BLACKWIN
};
enum SceneType {
	Lobby, Ingame
};
enum TurnType {
	Player1, Player2, AI1, AI2
};
const int chessID[] = { 1,2,3,4,5,6,9,10,12,13,17,18,19,20,21,22,25,26,28,29 };
const int Name2Index[] = { -2, 0, 1, 2, 3, 4, 5,-1,-1, 6, 7, -1,8, 9,-1,-1,-1,10,11,12,13,14,15,-1,-1,16,17,-1,18,19 };
const string TurnStr[] = { "Player1","Player2","AI1","AI2" };
const string chessname[] = {"步","銀","金","角","飛","王","偷","全","龍","馬","步","銀","金","角","飛","玉","偷","全","龍","馬" };



#endif // !1