#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<time.h>
void gotoxy(short x, short y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE), c);
}
int draw_ship(short x, short y)
{
	gotoxy(x, y);
	printf("<-0->");
	return 0;
}
int erase_ship(short x, short y)
{
	gotoxy(x, y);
	printf("      ");
	return 0;
}
void setcursor(bool visible)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console, &lpCursor);
}
void setcolor(int fg, int bg)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, bg * 16 + fg);
}
int draw_bullet(short x, short y)
{
	gotoxy(x + 2, y);
	setcolor(0, 2);
	printf(" ");

	return 0;
}
int draw_star(short x, short y)
{
	gotoxy(x, y);
	printf("*");
	return 0;
}
int erase_star(short x, short y)
{
	gotoxy(x, y);
	printf(" ");
	return 0;
}
int erase_bullet(short x, short y)
{
	gotoxy(x + 2, y);
	printf(" ");
	return 0;
}
int show_score(int score)
{
	gotoxy(100, 0);
	setcolor(3, 0);
	printf("score= %d", score);
	return 0;
}
char cursor(int x, int y) {
	HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);
	char buf[2]; COORD c = { x,y }; DWORD num_read;
	if (
		!ReadConsoleOutputCharacter(hStd, (LPTSTR)buf, 1, c, (LPDWORD)&num_read))

		return '\0';
	else
		return buf[0];

}
int main()
{
	int i, j, c = 0, score = 0;
	short bullet = 0;
	char ch = ' ', move = 's';
	int x = 38, y = 20, tempx = 0, tempy = 0;
	short b = 0;
	int  bx[20], by[20], starx[21], stary[21];
	setcursor(0);
	setcolor(2, 4);
	draw_ship(x, y);
	setcolor(6, 0);
	srand(time(NULL));
	for (i = 1; i <= 20; i++)
	{
		tempx = 10 + (rand() % 61); tempy = 2 + (rand() % 4);
		for (j = 1; j <= i; j++)
		{
			if (starx[j] == tempx && stary[j] == tempy)
			{
				c++;
			}
		}
		if (c == 0) {
			draw_star(starx[i] = tempx, stary[i] = tempy);
			setcolor(6, 0);
		}
		else i--;
		c = 0;
	}
	do {
		if (b == 5 && by[0] == 0) b = 0;
		draw_ship(x, y);
		if (_kbhit()) {
			ch = _getch();
			if (ch == ' ' && b < 5) { bullet = 1; bx[b] = x; by[b] = y - 1; setcolor(3, 0); draw_bullet(bx[b], by[b]); b++; }
			if (ch == 'a' || ch == 's' || ch == 'd') move = ch;
		}
		setcolor(2, 4);
		if (move == 'a') {
			if (x == 0) { draw_ship(x, y); }
			else {
				setcolor(7, 0);
				erase_ship(x, y);
				setcolor(2, 4);
				draw_ship(--x, y);
			}
		}
		if (move == 'd') {
			if (x == 80) { draw_ship(x, y); }
			else {
				setcolor(7, 0);
				erase_ship(x, y);
				setcolor(2, 4);
				draw_ship(++x, y);
			}
		}
		fflush(stdin);
		Sleep(100);
		for (i = 0; i <= 5; i++) {
			if (bullet == 1 && by[i] >= 1) {
				setcolor(6, 0);
				erase_bullet(bx[i], by[i]);
				if (cursor(bx[i] + 2, by[i] - 1) == '*')
				{
					score++;
					Beep(700, 100);
					for (int re = 0; re < 1; re++) {
						tempx = 10 + (rand() % 61); tempy = 2 + (rand() % 4);
						for (j = 1; j <= i; j++)
						{
							if (starx[j] == tempx && stary[j] == tempy)
							{
								setcolor(6, 0);
								c++;
							}
						}
						if (c == 0) {
							draw_star(starx[i] = tempx, stary[i] = tempy);
							setcolor(6, 0);
						}
						else re--;
						c = 0;
					}
				}
				draw_bullet(bx[i], --by[i]);
				setcolor(2, 4);
				show_score(score);
			}
			else if (by[i] == 0)
			{
				setcolor(7, 0);
				erase_bullet(bx[i], by[i]);
				setcolor(2, 4);
			}
		}
	} while (ch != 'x');
	return 0;
}
