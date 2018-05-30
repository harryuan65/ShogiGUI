//#define _WIN32_WINNT 0x0500 //加入這行定義，要放最上面
#include"lib.h"
#include<ctime>
#include<thread>

GUI G;
int buffer[200*sizeof(int)];




int main()
{
	HWND hWnd = GetConsoleWindow(); //隱藏視窗1
	ShowWindow(hWnd, SW_HIDE); //隱藏視窗2
	sf::Thread t(&GUI::EnableGUI, &G);
	bool breakflag = false;
	srand(time(NULL));
	t.launch();
	while (G.isOpen)
	{
		//等待介面與主程式溝通初始化mode
		breakflag = false;
		cout << "Waiting for gui" << endl;
		while (!G.isGameSet);
		cout << "Syncing gamemode"<<endl;
		int getsize = G.fm_mg.RecvMsg(buffer, sizeof(buffer), true);
		while (buffer[0] != ACK);
		cout << "GAME SYNCED" << endl;
		G.gamemodebuf[0] = ACK;
		cout << "**********************************\n[GUI]New Round Started\n**********************************" << endl;

		while (!G.isGameOver)
		{
			cout << "[Recv]Waiting for data..." << endl;
			G.GotStuff = false;
			getsize = G.fm_mg.RecvMsg(buffer, sizeof(buffer), true);
			//TODO flag to recycle the game loop
			switch (buffer[0])
			{
			case MOVE_NULL:
				cout << "[Recv]MOVE_NULL" << endl;
				if (G.Turn)G.win = 1;
				else G.win = 0;
				breakflag = true;
				break;
			case MOVELIST:
				getsize = G.fm_mg.RecvMsg(buffer, sizeof(buffer), true);
				cout << "\t[Recv]Movelist size = " << getsize / sizeof(int) << endl;
				G.SetMovelist(buffer, getsize);
				break;
			case AIPV:
				getsize = G.fm_mg.RecvMsg(buffer, sizeof(buffer), true);
				cout << "\t[Recv]New PV size = " << getsize / sizeof(int) << endl;
				G.StorePV(buffer, getsize);
				G.AIDoMove();
				break;
			case GAMEOVER:
				cout << "\t[Recv]Game Over";/*
				getsize = G.fm_mg.RecvMsg(buffer, sizeof(buffer), true);
				cout << (buffer[0] ? "\t\t[Recv]Winner後手" : "先手") << endl;*/
				G.isGameSet = false;
				breakflag = true;
				break;
			default:
				cout << "\t[Recv]Unknown command!! [ "<<buffer[0]<<"]" << endl;
				break;
			}
			G.GotStuff = true;
			memset(buffer, 0, 800);
			if (breakflag)break;
		}
		cout << "\n\t[Main]遊戲結束. Relooping..." << endl;
	}
	t.wait();
	return 0;
	
}
