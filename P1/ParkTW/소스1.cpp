#include "tetris.h"

int main()
{
	SetConsole(); // 콘솔창을 세팅합니다.
	srand((unsigned)time(NULL)); // 시드값 지정

	IntroDrawer(); // 게임표지
	system("cls"); // 게임화

	ResetGame(); // 게임정보를 초기화
	NewBlockMaker(); //새로운 블록을 생성합니다.

	while (1)
	{
		LevelManeger();

		if (holdChanger == 1)
			holdChanger = 0; // 홀드 체인저 변경

		for (int i = 0; i < 6; i++)
		{
			KeyboardControl(); // 게임 키보드 컨트롤

			if (holdChanger == 1) // 홀드 체인저가 1이면 루프를 빠져나옵니다.
				break;

			ShadowBlockMaker(); // 그림자 블록 생성
			PrintGameBoard(); //게임판을 출력합니다.
			Sleep(game_speed); // 게임 난이도 조절

			if (harddropOn == 1)
			{
				harddropOn = 0;
				break;
			}

			ShadowBlockDeleter(); // 그림자 블록 삭제
			if (crushOn == 1 && CrushCheak(0, 1, FALSE) == FALSE) // 충돌상황이어도 돌릴 수 있는 기회를 줌
				Sleep(50);
		}
		if (holdChanger == 0)
			BlockDrop(); // 블록하강

		LineCheak();
		GameoverCheak();

		if (neednewOn == 1)
			NewBlockMaker(); // 블록생성
	}

}
#include "tetris.h"

void ConsoleSize()// 콘솔창의 크기를 조절합니다.
{
	system("mode con cols=79 lines=30"); // 가로 79, 세로 30으로 설정
}

void RemoveScrollbar() // 콘솔창의 스크롤바를 삭제합니다.
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(handle, &info);
	COORD new_size =
	{
		info.srWindow.Right - info.srWindow.Left + 1,
		info.srWindow.Bottom - info.srWindow.Top + 1
	};
	SetConsoleScreenBufferSize(handle, new_size);
}

void Gotoxy(int x, int y) // 좌표로 커서를 이동합니다.
{
	COORD pos = { 2 * x,y }; // 가로는 두 칸씩 이동합니다.
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void RemoveCurser() // 커서를 표시하지 않습니다.
{
	CONSOLE_CURSOR_INFO curinfo = { 0, };
	curinfo.dwSize = 1;
	curinfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curinfo);
}


void MusicPlay() // 음악을 반복재생합니다.
{
	PlaySound(TEXT(SOUND_FILE_NAME), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}

void SetConsole() // 콘솔창 세팅
{
	ConsoleSize();
	RemoveScrollbar();
	RemoveCurser();
	MusicPlay();
}
#include"tetris.h"
void IntroDrawer()
{
	int x = 5;
	int y = 2;

	Gotoxy(x + 1, y + 0); printf("☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★");
	Gotoxy(x + 1, y + 2); printf("  ■■■  ■■■  ■■■  ■■■    ■■■  ■■■ \n"); Sleep(20);
	Gotoxy(x + 1, y + 3); printf("    ■    ■        ■    ■  ■      ■    ■      \n"); Sleep(20);
	Gotoxy(x + 1, y + 4); printf("    ■    ■■■    ■    ■■■      ■    ■■■  \n"); Sleep(20);
	Gotoxy(x + 1, y + 5); printf("    ■    ■        ■    ■  ■      ■        ■  \n"); Sleep(20);
	Gotoxy(x + 1, y + 6); printf("    ■    ■■■    ■    ■    ■  ■■■  ■■■  \n"); Sleep(20);
	Gotoxy(x + 1, y + 8); printf("★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆");

	Gotoxy(x + 1, y + 18); printf("---------------------- HOWTOPLAY ---------------------");
	Gotoxy(x + 1, y + 20); printf("[◀] LEFT MOVE  [▶] RIGHT MOVE  [SPC] HARD DROP");
	Gotoxy(x + 1, y + 22); printf("[▼] DOWN MOVE  [▲] ROTATE      [A] HOLD");
	Gotoxy(x + 1, y + 24); printf("------------------------------------------------------");

	Gotoxy(x + 2, 26 + y); printf("https://blog.naver.com/workend1998 // Make by 여장소년(DragBoy) ");

	while (1)
	{
		if (_kbhit()) // 입력이 있을때까지
			break;
		Gotoxy(x + 9, y + 13); printf("  >> PRESS ANY BUTTON <<  "); Sleep(200);
		Gotoxy(x + 9, y + 13); printf("                          "); Sleep(200);
	}

	while (_kbhit()) // 버퍼 지우기
		_getch();

	system("cls"); // 화면 지우기
}


void PrintGameBoard() // 게임판 출력
{
	for (int y = 0; y < SIZE_Y; y++)
	{
		for (int x = 0; x < SIZE_X; x++)
		{
			if (copyboard[y][x] != realboard[y][x]) // 리얼보드와 카피를 비교, 값이 다르면 수정해서 출력
			{
				realboard[y][x] = copyboard[y][x];
				switch (realboard[y][x])
				{
				case EMPTY:
					Gotoxy(x + SIZE_X_ADJ, y + SIZE_Y_ADJ);
					printf(" ");
					break;

				case MBLOCK:
					Gotoxy(x + SIZE_X_ADJ, y + SIZE_Y_ADJ);
					printf("■");
					break;

				case OVERLINE:
					Gotoxy(x + SIZE_X_ADJ, y + SIZE_Y_ADJ);
					printf(". ");
					break;

				case SBLOCK:
					Gotoxy(x + SIZE_X_ADJ, y + SIZE_Y_ADJ);
					printf("◎");
					break;

				case WALL:
					Gotoxy(x + SIZE_X_ADJ, y + SIZE_Y_ADJ);
					printf("▩");
					break;

				case FBLOCK:
					Gotoxy(x + SIZE_X_ADJ, y + SIZE_Y_ADJ);
					printf("□");
					break;

				case EBLOCK:
					Gotoxy(x + SIZE_X_ADJ, y + SIZE_Y_ADJ);
					printf("■");
					break;
				}
				if (y == 2 && x != 0 && x != SIZE_X - 1 && copyboard[y][x] == EMPTY)
					copyboard[y][x] = OVERLINE; //오버라인이 지워지면 다시 그리기

			}
		}
	}
}

void UIDrawer() // UI를 그립니다.
{

	int x = 2, y = 2;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

	Gotoxy(2 + x, y); printf("[HOLD]"); // Hold 블록칸
	Gotoxy(x, 1 + y); printf("┌");
	Gotoxy(6 + x, 1 + y); printf("┐");
	Gotoxy(x, 6 + y); printf("└");
	Gotoxy(6 + x, 6 + y); printf("┘");

	Gotoxy(23 + x, y); printf("[NEXT]"); // 1번 블록칸
	Gotoxy(21 + x, 1 + y); printf("┌");
	Gotoxy(27 + x, 1 + y); printf("┐");
	Gotoxy(21 + x, 6 + y); printf("└");
	Gotoxy(27 + x, 6 + y); printf("┘");

	Gotoxy(21 + x, 7 + y); printf("┌"); // 2번 블록칸
	Gotoxy(27 + x, 7 + y); printf("┐");
	Gotoxy(21 + x, 11 + y); printf("└");
	Gotoxy(27 + x, 11 + y); printf("┘");


	Gotoxy(21 + x, 12 + y); printf("┌"); // 3번 블록칸
	Gotoxy(27 + x, 12 + y); printf("┐");
	Gotoxy(21 + x, 15 + y); printf("└");
	Gotoxy(27 + x, 15 + y); printf("┘");


	Gotoxy(21 + x, 17 + y); printf(" [ BESTSCORE ]: ");
	Gotoxy(21 + x, 19 + y); printf(" [ YOURSCORE ]: ");
	Gotoxy(21 + x, 21 + y); printf(" [   LEVEL   ]: ");
	Gotoxy(21 + x, 23 + y); printf(" [  DESTROY  ]: ");

	Gotoxy(x + 5, 26 + y); printf("https://blog.naver.com/workend1998 // Make by 여장소년(DragBoy) ");


	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
	Gotoxy(x - 1, 8 + y); printf(" - How TO PLAY -  ");
	Gotoxy(x - 1, 10 + y); printf("[◀▶] :    MOVE  ");
	Gotoxy(x - 1, 14 + y); printf("[▲] :    ROTATE");
	Gotoxy(x - 1, 12 + y); printf("[▼] : SOFT DROP ");
	Gotoxy(x - 1, 16 + y); printf("[SPC] :HARD DROP");
	Gotoxy(x - 1, 18 + y); printf("[A] :       HOLD");
	Gotoxy(x - 1, 20 + y); printf("[P] :      PAUSE");
	Gotoxy(x - 1, 22 + y); printf("[ESC] :     EXIT");

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

}
void NextBlockDrawer()// 다음블록을 그립니다.
{
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if (blocks[block_typeNext_1][0][y][x] == 1) // Next Block_1 그리기
			{

				Gotoxy(24 + x, 4 + y);
				printf("■");
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				Gotoxy(24 + x, 4 + y);
				printf(" ");
			}

			if (blocks[block_typeNext_2][0][y][x] == 1) // Next Block_2 그리기
			{

				Gotoxy(24 + x, 9 + y);
				printf("■");
			}
			else
			{

				Gotoxy(24 + x, 9 + y);
				printf(" ");
			}

			if (blocks[block_typeNext_3][0][y][x] == 1) // Next Block_3 그리기
			{
				Gotoxy(24 + x, 14 + y);
				printf("■");
			}
			else
			{
				Gotoxy(24 + x, 14 + y);
				printf(" ");
			}
		}
	}

}

void HoldBlockDrawer()
{
	if (holdOn == 0) // 홀드를 사용한적이 없으면 빠져나가기
		return;

	for (int y = 0; y < 4; y++) // 홀드 블록 그리기
	{
		for (int x = 0; x < 4; x++)
		{
			if (blocks[block_typeHold][0][y][x] == 1)
			{
				Gotoxy(3 + x, 4 + y);
				printf("■");
			}
			else
			{
				Gotoxy(3 + x, 4 + y);
				printf(" ");
			}
		}
	}
}

void HideDrawer()
{
	for (int y = 0; y < SIZE_Y - 1; y++) // 게임 영역 가리기
	{
		for (int x = 1; x < SIZE_X - 1; x++)
		{
			Gotoxy(x + SIZE_X_ADJ, y + SIZE_Y_ADJ);
			printf(" ");
		}
	}

	for (int y = 0; y < 4; y++) // 홀드 블록 영역 가리기
	{
		for (int x = 0; x < 6; x++)
		{
			Gotoxy(3 + x, 4 + y);
			printf(" ");
		}
	}

	for (int y = 0; y < 4; y++) // 1번 블록 영역 가리기
	{
		for (int x = 0; x < 6; x++)
		{
			Gotoxy(24 + x, 4 + y);
			printf(" ");
		}
	}

	for (int y = 0; y < 3; y++) // 2번 블록 영역 가리기
	{
		for (int x = 0; x < 6; x++)
		{
			Gotoxy(24 + x, 10 + y);
			printf(" ");
		}
	}

	for (int y = 0; y < 2; y++) // 3번 블록 영역 가리기
	{
		for (int x = 0; x < 6; x++)
		{
			Gotoxy(24 + x, 15 + y);
			printf(" ");
		}
	}

}

void PauseDrawer()
{
	HideDrawer(); // 게임 내 블록 모두 지우기
	Gotoxy(13, 14); printf("  [ PAUSE ] ");
	Gotoxy(11, 16); printf("  PRESS ANY BUTTON ");

	EndPauseManeger(); // 버퍼 비우기
	NextBlockDrawer(); // 다음블록 다시표시
	HoldBlockDrawer(); // 홀드블록 다시표시

	Gotoxy(13, 14); printf("                   ");
	Gotoxy(11, 16); printf("                   ");

	ResetRealBoard(); // 실제 게임판 초기화
}

void GameOverDrawer() // 게임 오버화면을 그림
{
	HideDrawer(); // 게임 내 블록 모두 지우기

	if (bestscoreFlag == 1)
	{
		Gotoxy(11, 12); printf(" ☆★BestScore★☆");
		bestscoreFlag = 0;
	}

	Gotoxy(11, 14); printf("  [ ★GameOver★ ] ");
	Gotoxy(11, 16); printf("  PRESS ANY BUTTON ");

	EndPauseManeger(); // 버퍼 비우기
	Gotoxy(12, 12); printf("                     ");

	NextBlockDrawer(); // 다음블록 다시표시
	HoldBlockDrawer(); // 홀드블록 다시표시

	Gotoxy(11, 14); printf("                   ");
	Gotoxy(11, 16); printf("                   ");
}

void WriteScore() // 스코어 표시
{
	Gotoxy(31, 19); printf("                   ");
	Gotoxy(31, 21); printf("                   ");
	Gotoxy(31, 23); printf("                   ");
	Gotoxy(31, 25); printf("                   ");

	Gotoxy(31, 19); printf("%d", bestscore);
	Gotoxy(31, 21); printf("%d", yourscore);
	Gotoxy(31, 23); printf("%d", game_level);
	Gotoxy(31, 25); printf("%d", deleteline_count);
}

void GameEndDrawer()
{
	for (int y = SIZE_Y; y > 0; y--)
	{
		Sleep(60);
		for (int x = 0; x < SIZE_X; x++)
		{
			if (copyboard[y][x] == FBLOCK)
				copyboard[y][x] = EBLOCK;
		}
		PrintGameBoard(); // 게임판 출력
		Sleep(20);
	}
	Sleep(200);
}#include "tetris.h"

blocks[7][4][4][4] = // [블록종류][회전][세로][가로]
{
	// J미노(0번 블록)
	{
		0,0,0,0,
		0,1,0,0,
		0,1,1,1,
		0,0,0,0,

		0,0,0,0,
		0,0,1,1,
		0,0,1,0,
		0,0,1,0,

		0,0,0,0,
		0,0,0,0,
		0,1,1,1,
		0,0,0,1,

		0,0,0,0,
		0,0,1,0,
		0,0,1,0,
		0,1,1,0
	},
	// L미노(1번 블록)
	{
		0,0,0,0,
		0,0,0,1,
		0,1,1,1,
		0,0,0,0,

		0,0,0,0,
		0,0,1,0,
		0,0,1,0,
		0,0,1,1,

		0,0,0,0,
		0,0,0,0,
		0,1,1,1,
		0,1,0,0,

		0,0,0,0,
		0,1,1,0,
		0,0,1,0,
		0,0,1,0
	},
	// O미노(2번 블록)
	{
		0,0,0,0,
		0,1,1,0,
		0,1,1,0,
		0,0,0,0,

		0,0,0,0,
		0,1,1,0,
		0,1,1,0,
		0,0,0,0,

		0,0,0,0,
		0,1,1,0,
		0,1,1,0,
		0,0,0,0,

		0,0,0,0,
		0,1,1,0,
		0,1,1,0,
		0,0,0,0
	},
	// T미노(3번 블록)
	{
		0,0,0,0,
		0,0,1,0,
		0,1,1,1,
		0,0,0,0,

		0,0,0,0,
		0,0,1,0,
		0,0,1,1,
		0,0,1,0,

		0,0,0,0,
		0,0,0,0,
		0,1,1,1,
		0,0,1,0,

		0,0,0,0,
		0,0,1,0,
		0,1,1,0,
		0,0,1,0
	},
	// I미노(4번 블록)
	{
		0,0,0,0,
		0,0,0,0,
		1,1,1,1,
		0,0,0,0,

		0,0,1,0,
		0,0,1,0,
		0,0,1,0,
		0,0,1,0,

		0,0,0,0,
		1,1,1,1,
		0,0,0,0,
		0,0,0,0,

		0,1,0,0,
		0,1,0,0,
		0,1,0,0,
		0,1,0,0
	},
	// Z미노(5번 블록)
	{
		0,0,0,0,
		0,1,1,0,
		0,0,1,1,
		0,0,0,0,

		0,0,0,1,
		0,0,1,1,
		0,0,1,0,
		0,0,0,0,

		0,1,1,0,
		0,0,1,1,
		0,0,0,0,
		0,0,0,0,

		0,0,1,0,
		0,1,1,0,
		0,1,0,0,
		0,0,0,0
	},
	// S미노(6번 블록)
	{
		0,0,0,0,
		0,0,1,1,
		0,1,1,0,
		0,0,0,0,

		0,0,1,0,
		0,0,1,1,
		0,0,0,1,
		0,0,0,0,

		0,0,1,1,
		0,1,1,0,
		0,0,0,0,
		0,0,0,0,

		0,1,0,0,
		0,1,1,0,
		0,0,1,0,
		0,0,0,0
	}
};

void NewBlockMaker() // 새로운 블록을 맵에 생성합니다.
{
	block_X = (SIZE_X / 2) - 2;
	block_Y = 0;
	block_rotation = 0;

	if (holdOn == 0 || holdOn == 1) // 홀드가능상태일때에만
		NextBlocksPush();
	NextBlockDrawer();

	if (holdOn == 2) // 홀드를 사용했을 때만 업데이트
		HoldBlockDrawer(); // 홀드 블록 그리기

	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if (blocks[block_typeNow][block_rotation][y][x] == 1)
				copyboard[block_Y + y][block_X + x] = MBLOCK;
		}
	}
	neednewOn = 0; // 블록필요상태를 다시 변환
}

int BlockSelecter() // 랜덤한 블록을 선택합니다.
{
	static int count = 7;

	count++;
	if (count > 6)
	{
		BlockShuffler(); // 블록 7개를 다시 섞습니다.
		count = 0; //다시 카운트를 0으로 초기화
	}
	return blockshuffle[count];
}

void BlockShuffler() // 7종류의 블록을 섞어줍니다.
{
	int j, temp;

	for (int i = 0; i < 7; i++)
		blockshuffle[i] = i;

	for (int i = 0; i < 7; i++)
	{
		j = rand() % 7;

		temp = blockshuffle[i];
		blockshuffle[i] = blockshuffle[j];
		blockshuffle[j] = temp;
	}
}

void ResetBlocks() // 블록들을 초기화합니다.
{
	block_typeNext_1 = BlockSelecter();
	block_typeNext_2 = BlockSelecter();
	block_typeNext_3 = BlockSelecter();
}

void NextBlocksPush() // 다음블록을 현재 블록으로 바꿉니다.
{
	block_typeNow = block_typeNext_1;
	block_typeNext_1 = block_typeNext_2;
	block_typeNext_2 = block_typeNext_3;
	block_typeNext_3 = BlockSelecter();
}

void ShadowBlockMaker() // 그림자블록을 생성합니다.
{

	int shadowblock_Y = 0;
	while (1)
	{
		if (CrushCheak(0, shadowblock_Y, FALSE) == TRUE) // 그림자 블록을 픽스블록과 충돌할때까지 내립니다.
			++shadowblock_Y;

		if (CrushCheak(0, shadowblock_Y, FALSE) == FALSE) // 충돌을 한 위치에 그립니다.
		{
			for (int y = 0; y < 4; y++)
			{
				for (int x = 0; x < 4; x++)
				{
					if (blocks[block_typeNow][block_rotation][y][x] == 1
						&& copyboard[(block_Y - 1) + shadowblock_Y + y][block_X + x] < 1) //충돌이 일어난 Y에서 -1을뺌
						copyboard[(block_Y - 1) + shadowblock_Y + y][block_X + x] = SBLOCK;
				}
			}
			shadowblock_Y = 0;
			return;
		}
	}
}
#include "tetris.h"

void KeyboardControl() // 블록을 키보드로 컨드롤 합니다.
{
	int key;
	if (_kbhit())
	{
		key = _getch();
		if (key == 224) //방향키이면
		{
			key = _getch();
			switch (key)
			{
			case LEFT: //왼쪽 이동
				if (CrushCheak(-1, 0, FALSE) == TRUE)
					BlockMove(-1, 0, FALSE);
				break;

			case RIGHT: // 오른쪽 이동
				if (CrushCheak(1, 0, FALSE) == TRUE)
					BlockMove(1, 0, FALSE);
				break;

			case UP: // 기본 회전(왼쪽)
				for (int rotatemove_y = 0;; rotatemove_y--)
				{
					for (int rotatemove_x = 0; rotatemove_x < 3; rotatemove_x++)
					{
						for (int n = 0; n < 2; n++)
						{
							rotatemove_x *= -1;

							if (CrushCheak(rotatemove_x, rotatemove_y, TRUE) == TRUE)
							{
								BlockMove(rotatemove_x, rotatemove_y, TRUE);
								return;
							}
						}
					}
				}

			case DOWN: // 소프트 드롭
				if (CrushCheak(0, 1, FALSE) == TRUE)
					BlockMove(0, 1, FALSE);
				break;

			}
		}
		else
		{
			switch (key)
			{
			case SPACE: // 하드 드롭
				harddropOn = 1;
				while (crushOn != 1)
					BlockDrop();
				break;


			case 'A': // 홀드
			case 'a':

				if (holdOn == 0) // 상황: 해당 판에서 홀드를 한번도 사용한 적이 없다면
				{
					block_typeHold = block_typeNow; // 현재블록을 홀드블록에 저장합니다.
					NextBlocksPush(); // 다음블록을 1칸씩 밀어줍니다.
					neednewOn = 1;
					MblockDeleter(); // 현재 나와있는 무브 블록을 지워줍니다.
					holdOn = 2;
					holdChanger = 1;
					break;
				}
				if (holdOn == 1) // 홀드 사용 가능 상태라면
				{
					int block_typeTemp;
					block_typeTemp = block_typeHold; // 홀드 블록과 현재블록 교체
					block_typeHold = block_typeNow;
					block_typeNow = block_typeTemp;

					neednewOn = 1; // 블록 필요상태로 변경
					MblockDeleter(); // 현재 나와있는 무브 블록을 지워줍니다.
					holdOn = 2; // 홀드 사용 불가능 상태로 변경
					holdChanger = 1;
					break;
				}
				else
					break;// 0,1 이 아니라면 아무일도 일어나지 않아야함 
				break;

			case 'P': // 퍼즈
			case 'p':
				PauseDrawer();
				break;
			case ESC: //ESC 클릭
				system("cls");
				printf("게임이 종료되었습니다\n");
				exit(0); //게임종료 
			}
		}
	}
}

void BlockMove(int inputX, int inputY, int rotateCheak) // 블록을 이동 및 회전시킵니다.
{

	for (int y = 0; y < 4; y++) // 원래 있던 값 지우기
	{
		for (int x = 0; x < 4; x++)
		{
			if (blocks[block_typeNow][block_rotation][y][x] == 1)
				copyboard[block_Y + y][block_X + x] = EMPTY;
		}
	}

	if (rotateCheak == TRUE) // 회전 체크
	{
		block_rotation++;
		if (block_rotation > 3) // 3을 넘어가면
			block_rotation = 0; // 0으로 다시 돌리기
	}

	for (int y = 0; y < 4; y++) // 다시 값 넣기
	{
		for (int x = 0; x < 4; x++)
		{
			if (blocks[block_typeNow][block_rotation][y][x] == 1)
				copyboard[block_Y + y + inputY][block_X + x + inputX] = MBLOCK;
		}
	}

	block_X = block_X + inputX; //입력받은 값 만큼 X값 이동
	block_Y = block_Y + inputY; //입력받은 값 만큼 Y값 이동
}

void BlockDrop() // 블록자동하강
{

	if (crushOn == 1 && CrushCheak(0, 1, FALSE) == TRUE) // 충돌 판정이 켜져 있지만 충돌하지 않음
		crushOn = 0;

	if (crushOn == 1 && CrushCheak(0, 1, FALSE) == FALSE) // 충돌 판정이 켜져있고, 이번에도 충돌
		BlockPrize(); // 블록을 고정시킨다.

	if (CrushCheak(0, 1, FALSE) == TRUE)
		BlockMove(0, 1, FALSE);

	if (CrushCheak(0, 1, FALSE) == FALSE)
		crushOn = 1;
}

void BlockPrize() // 블록을 픽스시킵니다.
{
	for (int y = 0; y < SIZE_Y; y++)
	{
		for (int x = 0; x < SIZE_X; x++)
		{
			if (copyboard[y][x] == MBLOCK)
				copyboard[y][x] = FBLOCK;
		}
	}
	crushOn = 0; // 충돌 체크 끄기
	neednewOn = 1; // 새로운 블록 필요 플래그 켜기
	yourscore += 5; // 점수 획득
	WriteScore(); // 게임 점수를 표시

	if (holdOn == 2) // 홀드키가 사용 불가 상태라면
		holdOn = 1; // 사용가능 상태로 변경
	return;
}
#include "tetris.h"

int CrushCheak(int blockX_ODJ, int blockY_ODJ, int blockR_ODJ)
{
	int temp_blockrotation;
	temp_blockrotation = block_rotation + blockR_ODJ; // 임시 로테이션 테스트 값

	if (temp_blockrotation > 3) // 만약 3보다 커지면 0으로 바꾼다.
		temp_blockrotation = 0;

	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if (blocks[block_typeNow][temp_blockrotation][y][x] ==
				1 && copyboard[block_Y + blockY_ODJ + y][block_X + blockX_ODJ + x] > 3)
				return FALSE;
		}
	}
	return TRUE;
}

void ShadowBlockDeleter() // 그림자 블록 삭제
{
	for (int y = 0; y < SIZE_Y; y++)
	{
		for (int x = 0; x < SIZE_X; x++)
		{
			if (copyboard[y][x] == SBLOCK)
				copyboard[y][x] = EMPTY;
		}
	}
}

void LineCheak() // 라인을 체크하고, 줄을 지웁니다.
{
	int k;
	deleteline_combo = 0; // 라인 파괴 콤보 초기화

	int block_linecheak;
	for (int y = SIZE_Y - 2; y > 2;) // Y이동 ▲
	{
		block_linecheak = 0; // 0으로 초기화
		for (int x = 1; x < SIZE_X - 1; x++) // X이동 ▶
			if (copyboard[y][x] == FBLOCK) // 해당 위치에 fix된 블록이 있으면 값 증가
				block_linecheak++;

		if (block_linecheak == SIZE_X - 2)
		{
			for (k = y; k > 1; k--)
				for (int l = 1; l < SIZE_X - 1; l++)
				{
					if (copyboard[k - 1][l] != OVERLINE)
						copyboard[k][l] = copyboard[k - 1][l];

					if (copyboard[k - 1][l] == OVERLINE)
						copyboard[k][l] = EMPTY;
				}
			deleteline_count++; // 지운줄 총합 증가
			deleteline_combo++; // 라인 파괴 콤보 증가
		}
		else
			y--;
	}
	DeleteScoreManeger(); // 라인 파괴로 인한 점수 획득
}

void MblockDeleter() // 현재 이동중인 블록을 찾아서 지웁니다.
{
	for (int y = 0; y < SIZE_Y; y++)
	{
		for (int x = 0; x < SIZE_X; x++)
		{
			if (copyboard[y][x] == MBLOCK)
				copyboard[y][x] = EMPTY;
		}
	}
}
#include "tetris.h"
void GameoverCheak() // 게임오버를 검사합니다.
{
	for (int y = 0; y < 3; y++) // 오버라인을 넘은 블록이 있는지 체크
	{
		for (int x = 1; x < SIZE_X - 2; x++)
		{
			if (copyboard[y][x] == FBLOCK) // 오버라인을 넘은 블록이 있음?
			{
				if (bestscore < yourscore) // 현재 스코어가 베스트 스코어를 이김?
				{
					bestscoreFlag = 1;
					FILE* data = fopen("score.txt", "wt");

					if (data == 0) // 파일에 에러가 뜨면
					{
						Gotoxy(0, 0);
						printf("데이터 저장에 실패했습니다");
					}
					else
					{
						fprintf(data, "%d", yourscore);
						fclose(data);
					}

				}
				GameEndDrawer();
				GameOverDrawer(); // 게임 오버 화면을 그림
				ResetGame(); // 게임초기화
			}
		}
	}
	return;
}

void ReadBestScore() // 베스트 스코어 읽어오기
{
	FILE* data = fopen("score.txt", "rt");
	if (data == 0)
		bestscore = 0;
	else
	{
		fscanf(data, "%d", &bestscore);
		fclose(data);
	}
}

void ResetGame() // 게임 리셋시키기
{
	ReadBestScore(); // 베스트 스코어를 불러옵니다.
	ResetBlocks(); // 블록을 초기화시킵니다.
	ResetRealBoard(); // 실제게임판을 초기화시킵니다.
	ResetCopyBoard();
	UIDrawer(); // UI를 그립니다.

	holdOn = 0;
	yourscore = 0;
	deleteline_count = 0;
	game_level = 1;
	game_speed = 0;

	WriteScore(); // 게임 점수를 표시

}

void ResetRealBoard() // 실제 게임판을 초기화합니다.
{
	for (int y = 0; y < SIZE_Y; y++)
		for (int x = 0; x < SIZE_X; x++)
			realboard[y][x] = 10000;
}

void ResetCopyBoard() //카피 게임판을 초기화합니다.
{
	for (int y = 0; y < SIZE_Y; y++) // 빈 공간
		for (int x = 0; x < SIZE_X; x++)
			copyboard[y][x] = EMPTY;

	for (int y = 0; y < SIZE_Y; y++)
	{
		for (int x = 0; x < SIZE_X; x++)
		{
			if (x == 0 || x == SIZE_X - 1) // 좌-우 벽 그리기
				copyboard[y][x] = WALL;

			if (y == SIZE_Y - 1) // 하단 벽 그리기
				copyboard[y][x] = WALL;

			if (y == 2 && x != 0 && x != SIZE_X - 1) // 게임 오버라인 그리기
				copyboard[y][x] = OVERLINE;
		}
	}
}

void EndPauseManeger() // 버퍼주는용도
{
	int garbagy;

	Sleep(500);
	while (_kbhit())
		_getch();
	garbagy = _getch();
} // 퍼즈/종료 버퍼비우기

void LevelManeger() // 
{
	if (deleteline_count < 10)
	{
		game_level = 1;
		game_speed = 75;
		return;
	}

	else if (deleteline_count < 20)
	{
		game_level = 2;
		game_speed = 45;
		return;
	}

	else if (deleteline_count < 30)
	{
		game_level = 3;
		game_speed = 35;
		return;
	}

	else if (deleteline_count < 40)
	{
		game_level = 4;
		game_speed = 30;
		return;
	}

	else if (deleteline_count < 50)
	{
		game_level = 5;
		game_speed = 25;
		return;
	}

	else if (deleteline_count < 60)
	{
		game_level = 6;
		game_speed = 20;
		return;
	}

	else if (deleteline_count < 70)
	{
		game_level = 7;
		game_speed = 15;
		return;
	}

	else
	{
		game_level = 8;
		game_speed = 10;
		return;
	}

} // 레벨(게임스피드) 매니저
void DeleteScoreManeger()
{
	if (deleteline_combo == 1)
		yourscore += 50;

	if (deleteline_combo == 2)
	{
		yourscore += 150;
		Gotoxy(13, 26); printf("%d c o m bo!", deleteline_combo); Sleep(200);
		Gotoxy(13, 26); printf("            ");
	}

	if (deleteline_combo == 3)
	{
		yourscore += 300;
		Gotoxy(13, 26); printf("%d c o m b o!", deleteline_combo); Sleep(200);
		Gotoxy(13, 26); printf("             ");
	}

	if (deleteline_combo == 4)
	{
		yourscore += 1000;
		Gotoxy(13, 26); printf("%d c o m b o!", deleteline_combo); Sleep(200);
		Gotoxy(13, 26); printf("             ");
	}
} // 라인 파괴 점수 획득