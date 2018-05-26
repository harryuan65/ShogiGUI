#include"lib.h"
#include<ctime>
#include<thread>
void SetColor(int color = -1) // 直接先給預設
{
	switch (color)
	{
	case 0:    // White on Black
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			FOREGROUND_INTENSITY | FOREGROUND_RED |
			FOREGROUND_GREEN | FOREGROUND_BLUE);
		break;
	case 1:    // Red on Black
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			FOREGROUND_INTENSITY | FOREGROUND_RED);
		break;
	case 2:    // Green on Black
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			FOREGROUND_INTENSITY | FOREGROUND_GREEN);
		break;
	case 3:    // Yellow on Black
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			FOREGROUND_INTENSITY | FOREGROUND_RED |
			FOREGROUND_GREEN);
		break;
	case 4:    // Blue on Black
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			FOREGROUND_INTENSITY | FOREGROUND_BLUE);
		break;
	case 5:    // Magenta on Black
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			FOREGROUND_INTENSITY | FOREGROUND_RED |
			FOREGROUND_BLUE);
		break;
	case 6:    // Cyan on Black
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			FOREGROUND_INTENSITY | FOREGROUND_GREEN |
			FOREGROUND_BLUE);
		break;
	case 7:    // Black on Gray
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			BACKGROUND_INTENSITY | BACKGROUND_INTENSITY);
		break;
	
	default:    // White on Black
		
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
				FOREGROUND_INTENSITY | FOREGROUND_RED |
				FOREGROUND_GREEN | FOREGROUND_BLUE);
		break;
	}
}
GUI G;
int buffer[200*sizeof(int)];
enum type {
	MOVELIST = 1,AI,SETBOARD, GAMEOVER
};
bool Connect()
{
	char *mode[] = { "玩家VS電腦","電腦VS玩家","玩家對打","電腦對打","電腦對打 本機VS其他程式" };
	//char *mode[] = { "[Player Vs CPU]","[CPU VS Player]","[Player vs Player]","[CPU vs CPU]","[CPU vs CPU(Others)]" };

	
	if (EDIT_MODE||DEBUG_MODE)
	{
		cout << "*******[Debug mode]**********" << endl;
	}
	else
	{
		cout << "[Waiting to connect]" << endl;
		G.fm_mg.RecvMsg(buffer, sizeof(buffer), true);
		cout << "[Connected]" << "Mode = ";
		int Mode = buffer[0];
		if (Mode >= PlayervsAI && Mode < AIvsOtherAI)
		{
			cout << mode[Mode] << "]" << endl;
			switch (Mode)
			{
			case PlayervsAI:
				G.Turn = Player1;
				break;
			case AIvsPlayer:
				G.Turn = AI1;
				break;
			case PlayervsPlayer:
				G.Turn = Player1;
				break;
			case AIvsAI:
				G.Turn = AI1;
				break;
			case AIvsOtherAI:
				G.Turn = AI1;
				break;
			default:
				cout<<"[Mode]ERROR"<<endl;
				break;
			}
			G.Mode = Mode;
		}
		else 
		{
			cout << "[Mode Error!]" << endl;
			return false;
		}
	}
	
	
	return true;
}


int main()
{
	SetColor();
	sf::Thread t(&GUI::EnableGUI, &G);
	
	t.launch();
	srand(time(NULL));
	while (!Connect())
	{
		cerr << "[Failed to connect]"<<endl;
		system("clr");
	}
	
	G.SetBoard();
	G.UpdatePVnBoard();
	
	int src = 0;
	int dst = 0;
	bool pro = 0;
	while (true)
	{
		cout << "[Recv]Waiting for data..." << endl;
		int getsize = G.fm_mg.RecvMsg(buffer, sizeof(buffer), true);
		cout << "\tData [ " << buffer << " ] with size = " << getsize / sizeof(int) << endl;
		switch (buffer[0])
		{
		case MOVE_NULL:
			if (G.Turn)G.win = 1;
			else G.win = 0;
			break;
		case MOVE_ILLEGAL:
			cout << "\t[Recv]Invalid Move" << endl;
			G.ResetMove();
			break;
		case MOVELIST:
			//cout << "\t[**]Waiting for Movelist" <<endl;
			getsize = G.fm_mg.RecvMsg(buffer, sizeof(buffer), true);
			cout << "\t[Recv]Movelist size = " << getsize / sizeof(int) << endl;
			G.SetMovelist(buffer, getsize);
			break;
		case AI:
			//cout << "\t[**]Waiting for AI" << endl;
			getsize = G.fm_mg.RecvMsg(buffer, sizeof(buffer), true);
			cout << "\t[Recv]New PV size = " << getsize / sizeof(int) << endl;
			G.StorePV(buffer, getsize);
			G.AIDoMove();
			break;
		case GAMEOVER:
			cout << "\t[Recv]Game Over";
			getsize = G.fm_mg.RecvMsg(buffer, sizeof(buffer), true);
			cout << (buffer[0]?"\t\t[WINNER]黑方":"白方") << endl;
			G.win = buffer[0];
			break;
		default:
			cout << "\t[Recv]Unknown command!!" << endl;
			break;
		}
		SetColor(2);
		cout << "[Game]Now it's "<<TurnStr[G.Turn]<<"\'s Turn:" << endl;
		SetColor();
		memset(buffer, 0, 800);
	}
	t.wait();
	return 0;
	
}
