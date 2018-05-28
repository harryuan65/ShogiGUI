#pragma once
#include"lib.h"

#ifndef GUI_H
#define GUI_H

class Entity
{
private:
	sf::Sprite sprite;
	sf::Texture texture;
public:
	int id;//For chess
	int square;//For chess
	bool visible;//For pictures
	bool proable;//For chess
	bool alreadyPro;//For chess
	sf::Vector2f pos;//For chess
	sf::Sprite getSprite();
	void setTexture(std::string filename);
	void setRect(sf::IntRect rect);//For chess
	void setFace(Entity Rfchess[],int tochess);//For chess
	void setPos(int sq,sf::Vector2f pos);//For chess
	void setPos(float x, float y);//For pictures
	void setPos(sf::Vector2f pos);//For pictures
	bool isContaining(sf::Vector2i m);
};
class LatestAction
{
public:
	int src;
	int dst;
	Entity *SrcChess;
	Entity *DstChess;
	bool pro;
};
class GUI
{
private:
	const char *modename[5] = { "玩家VS電腦","電腦VS玩家","玩家對打","電腦對打","電腦對打 本機VS其他程式" };
	Move movelist[200];
	int movelistSize;
	LatestAction Lact;
	sf::Vector2f boardPos[35];//存下0~24的圖形位置
	sf::Font font;
	sf::Text handleft[10];//手牌數量0~4白 5~9黑
	sf::Text Turn_text;
	Entity Slot[35];
	Entity SlotHover[35];
	Entity SlotDST;
	sf::Texture textureChess;
	
	Entity Piece[12];
	Entity PVPiece[12];
	Entity Rfchess[20];
	Entity PVRfchess[20];
	Entity EBackground;
	Entity ETitle;
	Entity EPKPlayer;
	Entity EPKAI;
	Entity EAIPKAI;
	Entity EBoard;
	Entity EAskPro;
	Entity EYes;
	Entity ENo;
	Entity EWwin;
	Entity EBwin;
	Entity EShowPV;
	Entity EGiveUp;
	Entity EUndoMove;
public :
	bool isOpen;
	bool isGameStarted;
	bool isGameOver;
	int Scene;
	bool GotStuff;
	bool isHold;
	bool isAskPro;
	bool NoWayToGo;
	short Turn;
	int boardStatus[35];//25~29, 30~34 棋盤上跟手牌的狀況(存棋子)
	int Mode;
	int Highlight;
	int src;
	int dst;
	bool pro;
	int win;
	int movecount;
	int roundseed;
	FileMapping fm_gm;
	FileMapping fm_mg;

	
	GUI() ;
	void LoadTexture();
	void InitEnvironment();
	Entity *FindChess(int square);
	void UndoMove();
	void GUIDoMove(bool isSurrender);
	void DoMove(int s,int d ,bool pro);
	void ResetMove();
	int HightLight();
	void HightLightOff();
	void SetMovelist(int buf[],int getsize);
	void StorePV(int buf[],int getsize);
	bool SetBoard(std::string init = "21 20 18 19 22 0 0 0 0 17 0 0 0 0 0 1 0 0 0 0 6 3 2 4 5 0 0 0 0 0 0 0 0 0 0");
	void SetCustomBoard();
	void ModeString();
	void EnableGUI();
	void StartGame(int mode);
	string GetModeName();
	//PV
	Entity *FindPVChess(int square);
	Entity PVDisplayChess[20];//小顆的
	Move NewPV[200];
	Move PV[200];
	int ResetPVboardStatus[35];
	int PVboardStatus[35];

	sf::Vector2f PVPos[12];
	int PVsquare[12];
	bool PVproable[12];
	bool PValreadyPro[12];
	int PVid[12];

	int NewpvSize;
	int pvSize;
	int pv_i;
	bool isPVon;
	void SwitchPV();
	void AIDoMove();
	void PV_DoMove();
	void UpdatePVnBoard();
	void ResetPV();
	time_t t1,t2;
	bool movefinished;
	string fdrpath;
	sf::Image scrs;
	//Debug
	string toreadablemove(Move a);
	string readablemovelist[200];
	string readablePVlist[200];
	void ShowAllPos(bool on);
};

#endif // !DRAW_H





