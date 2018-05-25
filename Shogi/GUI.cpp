#include"lib.h"
void Entity::setTexture(std::string filename)
{
	std::string text = "images/" + filename + ".png";
	texture.loadFromFile(text);
	sprite.setTexture(texture);
}
void Entity::setRect(sf::IntRect rect)
{
	sprite.setTextureRect(rect);
}
void Entity::setFace(Entity Rfchess[], int tochess) {
	sprite.setTexture(*Rfchess[Name2Index[tochess]].sprite.getTexture(), true);
	setRect(Rfchess[Name2Index[tochess]].sprite.getTextureRect());
	id = tochess;
}
void Entity::setPos(int sq, sf::Vector2f pos)
{
	square = sq;
	sprite.setPosition(pos);
}
void Entity::setPos(float x,float y)
{
	sf::Vector2f pos(x,y);
	sprite.setPosition(pos);
}
void Entity::setPos(sf::Vector2f pos)
{
	sprite.setPosition(pos);
}
bool Entity::isContaining(sf::Vector2i m)
{
	return sprite.getGlobalBounds().contains(m.x, m.y);
}
sf::Sprite Entity::getSprite() {
	return sprite;
}


void GUI::LoadTexture()
{
	EBackground.setTexture("Background");
	ETitle.setTexture("Title");
	EButton1.setTexture("Button1");
	EButton2.setTexture("Button2");
	EBoard.setTexture("Board_new");
	EAskPro.setTexture("Pro");
	EYes.setTexture("Yes");
	ENo.setTexture("No");
	EWwin.setTexture("Wwin_F");
	EBwin.setTexture("Bwin_F");
	EShowPV.setTexture("Button_ShowPV");
	EGiveUp.setTexture("Button_GiveUp");
	EUndoMove.setTexture("Button_UndoMove");
}
void GUI::InitEnvironment()
{
	ETitle.setPos(187.0f, 40.0f);
	EButton1.setPos(288.0f, 211.0f);
	EButton2.setPos(288.0f, 324.0f);
	EBoard.setPos(0.0f, 0.0f);
	
	//Board blocks 0~25
	for (int i = 0, k = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			boardPos[k].x = (float)(58 + j * 80);
			boardPos[k].y = (float)(164 + i * 95);
			//MovableSlots
			sf::Vector2f pos(43.0f + (SLOTWIDTH + 1)*j, 150.0f + (SLOTHEIGHT + 2)*i);
			Slot[k].setTexture("rect_b_g45");
			Slot[k].setPos(pos);
			SlotHover[k].setTexture("rect_b_grey34");
			SlotHover[k].setPos(pos);
			boardStatus[k] = 0;
			k++;
		}
	}
	//Hand blocks = Board 25~29 30~34
	float x = 58;
	float y1 = 52,y2 = 654;
	for (int i = 0, k = 25; i < 2; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			boardPos[k] = sf::Vector2f(x+j*80.0f,(i == 1?y2:y1));
			Slot[k].setTexture("rect_h_g45");
			Slot[k].setPos(boardPos[k]);
			SlotHover[k].setTexture("rect_h_grey34");
			SlotHover[k].setPos(boardPos[k]);
			boardStatus[k] = 0;
			PVboardStatus[k] = boardStatus[k];
			k++;
		}
	}
	//Set Reference Chess Textures
	for (int i = 0, k = 0; i < 2; i++)//ROW
	{
		for (int j = 0; j < 10; j++)//COLUMN
		{
			
			Rfchess[k].setTexture("Shogi");
			Rfchess[k].setRect(sf::IntRect(j*CHESSWIDTH, i*CHESSHEIGHT, CHESSWIDTH, CHESSHEIGHT));
			Rfchess[k].visible = true;
			Rfchess[k].setPos(boardPos[k]);
			Rfchess[k].id = chessID[k];

			PVRfchess[k].setTexture("Shogi_plain");
			PVRfchess[k].setRect(sf::IntRect(j*CHESSWIDTH, i*CHESSHEIGHT, CHESSWIDTH, CHESSHEIGHT));
			PVRfchess[k].visible = true;
			PVRfchess[k].setPos(boardPos[k]);
			PVRfchess[k].id = chessID[k];
			switch (chessID[k])
			{
			case 6:
			case 22:
			case 3:
			case 19:
				Rfchess[k].proable = false;
				PVRfchess[k].proable = false;
				break;
			default:
				Rfchess[k].proable = true;
				PVRfchess[k].proable = true;
				break;
			}
			k++;
		}
	}
	win = -1;
	x = 109;
	y1 = 107;
	y2 = 714;
	//Hand #
	for (int i = 0,k = 0; i < 2; i++) {
		for (int j = 0; j < 5; j++)
		{
			handleft[k].setFont(font);
			handleft[k].setColor(sf::Color::Black);
			handleft[k].setString(std::to_string(0));
			handleft[k].setPosition(x + j*80.0f, (i == 1? y2 : y1));
			handleft[k].setCharacterSize(35);
			k++;
		}

	}
	Turn_text.setFont(font);
	Turn_text.setColor(sf::Color::Black);
	Turn_text.setCharacterSize(20);
	Turn_text.setPosition(0.0f, 0.0f);

	EAskPro.setPos(200.0f, 170.0f);
	EYes.setPos(230.0f, 300.0f);
	ENo.setPos(420.0f, 300.0f);
	//EWwin.setPos(200.0f, 170.0f);
	//EBwin.setPos(200.0f, 170.0f);

	EShowPV.setPos(560.0f,120.0f);//160 + 90
	EGiveUp.setPos(560.0f,210.0f);
	EUndoMove.setPos(560.0f,300.0f);

	Turn = -1;
	Mode = -1;
	isAskPro = false;

	//EditMode
	movingpiece = 0;
	hlon = false;

	//Debug
	if (DEBUG_MODE)
	{
		Turn = 0;
		Mode = 2;
	}
	//PV
	isPVon = false;
	pv_i = 0;
	t1 = 0;
	t2 = 0;
}
GUI::GUI() {
	Scene = Ingame;
	src = 0;
	dst = 0;
	isHold = false;
	isEnable = false;
	RefreshScreen = false;
	if (!font.loadFromFile("棒棒體W5.TTC"))
		std::cout << "Can't load font" << std::endl;

	LoadTexture();
	InitEnvironment();
	fm_gm.Open("GUI_gm");
	fm_mg.Open("GUI_mg");
}
bool GUI::SetBoard(std::string init)
{
	int appearance[] = { 2,2,2,2,2,2 };
	stringstream ss(init);
	string token = "";
	int square = 0;//Board count from 0 to 34
	int count = 0;//Max amount of chess on the go = 12
	while (getline(ss, token, ' '))
	{
		int chessvalue = atoi(token.c_str());
		int chess = 0;
		if (Name2Index[chessvalue] == -1)//利用棋子id可以對應到一個texture來判斷是不是存在的棋子 e.g.如果Name2Index[20] = -1沒有這個棋子
		{
			cout << "[ERROR]初始化盤面失敗：無效棋子 = " << chessvalue << endl;
			return false;
		}
		else if (chessvalue > 0)
		{
			//手牌區or棋盤上
			if (square > 24)
			{
				chess = square < 29 ? square - 8 : square - 29;//看筆記對照盤面
				boardStatus[square]++;
				handleft[square - 25].setString(std::to_string(boardStatus[square]));
			
			}
			else
			{
				chess = chessvalue;
				boardStatus[square] = chess;
			}
			
				Piece[count].setFace(Rfchess, chess);
				Piece[count].proable = Rfchess[Name2Index[Piece[count].id]].proable;
				Piece[count].setPos(square, boardPos[square]);
			
			
		/*	cout << chessname[Name2Index[Piece[count].id]]<<" id = "<< Piece[count].id <<"參考至"<<Rfchess[count].id  << endl;
			cout << chessname[Name2Index[Piece[count].id]]<<(Piece[count].proable?"可以":"不行")<<"升變" << endl;*/
			//檢查兵種數量
			if (chess == 1 || chess == 17 || chess == 9 || chess == 25)
				appearance[0]--;
			else if (chess == 2 || chess == 18 || chess == 10 || chess == 26)
				appearance[1]--;
			else if (chess == 3 || chess == 19)
				appearance[2]--;
			else if (chess == 4 || chess == 20 || chess == 12 || chess == 28)
				appearance[3]--;
			else if (chess == 5 || chess == 21 || chess == 13 || chess == 29)
				appearance[4]--;
			else if (chess == 6 || chess == 22)
				appearance[5]--;

			for (int i = 0; i < 6; i++)
				if (appearance[i] < 0)
				{
					cout << "[ERROR]兵種數量不符" << endl;
					return false;
				}

			count++;
		}
		square++;
	}


	cout << "[SetBoard]Board initialized " << endl;
}
void GUI::SetCustomBoard() {
	bool ok = false;
	char initboard[256];
	do
	{
		cout << "[SetCustomBoard]請輸入棋盤 共35格 (e.g \"21 20 18 19 22 0 0 0 0 17 0 0 0 0 0 1 0 0 0 0 6 3 2 4 5 0 0 0 0 0 0 0 0 0 0\")";
		cin.getline(initboard, 256);

		if (initboard[0] == '-') {
			cout << "[SetCustomBoard]取消設定盤面" << endl;
		}
		cout << initboard << endl;
		ok = SetBoard(initboard);
		if (!ok)cout << "[SetCustomBoard]格式錯誤! 或輸入 \"-\"以退出設定 " << endl;
	} while (!ok);
}

//Move, Win
Entity * GUI::FindChess(int square)
{
	for (int i = 0; i < 12; i++)
		if (Piece[i].square == square)
			return &Piece[i];
		
	return NULL;
}
void GUI::UndoMove() {
	Entity *SrcChess = Lact.SrcChess;
	Entity *DstChess = Lact.DstChess;
	int src = Lact.src;
	int dst = Lact.dst;
	int pro = Lact.pro;
	if (src > 25)//Hand
	{
		(*SrcChess).setPos(src, boardPos[src]);
		boardStatus[src]++;
		boardStatus[dst] = 0;
	}
	else
	{
		if (DstChess == NULL)//Move
		{
			(*SrcChess).setPos(src, boardPos[src]);
			boardStatus[src] = boardStatus[dst];
			boardStatus[dst] = 0;
		}
		else//Eat
		{
			if ((*DstChess).alreadyPro)
			{
				(*DstChess).setFace(Rfchess, (*DstChess).id + 8);
			}
			if (pro) (*SrcChess).setFace(Rfchess, (*SrcChess).id - 8);
			(*SrcChess).setPos(src, boardPos[src]);
			(*DstChess).setPos(dst,boardPos[dst]);
			boardStatus[src] = (*SrcChess).id;//不用boardStatus[dst] 是因為除掉升變
			boardStatus[dst] = (*DstChess).id;
			
		}
	}
	Turn = !Turn;

}
void GUI::DoMove(int src, int dst, bool pro) {
	Entity *SrcChess = FindChess(src);
	Entity *DstChess = FindChess(dst);
	if (SrcChess != NULL)
	{
		if (src > 24 && boardStatus[src] > 0)//Hand
		{
			(*SrcChess).setPos(dst, boardPos[dst]);
			boardStatus[src]--;
			boardStatus[dst] = (*SrcChess).id;
			handleft[src - 25].setString(std::to_string(boardStatus[src]));;
			cout << "\t[DoMove]打入:" << chessname[Name2Index[(*SrcChess).id]] << ":(" << src << ")至(" << dst << ")" << endl;
		}
		else
		{
			if (boardStatus[dst] == 0)//Move
			{
				(*SrcChess).setPos(dst, boardPos[dst]);
				boardStatus[dst] = boardStatus[src];
				boardStatus[src] = 0;
				cout << "\t[DoMove]移動:" << chessname[Name2Index[(*SrcChess).id]] << ":(" << src << ")至(" << dst << ")" << endl;
			}
			else if (boardStatus[dst] > 0)//Eat
			{
				if ((*DstChess).id == 6)
					win = 1;
				else if ((*DstChess).id == 22)
					win = 0;
				else
				{
					(*SrcChess).setPos(dst, boardPos[dst]);
					if ((*DstChess).alreadyPro)
					{
						(*DstChess).alreadyPro = false;
						(*DstChess).setFace(Rfchess, (*DstChess).id - 8);
					}
					int sendpos = (*DstChess).id > 16 ? (*DstChess).id + 13 : (*DstChess).id + 24;//本行只適用於黑白未升變的棋子
					(*DstChess).setFace(Rfchess, (*DstChess).id ^ 16);
					(*DstChess).setPos(sendpos, boardPos[sendpos]);
					boardStatus[dst] = boardStatus[src];
					boardStatus[src] = 0;
					boardStatus[sendpos]++;
					handleft[sendpos - 25].setString(std::to_string(boardStatus[sendpos]));
					cout << "\t[DoMove]" << chessname[Name2Index[(*SrcChess).id]] << "從(" << src << "(" << ":吃" << chessname[Name2Index[(*DstChess).id]] << "至(" << sendpos << ")" << endl;
				}

			}
		}
	}
	if (pro && (*SrcChess).proable)
	{
		(*SrcChess).setFace(Rfchess, (*SrcChess).id + 8);
		(*SrcChess).alreadyPro = true;
	}

	Lact.src = src;
	Lact.dst = dst;
	Lact.pro = pro;
	Lact.SrcChess = SrcChess;
	Lact.DstChess = DstChess;
	if (Mode == PlayervsAI)//P1 = 0 v AI1 = 2
		Turn ^= 2;
	else if (Mode == AIvsPlayer)//AI1 = 2 , P2 =1
		Turn = (Turn == AI1 ? AI1 : Player2);
	else if (Mode == PlayervsPlayer)//P1 = 0 , P2 = 1
		Turn = !Turn;
	else if (Mode == AIvsAI || Mode == AIvsOtherAI)//CPU1 v CPU2
		Turn = (Turn == AI1 ? AI1:AI2);

	src = 0;
	dst = 0;
	pro = false;
	HightLightOff();
}
bool GUI::isWin()
{
	if (win == 0)
	{
		EWwin.visible = true;
		return true;
	}
	else if (win == 1)
	{
		EBwin.visible = true;
		return true;
	}
	else
		return false;
}
void GUI::SetMovelist(int buf[], int getsize)
{
	movelistSize = getsize / sizeof(int);
	for (int i = 0; i < movelistSize; i++)
	{
		movelist[i] = (Move)buf[i];
		readablemovelist[i] = toreadablemove(movelist[i]);//*************************debug
	}
	cout << "\t[GUI]Movelist updated with size = " << movelistSize << endl;
}

//Edit
void GUI::ShowAllPos(bool on) {
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		Slot[i].visible = on;
	}
	for (int i = 0; i < PIECES_INGAME_AMOUNT; i++)
	{
		Piece[i].visible = on;
	}

}

//PV
Entity * GUI::FindPVChess(int square)
{
	for (int i = 0; i < 12; i++)
		if (PVPiece[i].square == square)
			return &PVPiece[i];

	return NULL;
}
void GUI::StorePV(int buf[], int getsize)//一直接收PV 就先存在NewPV之中 等到下次開啟SwitchPV時才更新到PV
{
	NewpvSize = getsize / sizeof(int);
	int i, k;
	for (i = 0, k = 0; k < NewpvSize; k++)
	{
		Square s = from_sq((Move)buf[k]);
		Square d = to_sq((Move)buf[k]);
		bool p = is_pro((Move)buf[k]);
		if ((s!=d) && d >= 0 && d < 35 && s >= 0 && s < 35 && buf[k] > 0)
		{
			NewPV[i] = (Move)buf[k];
			readablePVlist[i] = toreadablemove(NewPV[i]);
			i++;
			cout << "NewPV =  " <<to_string(s)<<" "<< to_string(d)<<" "<< to_string(p) <<" Stored" << endl;
		}
	}
	cout << endl;
	NewpvSize = i;
	cout << "\t[GUI]PV updated with size = " << NewpvSize << endl;
}
void GUI::UpdatePVnBoard() {//只有在打開SwitchPV的時候才會更新PVBoardStatus
	pv_i = 1;
	pvSize = NewpvSize;
	for (int i = 0; i < pvSize; i++)
	{
		PV[i] = NewPV[i];
	}
	for (int i = 0; i < PIECES_INGAME_AMOUNT; i++)//取得目前Piece的id、位置(sprite和sq)、是否可升變、是否已經升變
	{
		PVid[i] = Piece[i].id;
		PVPos[i] = Piece[i].getSprite().getPosition();
		PVsquare[i] = Piece[i].square;
		PVproable[i] = Piece[i].proable;
		PValreadyPro[i] = Piece[i].alreadyPro;

		PVPiece[i].setFace(PVRfchess, PVid[i]);
		PVPiece[i].setPos(PVPos[i]);
		PVPiece[i].square = PVsquare[i];
		PVPiece[i].proable = PVproable[i];
		PVPiece[i].alreadyPro = PValreadyPro[i];
	}
	for (int i = 0; i < BOARD_SIZE; i++)//設定PVboard狀態
	{
		ResetPVboardStatus[i] = boardStatus[i];
		PVboardStatus[i] = boardStatus[i];
	}
	for (int i = 0; i < 10; i++)//以PVBoard的25~34手牌數量
		handleft[i].setString(to_string(ResetPVboardStatus[i+25]));
	
	cout << "[SetPVBoard]PVBoard、PV has been updated" << endl;
}
void GUI::ResetPV()
{
	pv_i = 1;
	for (int i = 0; i < PIECES_INGAME_AMOUNT; i++)
	{
		PVPiece[i].setFace(PVRfchess, PVid[i]);
		PVPiece[i].setPos(PVPos[i]);
		PVPiece[i].square = PVsquare[i];
		PVPiece[i].proable = PVproable[i];
		PVPiece[i].alreadyPro = PValreadyPro[i];
	}
	for (int i = 0; i < BOARD_SIZE; i++)//設定PVboard狀態
	{
		PVboardStatus[i] = ResetPVboardStatus[i];
	}
	for (int i = 0; i < 10; i++)//以PVBoard的25~34手牌數量
	{
		handleft[i].setString(to_string(PVboardStatus[i + 25]));
	}
	cout << "[ResetPV]PV RESET" << endl;

}
void GUI::AIDoMove()
{
	int s = from_sq(NewPV[0]);
	int d = to_sq(NewPV[0]);
	bool p = is_pro(NewPV[0]);
	cout << "[AIDoMove]移動:" << chessname[Name2Index[(*FindChess(s)).id]] << ":(" << s << ")至(" << d << ") " <<(p?"升變":"")<< endl;
	DoMove(s, d, p);
}
void GUI::PV_DoMove()
{
	Square s = from_sq(PV[pv_i]);
	Square d = to_sq(PV[pv_i]);
	bool p = is_pro(PV[pv_i]);
	cout << "\t\t[PV DoMove] pv_i = " << pv_i << endl;

	//*********************************************************
	Entity *srcChess = FindPVChess(s);
	Entity *dstChess = FindPVChess(d);
	if (srcChess != NULL)
	{
		if (s > 24 && PVboardStatus[s] > 0)//Hand
		{
			(*srcChess).setPos(d, boardPos[d]);
			PVboardStatus[s]--;
			PVboardStatus[d] = (*srcChess).id;
			handleft[s - 25].setString(std::to_string(PVboardStatus[s]));;
			cout << "\t[DoMove]PV打入:" << chessname[Name2Index[(*srcChess).id]] << ":(" << s << ")至(" << d << ")" << endl;
		}
		else
		{
			if (PVboardStatus[d] == 0)//Move
			{
				(*srcChess).setPos(d, boardPos[d]);
				PVboardStatus[d] = PVboardStatus[s];
				PVboardStatus[s] = 0;
				cout << "\t[DoMove]PV移動:" << chessname[Name2Index[(*srcChess).id]] << ":(" << s << ")至(" << d << ")" << endl;
			}
			else if (PVboardStatus[d] > 0)//Eat
			{
				int sendpos = (*dstChess).id > 16 ? (*dstChess).id + 13 : (*dstChess).id + 24;
				(*srcChess).setPos(d, boardPos[d]);
				if ((*dstChess).alreadyPro)
				{
					(*dstChess).alreadyPro = false;
					(*dstChess).setFace(PVRfchess, (*dstChess).id - 8);
				}

				(*dstChess).setFace(PVRfchess, (*dstChess).id ^ 16);
				(*dstChess).setPos(sendpos, boardPos[sendpos]);
				PVboardStatus[d] = PVboardStatus[s];
				PVboardStatus[s] = 0;
				PVboardStatus[sendpos]++;
				handleft[sendpos - 25].setString(std::to_string(PVboardStatus[sendpos]));
				cout << "\t[DoMove]PV" << chessname[Name2Index[(*srcChess).id]] << "從(" << s << "(" << ":吃" << chessname[Name2Index[(*dstChess).id]] << "至(" << sendpos << ")" << endl;

			}
		}
	}
	else
	{
		cout << "\tSrcChess = NULL!!!!" << endl;
	}
	if (p && (*srcChess).proable)
	{
		(*srcChess).setFace(PVRfchess, (*srcChess).id + 8);
		(*srcChess).alreadyPro = true;
	}
	//TODO:PV棋子右邊顯示

	//*********************************************************
	if (pv_i < pvSize - 1)
	{
		pv_i++;
	}
	else
	{
		ResetPV();
		pv_i = 0;
	}
	t1 = clock();
}
void GUI::SwitchPV() {
	isPVon = !isPVon;
	if (isPVon)
	{
		UpdatePVnBoard();
	}
	if (!isPVon)
	{
		//UpdatePVAll
		//1. PV
		//2. PVBoardStatus
	}
	for (int i = 0; i < PIECES_INGAME_AMOUNT; i++)
	{
		PVPiece[i].visible = isPVon;
		Piece[i].visible = !isPVon;
	}
	for (int k = 0; k < 10; k++) 
	{
		if (isPVon)
			handleft[k].setString(std::to_string(PVboardStatus[k + 25]));
		else
			handleft[k].setString(std::to_string(boardStatus[k + 25]));;
	}
	t1 = clock();
	cout << "\t[SwitchPV]Turned " << (isPVon ? "on" : "off") << " PV display " << endl;
}


//View
void GUI::HightLightOff()
{
	for (int i = 0; i < 35; i++)
	{
		Slot[i].visible = false;
		//if (Slot[i].proable)Slot[i].setTexture("rect_b_g");
		Slot[i].proable = false;
	}
}
int GUI::HightLight()//依照當下的src去找
{
	int count = 0;
	cout << "\t[HightLight]" << chessname[Name2Index[(*FindChess(src)).id]] << "在" << src << "可以走:";
	NoWayToGo = true;
	Square psrc = SQ_A5, pdst = SQ_A5;
	for (int i = 0; i < movelistSize; i++)
	{
		Square s = from_sq((Move)movelist[i]);
		if (src == s)
		{
			NoWayToGo = false;
			if (i > 0)
			{
				psrc = from_sq(movelist[i - 1]);
				pdst = to_sq(movelist[i - 1]);
			}
			Square d = to_sq((Move)movelist[i]);
			if (s == psrc && d == pdst)//避免銀將有兩步 一步可以升變 下一步不行(Movelist中連續兩步) 而使得某一格Slot變成不能升變
			{
				continue;
			}
			Slot[d].proable = is_pro((Move)movelist[i]);
			Slot[d].visible = true;
			cout << d << " ";
		}
		count++;
	}
	cout << endl;
	return count;
}
void GUI::ResetMove()
{
	src = 0;
	dst = 0;
	pro = 0;
	isHold = 0;
	HightLightOff();
}
void GUI::ModeString()
{
	if (Mode >= 0)
		Turn_text.setString(TurnStr[Turn] + "\'s Turn");
	else if (EDIT_MODE && !hlon)
		Turn_text.setString("EDIT_MODE: Piece on " + to_string(Piece[movingpiece].getSprite().getPosition().x) + " " + to_string(Piece[movingpiece].getSprite().getPosition().y));
	else if (hlon)
		Turn_text.setString("EDIT_MODE: Highlight = " + to_string(Highlight) + " pos = " + to_string(Slot[Highlight].getSprite().getPosition().x) + ", " + to_string(Slot[Highlight].getSprite().getPosition().y));
	else if (DEBUG_MODE)
	{
		Turn_text.setString("DEBUG_MODE");
	}
	else
		Turn_text.setString("Not Started");
}
string GUI::toreadablemove(Move a)
{
	return to_string(from_sq(a)) + " " + to_string(to_sq(a)) + " "+to_string(is_pro(a));
}
void GUI::EnableGUI()
{
	sf::RenderWindow window(sf::VideoMode(780,780), "Minishogi");
	sf::Image image;
	image.loadFromFile("images/prorook.png");
	window.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());
	float unit = 2.0f;
	isEnable = true;

	while (window.isOpen())
	{
		ModeString();
		sf::Event event;
		if (window.waitEvent(event)||RefreshScreen)
		{
			sf::Event::EventType t = event.type;
			sf::Event::KeyEvent k = event.key;
			if (t == sf::Event::Closed)
				window.close();
			sf::Vector2i MousePos = sf::Mouse::getPosition(window);

			//按下功能按鈕
			if (t == sf::Event::MouseButtonPressed) 
			{
				int color;
				if (isWin())
				{
					color = win;
					cout <<"[WIIIIIIIIIIIIIIIIN]"<< color << endl;

					if ((EBwin.visible && EBwin.isContaining(MousePos)) || (EWwin.visible && EWwin.isContaining(MousePos)))
					{
						win = NOONEWIN;
						SetBoard();
						cout << "[Clicked on win]Game Reset" << endl;
					}
				}
				else if (Mode == AIvsAI && EShowPV.isContaining(MousePos))
					SwitchPV();
			}

			if (EDIT_MODE)
			{
				if (t == sf::Event::KeyPressed)
				{
					if (k.code == sf::Keyboard::P)
					{
						Piece[movingpiece].setFace(Rfchess, Piece[movingpiece].id ^ 16);
					}
					else if (k.code >= 75 && k.code <= 77)
					{
						movingpiece = k.code - 65;
						cout << "movingpiece = " << movingpiece << endl;
					}
					else if (k.code >= 26 && k.code <= 35)
					{
						movingpiece = k.code - 26;
						cout << "movingpiece = " << movingpiece << endl;
					}
					else if (k.code == sf::Keyboard::Z)
					{
						ShowAllPos(true);
					}
					else if (k.code == sf::Keyboard::X)
					{
						ShowAllPos(false);
					}
					else if (k.code == sf::Keyboard::A)
					{
						Slot[Highlight].visible = true;
						hlon = true;
					}
					else if (k.code == sf::Keyboard::S)
					{
						Slot[Highlight].visible = false;
						hlon = false;
					}
					else if (k.code == sf::Keyboard::C)
					{
						if (Highlight > 0)Highlight--;
					}
					else if (k.code == sf::Keyboard::V)
					{
						if (Highlight < 34)Highlight++;
					}
					else if (k.code == sf::Keyboard::B)
					{
						unit--;
					}
					else if (k.code == sf::Keyboard::N)
					{
						unit++;
					}
					else
					{
						sf::Vector2f ScurrentPos = Slot[Highlight].getSprite().getPosition();
						sf::Vector2f PcurrentPos = Piece[movingpiece].getSprite().getPosition();
						if (k.code == sf::Keyboard::Up)
						{
							if (hlon)Slot[Highlight].setPos(sf::Vector2f(ScurrentPos.x, ScurrentPos.y - unit));
							else Piece[movingpiece].setPos(sf::Vector2f(PcurrentPos.x, PcurrentPos.y - unit));
						}
						if (k.code == sf::Keyboard::Down)
						{
							if (hlon)Slot[Highlight].setPos(sf::Vector2f(ScurrentPos.x, ScurrentPos.y + unit));
							else Piece[movingpiece].setPos(sf::Vector2f(PcurrentPos.x, PcurrentPos.y + unit));
						}
						if (k.code == sf::Keyboard::Left)
						{
							if (hlon)Slot[Highlight].setPos(sf::Vector2f(ScurrentPos.x - unit, ScurrentPos.y));
							else Piece[movingpiece].setPos(sf::Vector2f(PcurrentPos.x - unit, PcurrentPos.y));
						}
						if (k.code == sf::Keyboard::Right)
						{
							if (hlon)Slot[Highlight].setPos(sf::Vector2f(ScurrentPos.x + unit, ScurrentPos.y));
							else Piece[movingpiece].setPos(sf::Vector2f(PcurrentPos.x + unit, PcurrentPos.y));
						}
					}

				}
			}
			else if (DEBUG_MODE || Mode >= 0 && (Turn == Player1 || Turn == Player2) &&win == NOONEWIN)
			{
				MousePos = sf::Mouse::getPosition(window);
				if (t == sf::Event::MouseButtonPressed) // 1 Mouse Click
				{
					if (k.code == sf::Mouse::Right)
						ResetMove();
					else if (k.code == sf::Mouse::Left)
					{
						switch (Scene) {
						case Main:
							if (EButton1.isContaining(MousePos))
								Scene = Ingame;
							break;
						case Ingame:
							if (isAskPro) //詢問可升變者
							{
								if (EYes.isContaining(MousePos))
									pro = true;
								else if (ENo.isContaining(MousePos))
									pro = false;

								isAskPro = false;
								isHold = false;
								int send[2];
								send[0] = 2;
								send[1] = make_move((Square)src, (Square)dst, pro);
								fm_gm.SendMsg(send, sizeof(send), false);
								DoMove(src, dst, pro);
							}
							else if (!isPVon) //點按棋子
							{
								for (int i = 0; i < 35; i++)
								{
									if (Slot[i].getSprite().getGlobalBounds().contains(MousePos.x, MousePos.y))
									{
										Entity *Chess = FindChess(i);
										if (boardStatus[i] && Chess != NULL) {//有按到棋子
											if (isHold && (DEBUG_MODE || Slot[i].visible)) {//已經選過棋且該位置可以按
												dst = i;
												if (src == dst)continue;
												isHold = false;
												if (Slot[i].proable)
													isAskPro = true;
												else {//不能升變的 即直接Domove 不須詢問
													int send[2];
													send[0] = 2;//在testFileMapping = Ack
													send[1] = make_move((Square)src, (Square)dst, pro);
													fm_gm.SendMsg(send, sizeof(send), false);
													DoMove(src, dst, pro);
												}
											}
											else if ((((*Chess).id & 16) > 0) == Turn)//未選棋，此時先選到自己的棋0 1 2 3
											{
												src = i;
												HightLight();
												if (!NoWayToGo || DEBUG_MODE)
													isHold = true;

												cout << "[Clicked on chess]" << (!DEBUG_MODE&&NoWayToGo  ? " ***但它沒地方走!!!!!!!!!" : "") << endl;
											}
										}
										else if (boardStatus[i] == 0 && Chess == NULL)
										{
											if (isHold && (DEBUG_MODE || Slot[i].visible))
											{
												dst = i;
												if (src == dst)continue;
												isHold = false;
												if (Slot[i].proable)
													isAskPro = true;
												else //不能升變的 即直接Domove 不須詢問
												{
													int send[2];
													send[0] = 2;//在testFileMapping = Ack
													send[1] = make_move((Square)src, (Square)dst, pro);
													fm_gm.SendMsg(send, sizeof(send), false);
													DoMove(src, dst, pro);
												}
											}
										}
									}
								}
							}
							break;
						}
					}//End 按下左鍵
				}//End 按下滑鼠
				else if (!isPVon&&win == NOONEWIN)// 滑鼠懸浮
				{
					for (int i = 0; i < 35; i++)
					{
						Entity *Chess = FindChess(i);
						if (!isHold&&Chess != NULL && (((*Chess).id & 16) > 0) == Turn && Slot[i].isContaining(MousePos))
						{
							SlotHover[i].visible = true;
						}
						else
							SlotHover[i].visible = false;
					}
					if (Mode == AIvsAI &&EShowPV.isContaining(MousePos)) {
						//TODO!!!!!
					}
				}// End 滑鼠懸浮

			}
		}
		window.clear();
		window.draw(EBackground.getSprite());
		switch (Scene)
		{
		case Main:
			window.draw(ETitle.getSprite());
			window.draw(EButton1.getSprite());
			window.draw(EButton2.getSprite());
			break;
		case Ingame:
			window.draw(EBoard.getSprite());
			window.draw(Turn_text);

			//Green Slots and Grey SlotHover
			for(int i =0;i<35;i++)
					if (Slot[i].visible) 
						window.draw(Slot[i].getSprite());
					else if(SlotHover[i].visible)
						window.draw(SlotHover[i].getSprite());
				//handleft # text
				for (int i = 0; i < 10; i++)
					if(handleft[i].getString() != "0")window.draw(handleft[i]);
			//Pieces
				if (isPVon)
				{
					t2 = clock();
					double tp = (double)((t2 - t1) / (double)(CLOCKS_PER_SEC));
					if (tp>= PVSPEED)
						PV_DoMove();
					for (int i = 0; i < 12; i++)if (PVPiece[i].id > 0)
						window.draw(PVPiece[i].getSprite());
				}
				else
					for (int i = 0; i < 12; i++)if (Piece[i].id>0)
						window.draw(Piece[i].getSprite());
			
			//Check reference pieces' faces
				//for (int i = 0; i < 20; i++)if (Rfchess[i].visible)window.draw(Rfchess[i].getSprite());
			//Check PV reference pieces' faces
				//for (int i = 0; i < 20; i++)if (PVRfchess[i].visible)window.draw(PVRfchess[i].getSprite());
			
			//Pro window
				if (isAskPro)
				{
					window.draw(EAskPro.getSprite());
					window.draw(EYes.getSprite());
					window.draw(ENo.getSprite());
				}
			
				if (DEBUG_MODE||Mode == AIvsAI)
				{
					window.draw(EShowPV.getSprite());
				}
				if (DEBUG_MODE||Mode>0)
				{
					window.draw(EGiveUp.getSprite());
					window.draw(EUndoMove.getSprite());
				}
			//Win 
				if (isWin())
					window.draw(win == WHITEWIN?EWwin.getSprite():EBwin.getSprite());
			

			break;

		}

		window.display();
	}

}


