#include "tetris.h"

int main()
{
	SetConsole(); // �ܼ�â�� �����մϴ�.
	srand((unsigned)time(NULL)); // �õ尪 ����

	IntroDrawer(); // ����ǥ��
	system("cls"); // ����ȭ

	ResetGame(); // ���������� �ʱ�ȭ
	NewBlockMaker(); //���ο� ����� �����մϴ�.

	while (1)
	{
		LevelManeger();

		if (holdChanger == 1)
			holdChanger = 0; // Ȧ�� ü���� ����

		for (int i = 0; i < 6; i++)
		{
			KeyboardControl(); // ���� Ű���� ��Ʈ��

			if (holdChanger == 1) // Ȧ�� ü������ 1�̸� ������ �������ɴϴ�.
				break;

			ShadowBlockMaker(); // �׸��� ��� ����
			PrintGameBoard(); //�������� ����մϴ�.
			Sleep(game_speed); // ���� ���̵� ����

			if (harddropOn == 1)
			{
				harddropOn = 0;
				break;
			}

			ShadowBlockDeleter(); // �׸��� ��� ����
			if (crushOn == 1 && CrushCheak(0, 1, FALSE) == FALSE) // �浹��Ȳ�̾ ���� �� �ִ� ��ȸ�� ��
				Sleep(50);
		}
		if (holdChanger == 0)
			BlockDrop(); // ����ϰ�

		LineCheak();
		GameoverCheak();

		if (neednewOn == 1)
			NewBlockMaker(); // ��ϻ���
	}

}
#include "tetris.h"

void ConsoleSize()// �ܼ�â�� ũ�⸦ �����մϴ�.
{
	system("mode con cols=79 lines=30"); // ���� 79, ���� 30���� ����
}

void RemoveScrollbar() // �ܼ�â�� ��ũ�ѹٸ� �����մϴ�.
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

void Gotoxy(int x, int y) // ��ǥ�� Ŀ���� �̵��մϴ�.
{
	COORD pos = { 2 * x,y }; // ���δ� �� ĭ�� �̵��մϴ�.
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void RemoveCurser() // Ŀ���� ǥ������ �ʽ��ϴ�.
{
	CONSOLE_CURSOR_INFO curinfo = { 0, };
	curinfo.dwSize = 1;
	curinfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curinfo);
}


void MusicPlay() // ������ �ݺ�����մϴ�.
{
	PlaySound(TEXT(SOUND_FILE_NAME), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}

void SetConsole() // �ܼ�â ����
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

	Gotoxy(x + 1, y + 0); printf("�١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١�");
	Gotoxy(x + 1, y + 2); printf("  ����  ����  ����  ����    ����  ���� \n"); Sleep(20);
	Gotoxy(x + 1, y + 3); printf("    ��    ��        ��    ��  ��      ��    ��      \n"); Sleep(20);
	Gotoxy(x + 1, y + 4); printf("    ��    ����    ��    ����      ��    ����  \n"); Sleep(20);
	Gotoxy(x + 1, y + 5); printf("    ��    ��        ��    ��  ��      ��        ��  \n"); Sleep(20);
	Gotoxy(x + 1, y + 6); printf("    ��    ����    ��    ��    ��  ����  ����  \n"); Sleep(20);
	Gotoxy(x + 1, y + 8); printf("�ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ�");

	Gotoxy(x + 1, y + 18); printf("---------------------- HOWTOPLAY ---------------------");
	Gotoxy(x + 1, y + 20); printf("[��] LEFT MOVE  [��] RIGHT MOVE  [SPC] HARD DROP");
	Gotoxy(x + 1, y + 22); printf("[��] DOWN MOVE  [��] ROTATE      [A] HOLD");
	Gotoxy(x + 1, y + 24); printf("------------------------------------------------------");

	Gotoxy(x + 2, 26 + y); printf("https://blog.naver.com/workend1998 // Make by ����ҳ�(DragBoy) ");

	while (1)
	{
		if (_kbhit()) // �Է��� ����������
			break;
		Gotoxy(x + 9, y + 13); printf("  >> PRESS ANY BUTTON <<  "); Sleep(200);
		Gotoxy(x + 9, y + 13); printf("                          "); Sleep(200);
	}

	while (_kbhit()) // ���� �����
		_getch();

	system("cls"); // ȭ�� �����
}


void PrintGameBoard() // ������ ���
{
	for (int y = 0; y < SIZE_Y; y++)
	{
		for (int x = 0; x < SIZE_X; x++)
		{
			if (copyboard[y][x] != realboard[y][x]) // ���󺸵�� ī�Ǹ� ��, ���� �ٸ��� �����ؼ� ���
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
					printf("��");
					break;

				case OVERLINE:
					Gotoxy(x + SIZE_X_ADJ, y + SIZE_Y_ADJ);
					printf(". ");
					break;

				case SBLOCK:
					Gotoxy(x + SIZE_X_ADJ, y + SIZE_Y_ADJ);
					printf("��");
					break;

				case WALL:
					Gotoxy(x + SIZE_X_ADJ, y + SIZE_Y_ADJ);
					printf("��");
					break;

				case FBLOCK:
					Gotoxy(x + SIZE_X_ADJ, y + SIZE_Y_ADJ);
					printf("��");
					break;

				case EBLOCK:
					Gotoxy(x + SIZE_X_ADJ, y + SIZE_Y_ADJ);
					printf("��");
					break;
				}
				if (y == 2 && x != 0 && x != SIZE_X - 1 && copyboard[y][x] == EMPTY)
					copyboard[y][x] = OVERLINE; //���������� �������� �ٽ� �׸���

			}
		}
	}
}

void UIDrawer() // UI�� �׸��ϴ�.
{

	int x = 2, y = 2;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

	Gotoxy(2 + x, y); printf("[HOLD]"); // Hold ���ĭ
	Gotoxy(x, 1 + y); printf("��");
	Gotoxy(6 + x, 1 + y); printf("��");
	Gotoxy(x, 6 + y); printf("��");
	Gotoxy(6 + x, 6 + y); printf("��");

	Gotoxy(23 + x, y); printf("[NEXT]"); // 1�� ���ĭ
	Gotoxy(21 + x, 1 + y); printf("��");
	Gotoxy(27 + x, 1 + y); printf("��");
	Gotoxy(21 + x, 6 + y); printf("��");
	Gotoxy(27 + x, 6 + y); printf("��");

	Gotoxy(21 + x, 7 + y); printf("��"); // 2�� ���ĭ
	Gotoxy(27 + x, 7 + y); printf("��");
	Gotoxy(21 + x, 11 + y); printf("��");
	Gotoxy(27 + x, 11 + y); printf("��");


	Gotoxy(21 + x, 12 + y); printf("��"); // 3�� ���ĭ
	Gotoxy(27 + x, 12 + y); printf("��");
	Gotoxy(21 + x, 15 + y); printf("��");
	Gotoxy(27 + x, 15 + y); printf("��");


	Gotoxy(21 + x, 17 + y); printf(" [ BESTSCORE ]: ");
	Gotoxy(21 + x, 19 + y); printf(" [ YOURSCORE ]: ");
	Gotoxy(21 + x, 21 + y); printf(" [   LEVEL   ]: ");
	Gotoxy(21 + x, 23 + y); printf(" [  DESTROY  ]: ");

	Gotoxy(x + 5, 26 + y); printf("https://blog.naver.com/workend1998 // Make by ����ҳ�(DragBoy) ");


	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
	Gotoxy(x - 1, 8 + y); printf(" - How TO PLAY -  ");
	Gotoxy(x - 1, 10 + y); printf("[����] :    MOVE  ");
	Gotoxy(x - 1, 14 + y); printf("[��] :    ROTATE");
	Gotoxy(x - 1, 12 + y); printf("[��] : SOFT DROP ");
	Gotoxy(x - 1, 16 + y); printf("[SPC] :HARD DROP");
	Gotoxy(x - 1, 18 + y); printf("[A] :       HOLD");
	Gotoxy(x - 1, 20 + y); printf("[P] :      PAUSE");
	Gotoxy(x - 1, 22 + y); printf("[ESC] :     EXIT");

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

}
void NextBlockDrawer()// ��������� �׸��ϴ�.
{
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if (blocks[block_typeNext_1][0][y][x] == 1) // Next Block_1 �׸���
			{

				Gotoxy(24 + x, 4 + y);
				printf("��");
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				Gotoxy(24 + x, 4 + y);
				printf(" ");
			}

			if (blocks[block_typeNext_2][0][y][x] == 1) // Next Block_2 �׸���
			{

				Gotoxy(24 + x, 9 + y);
				printf("��");
			}
			else
			{

				Gotoxy(24 + x, 9 + y);
				printf(" ");
			}

			if (blocks[block_typeNext_3][0][y][x] == 1) // Next Block_3 �׸���
			{
				Gotoxy(24 + x, 14 + y);
				printf("��");
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
	if (holdOn == 0) // Ȧ�带 ��������� ������ ����������
		return;

	for (int y = 0; y < 4; y++) // Ȧ�� ��� �׸���
	{
		for (int x = 0; x < 4; x++)
		{
			if (blocks[block_typeHold][0][y][x] == 1)
			{
				Gotoxy(3 + x, 4 + y);
				printf("��");
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
	for (int y = 0; y < SIZE_Y - 1; y++) // ���� ���� ������
	{
		for (int x = 1; x < SIZE_X - 1; x++)
		{
			Gotoxy(x + SIZE_X_ADJ, y + SIZE_Y_ADJ);
			printf(" ");
		}
	}

	for (int y = 0; y < 4; y++) // Ȧ�� ��� ���� ������
	{
		for (int x = 0; x < 6; x++)
		{
			Gotoxy(3 + x, 4 + y);
			printf(" ");
		}
	}

	for (int y = 0; y < 4; y++) // 1�� ��� ���� ������
	{
		for (int x = 0; x < 6; x++)
		{
			Gotoxy(24 + x, 4 + y);
			printf(" ");
		}
	}

	for (int y = 0; y < 3; y++) // 2�� ��� ���� ������
	{
		for (int x = 0; x < 6; x++)
		{
			Gotoxy(24 + x, 10 + y);
			printf(" ");
		}
	}

	for (int y = 0; y < 2; y++) // 3�� ��� ���� ������
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
	HideDrawer(); // ���� �� ��� ��� �����
	Gotoxy(13, 14); printf("  [ PAUSE ] ");
	Gotoxy(11, 16); printf("  PRESS ANY BUTTON ");

	EndPauseManeger(); // ���� ����
	NextBlockDrawer(); // ������� �ٽ�ǥ��
	HoldBlockDrawer(); // Ȧ���� �ٽ�ǥ��

	Gotoxy(13, 14); printf("                   ");
	Gotoxy(11, 16); printf("                   ");

	ResetRealBoard(); // ���� ������ �ʱ�ȭ
}

void GameOverDrawer() // ���� ����ȭ���� �׸�
{
	HideDrawer(); // ���� �� ��� ��� �����

	if (bestscoreFlag == 1)
	{
		Gotoxy(11, 12); printf(" �١�BestScore�ڡ�");
		bestscoreFlag = 0;
	}

	Gotoxy(11, 14); printf("  [ ��GameOver�� ] ");
	Gotoxy(11, 16); printf("  PRESS ANY BUTTON ");

	EndPauseManeger(); // ���� ����
	Gotoxy(12, 12); printf("                     ");

	NextBlockDrawer(); // ������� �ٽ�ǥ��
	HoldBlockDrawer(); // Ȧ���� �ٽ�ǥ��

	Gotoxy(11, 14); printf("                   ");
	Gotoxy(11, 16); printf("                   ");
}

void WriteScore() // ���ھ� ǥ��
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
		PrintGameBoard(); // ������ ���
		Sleep(20);
	}
	Sleep(200);
}#include "tetris.h"

blocks[7][4][4][4] = // [�������][ȸ��][����][����]
{
	// J�̳�(0�� ���)
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
	// L�̳�(1�� ���)
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
	// O�̳�(2�� ���)
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
	// T�̳�(3�� ���)
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
	// I�̳�(4�� ���)
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
	// Z�̳�(5�� ���)
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
	// S�̳�(6�� ���)
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

void NewBlockMaker() // ���ο� ����� �ʿ� �����մϴ�.
{
	block_X = (SIZE_X / 2) - 2;
	block_Y = 0;
	block_rotation = 0;

	if (holdOn == 0 || holdOn == 1) // Ȧ�尡�ɻ����϶�����
		NextBlocksPush();
	NextBlockDrawer();

	if (holdOn == 2) // Ȧ�带 ������� ���� ������Ʈ
		HoldBlockDrawer(); // Ȧ�� ��� �׸���

	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if (blocks[block_typeNow][block_rotation][y][x] == 1)
				copyboard[block_Y + y][block_X + x] = MBLOCK;
		}
	}
	neednewOn = 0; // ����ʿ���¸� �ٽ� ��ȯ
}

int BlockSelecter() // ������ ����� �����մϴ�.
{
	static int count = 7;

	count++;
	if (count > 6)
	{
		BlockShuffler(); // ��� 7���� �ٽ� �����ϴ�.
		count = 0; //�ٽ� ī��Ʈ�� 0���� �ʱ�ȭ
	}
	return blockshuffle[count];
}

void BlockShuffler() // 7������ ����� �����ݴϴ�.
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

void ResetBlocks() // ��ϵ��� �ʱ�ȭ�մϴ�.
{
	block_typeNext_1 = BlockSelecter();
	block_typeNext_2 = BlockSelecter();
	block_typeNext_3 = BlockSelecter();
}

void NextBlocksPush() // ��������� ���� ������� �ٲߴϴ�.
{
	block_typeNow = block_typeNext_1;
	block_typeNext_1 = block_typeNext_2;
	block_typeNext_2 = block_typeNext_3;
	block_typeNext_3 = BlockSelecter();
}

void ShadowBlockMaker() // �׸��ں���� �����մϴ�.
{

	int shadowblock_Y = 0;
	while (1)
	{
		if (CrushCheak(0, shadowblock_Y, FALSE) == TRUE) // �׸��� ����� �Ƚ���ϰ� �浹�Ҷ����� �����ϴ�.
			++shadowblock_Y;

		if (CrushCheak(0, shadowblock_Y, FALSE) == FALSE) // �浹�� �� ��ġ�� �׸��ϴ�.
		{
			for (int y = 0; y < 4; y++)
			{
				for (int x = 0; x < 4; x++)
				{
					if (blocks[block_typeNow][block_rotation][y][x] == 1
						&& copyboard[(block_Y - 1) + shadowblock_Y + y][block_X + x] < 1) //�浹�� �Ͼ Y���� -1����
						copyboard[(block_Y - 1) + shadowblock_Y + y][block_X + x] = SBLOCK;
				}
			}
			shadowblock_Y = 0;
			return;
		}
	}
}
#include "tetris.h"

void KeyboardControl() // ����� Ű����� ����� �մϴ�.
{
	int key;
	if (_kbhit())
	{
		key = _getch();
		if (key == 224) //����Ű�̸�
		{
			key = _getch();
			switch (key)
			{
			case LEFT: //���� �̵�
				if (CrushCheak(-1, 0, FALSE) == TRUE)
					BlockMove(-1, 0, FALSE);
				break;

			case RIGHT: // ������ �̵�
				if (CrushCheak(1, 0, FALSE) == TRUE)
					BlockMove(1, 0, FALSE);
				break;

			case UP: // �⺻ ȸ��(����)
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

			case DOWN: // ����Ʈ ���
				if (CrushCheak(0, 1, FALSE) == TRUE)
					BlockMove(0, 1, FALSE);
				break;

			}
		}
		else
		{
			switch (key)
			{
			case SPACE: // �ϵ� ���
				harddropOn = 1;
				while (crushOn != 1)
					BlockDrop();
				break;


			case 'A': // Ȧ��
			case 'a':

				if (holdOn == 0) // ��Ȳ: �ش� �ǿ��� Ȧ�带 �ѹ��� ����� ���� ���ٸ�
				{
					block_typeHold = block_typeNow; // �������� Ȧ���Ͽ� �����մϴ�.
					NextBlocksPush(); // ��������� 1ĭ�� �о��ݴϴ�.
					neednewOn = 1;
					MblockDeleter(); // ���� �����ִ� ���� ����� �����ݴϴ�.
					holdOn = 2;
					holdChanger = 1;
					break;
				}
				if (holdOn == 1) // Ȧ�� ��� ���� ���¶��
				{
					int block_typeTemp;
					block_typeTemp = block_typeHold; // Ȧ�� ��ϰ� ������ ��ü
					block_typeHold = block_typeNow;
					block_typeNow = block_typeTemp;

					neednewOn = 1; // ��� �ʿ���·� ����
					MblockDeleter(); // ���� �����ִ� ���� ����� �����ݴϴ�.
					holdOn = 2; // Ȧ�� ��� �Ұ��� ���·� ����
					holdChanger = 1;
					break;
				}
				else
					break;// 0,1 �� �ƴ϶�� �ƹ��ϵ� �Ͼ�� �ʾƾ��� 
				break;

			case 'P': // ����
			case 'p':
				PauseDrawer();
				break;
			case ESC: //ESC Ŭ��
				system("cls");
				printf("������ ����Ǿ����ϴ�\n");
				exit(0); //�������� 
			}
		}
	}
}

void BlockMove(int inputX, int inputY, int rotateCheak) // ����� �̵� �� ȸ����ŵ�ϴ�.
{

	for (int y = 0; y < 4; y++) // ���� �ִ� �� �����
	{
		for (int x = 0; x < 4; x++)
		{
			if (blocks[block_typeNow][block_rotation][y][x] == 1)
				copyboard[block_Y + y][block_X + x] = EMPTY;
		}
	}

	if (rotateCheak == TRUE) // ȸ�� üũ
	{
		block_rotation++;
		if (block_rotation > 3) // 3�� �Ѿ��
			block_rotation = 0; // 0���� �ٽ� ������
	}

	for (int y = 0; y < 4; y++) // �ٽ� �� �ֱ�
	{
		for (int x = 0; x < 4; x++)
		{
			if (blocks[block_typeNow][block_rotation][y][x] == 1)
				copyboard[block_Y + y + inputY][block_X + x + inputX] = MBLOCK;
		}
	}

	block_X = block_X + inputX; //�Է¹��� �� ��ŭ X�� �̵�
	block_Y = block_Y + inputY; //�Է¹��� �� ��ŭ Y�� �̵�
}

void BlockDrop() // ����ڵ��ϰ�
{

	if (crushOn == 1 && CrushCheak(0, 1, FALSE) == TRUE) // �浹 ������ ���� ������ �浹���� ����
		crushOn = 0;

	if (crushOn == 1 && CrushCheak(0, 1, FALSE) == FALSE) // �浹 ������ �����ְ�, �̹����� �浹
		BlockPrize(); // ����� ������Ų��.

	if (CrushCheak(0, 1, FALSE) == TRUE)
		BlockMove(0, 1, FALSE);

	if (CrushCheak(0, 1, FALSE) == FALSE)
		crushOn = 1;
}

void BlockPrize() // ����� �Ƚ���ŵ�ϴ�.
{
	for (int y = 0; y < SIZE_Y; y++)
	{
		for (int x = 0; x < SIZE_X; x++)
		{
			if (copyboard[y][x] == MBLOCK)
				copyboard[y][x] = FBLOCK;
		}
	}
	crushOn = 0; // �浹 üũ ����
	neednewOn = 1; // ���ο� ��� �ʿ� �÷��� �ѱ�
	yourscore += 5; // ���� ȹ��
	WriteScore(); // ���� ������ ǥ��

	if (holdOn == 2) // Ȧ��Ű�� ��� �Ұ� ���¶��
		holdOn = 1; // ��밡�� ���·� ����
	return;
}
#include "tetris.h"

int CrushCheak(int blockX_ODJ, int blockY_ODJ, int blockR_ODJ)
{
	int temp_blockrotation;
	temp_blockrotation = block_rotation + blockR_ODJ; // �ӽ� �����̼� �׽�Ʈ ��

	if (temp_blockrotation > 3) // ���� 3���� Ŀ���� 0���� �ٲ۴�.
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

void ShadowBlockDeleter() // �׸��� ��� ����
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

void LineCheak() // ������ üũ�ϰ�, ���� ����ϴ�.
{
	int k;
	deleteline_combo = 0; // ���� �ı� �޺� �ʱ�ȭ

	int block_linecheak;
	for (int y = SIZE_Y - 2; y > 2;) // Y�̵� ��
	{
		block_linecheak = 0; // 0���� �ʱ�ȭ
		for (int x = 1; x < SIZE_X - 1; x++) // X�̵� ��
			if (copyboard[y][x] == FBLOCK) // �ش� ��ġ�� fix�� ����� ������ �� ����
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
			deleteline_count++; // ������ ���� ����
			deleteline_combo++; // ���� �ı� �޺� ����
		}
		else
			y--;
	}
	DeleteScoreManeger(); // ���� �ı��� ���� ���� ȹ��
}

void MblockDeleter() // ���� �̵����� ����� ã�Ƽ� ����ϴ�.
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
void GameoverCheak() // ���ӿ����� �˻��մϴ�.
{
	for (int y = 0; y < 3; y++) // ���������� ���� ����� �ִ��� üũ
	{
		for (int x = 1; x < SIZE_X - 2; x++)
		{
			if (copyboard[y][x] == FBLOCK) // ���������� ���� ����� ����?
			{
				if (bestscore < yourscore) // ���� ���ھ ����Ʈ ���ھ �̱�?
				{
					bestscoreFlag = 1;
					FILE* data = fopen("score.txt", "wt");

					if (data == 0) // ���Ͽ� ������ �߸�
					{
						Gotoxy(0, 0);
						printf("������ ���忡 �����߽��ϴ�");
					}
					else
					{
						fprintf(data, "%d", yourscore);
						fclose(data);
					}

				}
				GameEndDrawer();
				GameOverDrawer(); // ���� ���� ȭ���� �׸�
				ResetGame(); // �����ʱ�ȭ
			}
		}
	}
	return;
}

void ReadBestScore() // ����Ʈ ���ھ� �о����
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

void ResetGame() // ���� ���½�Ű��
{
	ReadBestScore(); // ����Ʈ ���ھ �ҷ��ɴϴ�.
	ResetBlocks(); // ����� �ʱ�ȭ��ŵ�ϴ�.
	ResetRealBoard(); // ������������ �ʱ�ȭ��ŵ�ϴ�.
	ResetCopyBoard();
	UIDrawer(); // UI�� �׸��ϴ�.

	holdOn = 0;
	yourscore = 0;
	deleteline_count = 0;
	game_level = 1;
	game_speed = 0;

	WriteScore(); // ���� ������ ǥ��

}

void ResetRealBoard() // ���� �������� �ʱ�ȭ�մϴ�.
{
	for (int y = 0; y < SIZE_Y; y++)
		for (int x = 0; x < SIZE_X; x++)
			realboard[y][x] = 10000;
}

void ResetCopyBoard() //ī�� �������� �ʱ�ȭ�մϴ�.
{
	for (int y = 0; y < SIZE_Y; y++) // �� ����
		for (int x = 0; x < SIZE_X; x++)
			copyboard[y][x] = EMPTY;

	for (int y = 0; y < SIZE_Y; y++)
	{
		for (int x = 0; x < SIZE_X; x++)
		{
			if (x == 0 || x == SIZE_X - 1) // ��-�� �� �׸���
				copyboard[y][x] = WALL;

			if (y == SIZE_Y - 1) // �ϴ� �� �׸���
				copyboard[y][x] = WALL;

			if (y == 2 && x != 0 && x != SIZE_X - 1) // ���� �������� �׸���
				copyboard[y][x] = OVERLINE;
		}
	}
}

void EndPauseManeger() // �����ִ¿뵵
{
	int garbagy;

	Sleep(500);
	while (_kbhit())
		_getch();
	garbagy = _getch();
} // ����/���� ���ۺ���

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

} // ����(���ӽ��ǵ�) �Ŵ���
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
} // ���� �ı� ���� ȹ��