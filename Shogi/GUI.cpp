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

wchar_t *convertCharArrayToLPCWSTR(const char* charArray)
{
	wchar_t* wString = new wchar_t[4096];
	MultiByteToWideChar(CP_ACP, 0, charArray, -1, wString, 4096);
	return wString;
}
void GUI::LoadTexture()
{
	EBackground.setTexture("Background");
	ETitle.setTexture("Title");
	EPKPlayer.setTexture("ButtonPvP");
	EPKAI_P.setTexture("ButtonPvA");
	EPKAI_A.setTexture("ButtonAvP");
	EAIPKAI.setTexture("ButtonAvA");
	EBoard.setTexture("Board_new");
	EAskPro.setTexture("Pro");
	EYes.setTexture("Yes");
	ENo.setTexture("No");
	EWwin.setTexture("Wwin_F");
	EBwin.setTexture("Bwin_F");
	EShowPV.setTexture("Button_ShowPV");
	EGiveUp.setTexture("Button_GiveUp");
	EUndoMove.setTexture("Button_UndoMove");
	SlotDST.setTexture("rect_b_bl50");
	EToLobby.setTexture("ButtonToLobby");
	EArrow.setTexture("arrow");
}
void GUI::LoadSound()
{
	soundbuf_SMove;
	if (!soundbuf_SMove.loadFromFile("sounds/move.wav")) {
		cout << "Can't Play sound :" << "sounds/move.wav" << endl;
		return;
	}
	SMove.setBuffer(soundbuf_SMove);
}
void GUI::InitEnvironment()
{
	ETitle.setPos(171.0f, 40.0f);
	EPKAI_P.setPos(288.0f, 281.0f);
	EPKAI_A.setPos(288.0f, 381.0f);
	EPKPlayer.setPos(288.0f, 481.0f);
	EAIPKAI.setPos(288.0f, 581.0f);
	EBoard.setPos(0.0f, 0.0f);
	EArrow.setPos(450.0f, 50.0f);
	srand(time(NULL));
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
	SlotDST.visible = false;
	Turn_text.setFont(font);
	Turn_text.setColor(sf::Color::Black);
	Turn_text.setCharacterSize(TURNSTR_FONTSIZE);
	Turn_text.setPosition(0.0f, 0.0f);

	EAskPro.setPos(200.0f, 170.0f);
	EYes.setPos(230.0f, 300.0f);
	ENo.setPos(420.0f, 300.0f);
	//EWwin.setPos(200.0f, 170.0f);
	//EBwin.setPos(200.0f, 170.0f);
	EToLobby.setPos(560.0f,50.0f);
	EShowPV.setPos(560.0f,120.0f);//160 + 90
	EGiveUp.setPos(560.0f,210.0f);
	EUndoMove.setPos(560.0f,300.0f);

	Turn = -1;
	Mode = -1;
	isAskPro = false;

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
	isOpen = true;
}
GUI::GUI() {
	GotStuff = false;
	src = 0;
	dst = 0;
	isHold = false;
	if (!font.loadFromFile("�δ���W5.TTC"))
		std::cout << "Can't load font" << std::endl;

	LoadTexture();
	LoadSound();
	InitEnvironment();
	//fm_gm.Open("GUI_gm");
	//fm_mg.Open("GUI_mg");
}
bool GUI::SetBoard(std::string init)
{
	if (NEEDSCRSHOT) {
		roundseed = rand() % 666;
		fdrpath = string(__DATE__);
		fdrpath.append(("_" + to_string(roundseed)).c_str());
		if (CreateDirectory(convertCharArrayToLPCWSTR(fdrpath.c_str()), NULL) ||
			ERROR_ALREADY_EXISTS == GetLastError())
		{
			cout << "[SetBoard]Screenshot Folder\"" << fdrpath << "\" created" << endl;
		}
		else
		{
			cout << "[SetBoard]Failed to create directory" << fdrpath << "." << endl;
		}
	}
	for (int i = 0; i < BOARD_SIZE; i++)
			boardStatus[i] = 0;
	
	int appearance[] = { 2,2,2,2,2,2 };//�C�@�ӴѤl�̦h2��
	stringstream ss(init);
	string token = "";
	int square = 0;//Board count �q 0 ~ 34
	int count = 0;//Max amount of chess on the go �q 0 ~ 12
	while (getline(ss, token, ' '))
	{
		int chessvalue = atoi(token.c_str());
		int chess = 0;
		if (Name2Index[chessvalue] == -1)//�Q�δѤlid�i�H������@��texture�ӧP�_�O���O�s�b���Ѥl e.g.�p�GName2Index[20] = -1�S���o�ӴѤl
		{
			cout << "[ERROR]��l�ƽL�����ѡG�L�ĴѤl = " << chessvalue << endl;
			return false;
		}
		else if (chessvalue > 0)
		{
			//��P��or�ѽL�W
			if (square > 24)
			{
				chess = square < 29 ? square - 8 : square - 29;//�ݵ��O��ӽL��
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
			
			
		/*	cout << chessname[Name2Index[Piece[count].id]]<<" id = "<< Piece[count].id <<"�ѦҦ�"<<Rfchess[count].id  << endl;
			cout << chessname[Name2Index[Piece[count].id]]<<(Piece[count].proable?"�i�H":"����")<<"����" << endl;*/
			//�ˬd�L�ؼƶq
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
					cout << "[ERROR]�L�ؼƶq����" << endl;
					return false;
				}

			count++;
		}
		square++;
	}

	for (int i = 0; i < 10; i++)//�HPVBoard��25~34��P�ƶq
		handleft[i].setString(to_string(boardStatus[i + 25]));
	src = 0;
	dst = 0;
	pro = false;
	isHold = false;
	movecount = 0;
	SlotDST.visible = false;
	movefinished = false;
	if (win >= 0)
		if (Mode == PlayervsAI)//P1 = 0 v AI1 = 2
			Turn ^= 2;
		else if (Mode == AIvsPlayer)//AI1 = 2 , P2 =1
			Turn = (Turn == AI1 ? Player2 : AI1);
		else if (Mode == PlayervsPlayer)//P1 = 0 , P2 = 1
			Turn = !Turn;
		else if (Mode == AIvsAI || Mode == AIvsOtherAI)//CPU1 v CPU2
			Turn = (Turn == AI1 ? AI2 : AI1);
	movefinished = true;//�@�}�l��@�i
	cout << "[SetBoard]Board initialized " << endl;
}
void GUI::SetCustomBoard() {
	bool ok = false;
	char initboard[256];
	do
	{
		cout << "[SetCustomBoard]�п�J�ѽL �@35�� (e.g \"21 20 18 19 22 0 0 0 0 17 0 0 0 0 0 1 0 0 0 0 6 3 2 4 5 0 0 0 0 0 0 0 0 0 0\")";
		cin.getline(initboard, 256);

		if (initboard[0] == '-') {
			cout << "[SetCustomBoard]�����]�w�L��" << endl;
			break;
		}
		cout << initboard << endl;
		ok = SetBoard(initboard);
		if (!ok)cout << "[SetCustomBoard]�榡���~! �ο�J \"-\"�H�h�X�]�w " << endl;
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
			boardStatus[src] = (*SrcChess).id;//����boardStatus[dst] �O�]����������
			boardStatus[dst] = (*DstChess).id;
			
		}
	}
	Turn = !Turn;

}
void GUI::GUIDoMove(bool isSurrender) {
	int send[2];
	send[0] = DOMOVE;//�btestFileMapping = Ack
	send[1] = isSurrender?MOVE_NULL:make_move((Square)src, (Square)dst, pro);
	fm_gm.SendMsg(send, sizeof(send), true);
	if (isSurrender)
	{
		if (Turn == Player1 || Turn == AI1)
			win = 1;
		else if (Turn == Player2 || Turn == AI2)
			win = 0;
	}
	else 
		DoMove(src, dst, pro);
}
void GUI::DoMove(int s, int d, bool p) {
	Entity *SrcChess = FindChess(s);
	Entity *DstChess = FindChess(d);
	if (SrcChess != NULL)
	{
		if (s > 24 && boardStatus[s] > 0)//Hand
		{
			(*SrcChess).setPos(d, boardPos[d]);
			boardStatus[s]--;
			boardStatus[d] = (*SrcChess).id;
			handleft[s - 25].setString(std::to_string(boardStatus[s]));;
			cout << "\t[DoMove]���J:" << chessname[Name2Index[(*SrcChess).id]] << ":(" << s << ")��(" << d << ")" << endl;
		}
		else
		{
			if (boardStatus[d] == 0)//Move
			{
				(*SrcChess).setPos(d, boardPos[d]);
				boardStatus[d] = boardStatus[s];
				boardStatus[s] = 0;
				cout << "\t[DoMove]����:" << chessname[Name2Index[(*SrcChess).id]] << ":(" << s << ")��(" << d << ")" << endl;
			}
			else if (boardStatus[d] > 0)//Eat
			{
				if ((*DstChess).id == 6)
					win = 1;
				else if ((*DstChess).id == 22)
					win = 0;
				else
				{
					(*SrcChess).setPos(d, boardPos[d]);
					if ((*DstChess).alreadyPro)
					{
						(*DstChess).alreadyPro = false;
						(*DstChess).setFace(Rfchess, (*DstChess).id - 8);
					}
					int sendpos = (*DstChess).id > 16 ? (*DstChess).id + 13 : (*DstChess).id + 24;//����u�A�Ω�¥ե����ܪ��Ѥl
					(*DstChess).setFace(Rfchess, (*DstChess).id ^ 16);
					(*DstChess).setPos(sendpos, boardPos[sendpos]);
					boardStatus[d] = boardStatus[s];
					boardStatus[s] = 0;
					boardStatus[sendpos]++;
					handleft[sendpos - 25].setString(std::to_string(boardStatus[sendpos]));
					cout << "\t[DoMove]" << chessname[Name2Index[(*SrcChess).id]] << "�q(" << s << "(" << ":�Y" << chessname[Name2Index[(*DstChess).id]] << "��(" << sendpos << ")" << endl;
				}

			}
		}
	}
	if (p && (*SrcChess).proable)
	{
		cout << "\t[DoMove]" << chessname[Name2Index[(*SrcChess).id]] << "���ܦ�";
		(*SrcChess).setFace(Rfchess, (*SrcChess).id + 8);
		(*SrcChess).alreadyPro = true;
		cout << chessname[Name2Index[(*SrcChess).id]]<<", id = "<< (*SrcChess).id << endl;

	}

	Lact.src = s;
	Lact.dst = d;
	Lact.pro = p;
	Lact.SrcChess = SrcChess;
	Lact.DstChess = DstChess;
	if (Mode == PlayervsAI)//P1 = 0 v AI1 = 2
		Turn ^= 2;
	else if (Mode == AIvsPlayer)//AI1 = 2 , P2 =1
		Turn = (Turn == AI1 ? Player2 :AI1 );
	else if (Mode == PlayervsPlayer)//P1 = 0 , P2 = 1
		Turn = !Turn;
	else if (Mode == AIvsAI || Mode == AIvsOtherAI)//CPU1 v CPU2
		Turn = (Turn == AI1 ? AI2:AI1);

	SlotDST.setPos(dst,Slot[d].getSprite().getPosition());
	SlotDST.visible = true;
	src = 0;
	dst = 0;
	pro = false;
	if(!DEBUG_MODE)HightLightOff();
	movecount++;
	movefinished = true;
	SMove.play();
}
void GUI::SetMovelist(int buf[], int getsize)
{
	movelistSize = getsize / sizeof(int);
	for (int i = 0; i < movelistSize; i++)
	{
		movelist[i] = (Move)buf[i];
		readablemovelist[i] = toreadablemove(movelist[i]);//*************************debug
		Entity *Chess = FindChess(from_sq(movelist[i]));
		//cout << "\t\tMovelist["<<i<<"] "<<((*Chess).id>16?"b":"w")<< chessname[Name2Index[(*Chess).id]] <<"("<<from_sq(movelist[i])<<") To "<<to_sq(movelist[i])<<" "<<(is_pro(movelist[i]) ?"true":"false") << endl;//DEBUG
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
void GUI::StorePV(int buf[], int getsize)//�@������PV �N���s�bNewPV���� ����U���}��SwitchPV�ɤ~��s��PV
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
			//cout << "\t\tNewPV =  " <<to_string(s)<<" "<< to_string(d)<<" "<< to_string(p) <<" Stored" << endl;
		}
	}
	NewpvSize = i;
	cout << "\t[GUI]PV updated with size = " << NewpvSize << endl;
}
void GUI::UpdatePVnBoard() {//�u���b���}SwitchPV���ɭԤ~�|��sPVBoardStatus
	pv_i = 1;
	pvSize = NewpvSize;
	for (int i = 0; i < pvSize; i++)
	{
		PV[i] = NewPV[i];
	}
	for (int i = 0; i < PIECES_INGAME_AMOUNT; i++)//���o�ثePiece��id�B��m(sprite�Msq)�B�O�_�i���ܡB�O�_�w�g����
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
	for (int i = 0; i < BOARD_SIZE; i++)//�]�wPVboard���A
	{
		ResetPVboardStatus[i] = boardStatus[i];
		PVboardStatus[i] = boardStatus[i];
	}
	for (int i = 0; i < 10; i++)//�HPVBoard��25~34��P�ƶq
		handleft[i].setString(to_string(ResetPVboardStatus[i+25]));
	
	cout << "[SetPVBoard]PVBoard�BPV has been updated" << endl;
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
	for (int i = 0; i < BOARD_SIZE; i++)//�]�wPVboard���A
	{
		PVboardStatus[i] = ResetPVboardStatus[i];
	}
	for (int i = 0; i < 10; i++)//�HPVBoard��25~34��P�ƶq
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
	cout << "\t[AIDoMove]����:" << chessname[Name2Index[(*FindChess(s)).id]] << ":(" << s << ")��(" << d << ") " <<(p?"����":"")<< endl;
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
			cout << "\t[DoMove]PV���J:" << chessname[Name2Index[(*srcChess).id]] << ":(" << s << ")��(" << d << ")" << endl;
		}
		else
		{
			if (PVboardStatus[d] == 0)//Move
			{
				(*srcChess).setPos(d, boardPos[d]);
				PVboardStatus[d] = PVboardStatus[s];
				PVboardStatus[s] = 0;
				cout << "\t[DoMove]PV����:" << chessname[Name2Index[(*srcChess).id]] << ":(" << s << ")��(" << d << ")" << endl;
			}
			else if (PVboardStatus[d] > 0)//Eat
			{
				(*srcChess).setPos(d, boardPos[d]);
				if ((*dstChess).alreadyPro)
				{
					(*dstChess).alreadyPro = false;
					(*dstChess).setFace(PVRfchess, (*dstChess).id - 8);
				}
				int sendpos = (*dstChess).id > 16 ? (*dstChess).id + 13 : (*dstChess).id + 24;

				(*dstChess).setFace(PVRfchess, (*dstChess).id ^ 16);
				(*dstChess).setPos(sendpos, boardPos[sendpos]);
				PVboardStatus[d] = PVboardStatus[s];
				PVboardStatus[s] = 0;
				PVboardStatus[sendpos]++;
				handleft[sendpos - 25].setString(std::to_string(PVboardStatus[sendpos]));
				cout << "\t[DoMove]PV" << chessname[Name2Index[(*srcChess).id]] << "�q(" << s << "(" << ":�Y" << chessname[Name2Index[(*dstChess).id]] << "��(" << sendpos << ")" << endl;

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
	//TODO:PV�Ѥl�k�����

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
int GUI::HightLight()//�̷ӷ�U��src�h��
{
	HightLightOff();
	SlotDST.visible = false;
	int count = 0;
	cout << "\t[HightLight]" << chessname[Name2Index[(*FindChess(src)).id]] << "�b" << src << "�i�H��:";
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
			if (s == psrc && d == pdst)//�קK�ȱN����B �@�B�i�H���� �U�@�B����(Movelist���s���B) �Өϱo�Y�@��Slot�ܦ��������
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
	if(movecount>0)SlotDST.visible = true;
	src = 0;
	dst = 0;
	pro = 0;
	isHold = 0;
	HightLightOff();
	cout << "[ResetMove]src = " << src << "dst = " << dst << "pro = " << (pro ? "true" : "false") << " HightlightOFF," << "isHold = " << (isHold?"true": "false") << endl;
}
void GUI::ModeString()
{
	if (Mode >= 0)
		Turn_text.setString(TurnStr[Turn] + "\'s Turn");
	else
		Turn_text.setString("Not Started");
}
string GUI::GetModeName() {
	if (Mode >= PlayervsAI)
		return modename[Mode];
	else
		return "[GetModeName]Not Started!";
}
string GUI::toreadablemove(Move a)
{
	return to_string(from_sq(a)) + " " + to_string(to_sq(a)) + " "+to_string(is_pro(a));
}
void GUI::SetFM(char *argv)
{
	cout << ("fm_gm_" + string(argv)) << endl;
	fm_gm.Open("fm_gm_"+string(argv));
	fm_mg.Open("fm_mg_"+string(argv));
}
void GUI::StartGame(int mode)
{
	win = NOONEWIN;
	int buf[1];
	isGameSet = true;
	buf[0] = GAMEMODE;
	fm_gm.SendMsg(buf, sizeof(int), true);
	buf[0] = mode;
	fm_gm.SendMsg(buf, sizeof(int), true);
	while (gamemodebuf[0] != ACK);

	if (mode >= PlayervsAI && mode <= AIvsOtherAI)
		{
			Mode = mode;
			Scene = Ingame;
			isGameOver = false;
			isGameSet = true;
			SetBoard();
			switch (mode)
			{
			case PlayervsAI:
				Turn = Player1;
				break;
			case AIvsPlayer:
				Turn = AI1;
				UpdatePVnBoard();
				break;
			case PlayervsPlayer:
				Turn = Player1;
				break;
			case AIvsAI:
				Turn = AI1;
				UpdatePVnBoard();
				break;
			case AIvsOtherAI:
				Turn = AI1;
				UpdatePVnBoard();
				break;
			default:
				cout << "[Mode]ERROR" << endl;
				break;
			}

			cout << "[StartGame]GameStarted with mode[" << modename[Mode] << "]" << endl;
		}

}
void GUI::EnableGUI()
{
	sf::RenderWindow window(sf::VideoMode(780,780), "Minishogi");
	sf::Image image;
	image.loadFromFile("images/prorook.png");
	window.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());
	float unit = 2.0f;
	sf::Event event;
	sf::Event::EventType t;
	sf::Event::KeyEvent k;
	sf::Vector2i MousePos;
	while (window.isOpen())
	{
		ModeString();	
		if (window.pollEvent(event))//���ƹ��ʧ@
		{	
			t = event.type;
			k = event.key;
			if (t == sf::Event::Closed)
				window.close();
			MousePos = sf::Mouse::getPosition(window);
			//Switch Scene
			switch (Scene)
			{
				
			case Lobby:
				if (t == sf::Event::MouseButtonPressed)
				{
					if (EPKAI_A.isContaining(MousePos))
					{
						StartGame(AIvsPlayer);
					}
					if (EPKAI_P.isContaining(MousePos)) {
						StartGame(PlayervsAI);
					}
					else if (EPKPlayer.isContaining(MousePos))
					{
						StartGame(PlayervsPlayer);
					}
					else if (EAIPKAI.isContaining(MousePos))
					{
						StartGame(AIvsAI);
					}
				}
				else // Hovering in lobby
				{
						EPKAI_A.setTexture(EPKAI_A.isContaining(MousePos)?"ButtonAvPH": "ButtonAvP");
						EPKAI_P.setTexture(EPKAI_P.isContaining(MousePos)?"ButtonPvAH":"ButtonPvA");
						EPKPlayer.setTexture(EPKPlayer.isContaining(MousePos)?"ButtonPvPH": "ButtonPvP");
						EAIPKAI.setTexture(EAIPKAI.isContaining(MousePos)?"ButtonAvAH": "ButtonAvA");
				}
				break;
			case Ingame:			
					//���U�\����s
					if (t == sf::Event::MouseButtonPressed)//�o�䦳���I�����a�B �n�S�O����
					{
						int color;
						if (win >= 0)
						{
							color = win;
							cout << "[GUI]win :" << (color ? "BLACK" : "WHITE") << endl;
							//Ĺ�F�åB�I�@�U�e��
							if (EBwin.isContaining(MousePos) ||  EWwin.isContaining(MousePos))
							{
								isGameOver = true;
								win = NOONEWIN;
							}
						}
						else if (Mode != PlayervsPlayer &&(movecount>1)&& EShowPV.isContaining(MousePos))
							SwitchPV();
						else if (Mode!=AIvsAI &&(Turn == Player1||Turn == Player2)&& EGiveUp.isContaining(MousePos)&&!isGameOver)
						{
							cout << "[GUI]�뭰" << endl;
							isGameOver = true;
							GUIDoMove(true);
						}
						else if (EToLobby.isContaining(MousePos))
						{
							gamemodebuf[0] = -1;
							win = NOONEWIN;
							Scene = Lobby;
							int send[1];
							if (!isGameOver) {
								send[0] = BREAK;
								fm_gm.SendMsg(send, sizeof(int), true);
							}
							isGameSet = false;
							isGameOver = true;
							send[0] = RESTART;
							fm_gm.SendMsg(send, sizeof(int), true);
							cout << "[GUI]Game Reset" << endl;
						}
					}
					
					//�I�Ѥl
					if (DEBUG_MODE || !isGameOver&& Mode >= 0 && (Turn == Player1 || Turn == Player2) && win == NOONEWIN)
					{
						MousePos = sf::Mouse::getPosition(window);
						// ���U�ƹ�
						if (t == sf::Event::MouseButtonPressed)
						{
							//�k�䭫�s���
							if (k.code == sf::Mouse::Right)
								ResetMove();
							//���U����
							else if (k.code == sf::Mouse::Left)
							{
								//�߰ݥi���ܪ�
								if (isAskPro)
								{
									if (EYes.isContaining(MousePos))
									{
										pro = true; 
										isAskPro = false;
										isHold = false;
										GUIDoMove(false);
									}
									else if (ENo.isContaining(MousePos))
									{
										pro = false;
										isAskPro = false;
										isHold = false;
										GUIDoMove(false);
									}
								}
								//�I���Ѥl
								else if (!isPVon)
								{
									for (int i = 0; i < 35; i++)
									{
										if (Slot[i].getSprite().getGlobalBounds().contains(MousePos.x, MousePos.y))
										{
											Entity *Chess = FindChess(i);
											if (boardStatus[i] && Chess != NULL) {//������Ѥl
												if (isHold && (DEBUG_MODE || Slot[i].visible)) {//�w�g��L�ѥB�Ӧ�m�i�H��

													dst = i;
													if (src == dst)continue;
													isHold = false;
													if (Slot[i].proable)
													{
														int srcchessid = (*FindChess(src)).id;
														bool isPawn = srcchessid == 1 || srcchessid == 17;
														if (isPawn)//���H��ڻ��B�L�i�H�����ɯũO�Ať�_�ӯu��
														{
															pro = true;
															GUIDoMove(false);
														}
														else
														{
															isAskPro = true;
														}
													}
													else {//������ܪ� �Y����Domove �ڬOı�o���θ߰ݤF��
														GUIDoMove(false);
													}
												}
												else if ((((*Chess).id & 16) > 0) == Turn)//����ѡA���ɥ����ۤv����
												{
													src = i;
													if (DEBUG_MODE)
													{
														isHold = true;
														cout << "[Debug-GUI]Picked Chess:"<< (*Chess).id <<endl;
													}
													else
													{
														HightLight();
														if (!NoWayToGo)
															isHold = true;
														cout << "\t[Clicked]On " << ((*Chess).id > 16 ? "b" : "w") << chessname[Name2Index[(*Chess).id]] << (!DEBUG_MODE&&NoWayToGo ? " ***�����S�a�訫!!!!!!!!!" : "");

													}
													
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
													{
														int srcchessid = (*FindChess(src)).id;
														bool isPawn = srcchessid == 1 || srcchessid == 17;
														if (isPawn)//���H��ڻ��B�L�n�����ɯũO�Ať�_�ӯu��
														{
															pro = true;
															//cout << "�B�������� src ="<<src<<"dst = "<<dst<<"pro =" <<pro << endl;
															GUIDoMove(false);
														}
														else
														{
															isAskPro = true;
														}

													}
													else //������ܪ� �Y����Domove �����߰�
													{
														GUIDoMove(false);
													}
												}
											}
										}
									}
								}

							}//End ���U����
						}//End ���U�ƹ�
						 // �ѽL���ƹ��a�B
						else if (!isPVon&&win == NOONEWIN)
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

						}// End �ѽL���ƹ��a�B

					}

					//�ѽL�~�a�B
					if (Mode != PlayervsPlayer)EShowPV.setTexture(EShowPV.isContaining(MousePos) ? "Button_ShowPVH50" : "Button_ShowPV");
					if (!isGameOver &&Mode != AIvsAI)EGiveUp.setTexture(EGiveUp.isContaining(MousePos) ? "Button_GiveUpH50" : "Button_GiveUp");
					if (Mode != AIvsAI && (Turn == Player1 || Turn == Player2))EToLobby.setTexture(EToLobby.isContaining(MousePos)?"ButtonTOLobbyH":"ButtonTOLobby");
					//if (Mode != AIvsAI)EUndoMove.setTexture(EUndoMove.isContaining(MousePos) ? "Button_UndoMoveH50" : "Button_UndoMove");
				
				break;
			}
			//End Switch Scene

			
		}
		//************************************************************************
		//DRAW
		window.draw(EBackground.getSprite());
		switch (Scene)
		{
		case Lobby:
			window.draw(ETitle.getSprite());
			window.draw(EPKPlayer.getSprite());
			window.draw(EPKAI_P.getSprite());
			window.draw(EAIPKAI.getSprite());
			window.draw(EPKAI_A.getSprite());
			break;
		case Ingame:
			window.draw(EBoard.getSprite());
			window.draw(Turn_text);
			if(Mode!=AIvsAI && (Turn==Player1||Turn==Player2))window.draw(EToLobby.getSprite());
			//Green Slots and Grey SlotHover
			for (int i = 0; i < 35; i++)
				if (Slot[i].visible)
					window.draw(Slot[i].getSprite());
				else if (SlotHover[i].visible)
					window.draw(SlotHover[i].getSprite());
			//handleft # text
			for (int i = 0; i < 10; i++)
				if (handleft[i].getString() != "0")window.draw(handleft[i]);
			//DST	
			if (SlotDST.visible)window.draw(SlotDST.getSprite());

			//Pieces
			if (isPVon)
			{
				t2 = clock();
				double tp = (double)((t2 - t1) / (double)(CLOCKS_PER_SEC));
				if (tp >= PVSPEED)
					PV_DoMove();
				for (int i = 0; i < 12; i++)if (PVPiece[i].id > 0)
					window.draw(PVPiece[i].getSprite());
			}
			else
				for (int i = 0; i < 12; i++)if (Piece[i].id > 0)
					window.draw(Piece[i].getSprite());

			//Pro window
			if (isAskPro)
			{
				window.draw(EAskPro.getSprite());
				window.draw(EYes.getSprite());
				window.draw(ENo.getSprite());
			}

			if (Mode >= 0)
			{
				if (Mode != PlayervsPlayer)
					window.draw(EShowPV.getSprite());
				if((Turn==Player1||Turn == Player2) && !isGameOver)window.draw(EGiveUp.getSprite());
				//window.draw(EUndoMove.getSprite());
			}
			//Win 
			if (win >= 0)
				window.draw(win == WHITEWIN ? EWwin.getSprite() : EBwin.getSprite());
			if (isGameOver)
				window.draw(EArrow.getSprite());
			break;

		}

		window.display();
		//************************************************************************

		if (NEEDSCRSHOT&&movefinished)
		{
			scrs = window.capture();
			if (scrs.saveToFile(fdrpath + "/" + to_string(movecount) + ".png")) {
				cout << "\t\t\t[GUi]Screenshot saved" << endl;
				movefinished = false;
			}
			else {
				cout << "[GUI]Failed to take screenshot" << endl;
			}
		}
		

	}
	isOpen = false;
	fm_gm.SendMsg(nullptr,0,false);
}


