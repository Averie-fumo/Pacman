#ifndef _INC_EKU_IO_CONCOL
#define _INC_EKU_IO_CONCOL

/*Header file to color text and background in windows console applications
Global variables - textcol,backcol,deftextcol,defbackcol,colorprotect*/

#include<windows.h>
#include<iosfwd>

namespace eku
{

#ifndef CONCOL
#define CONCOL
	enum concol
	{
		black = 0,
		dark_blue = 1,
		dark_green = 2,
		dark_aqua, dark_cyan = 3,
		dark_red = 4,
		dark_purple = 5, dark_pink = 5, dark_magenta = 5,
		dark_yellow = 6,
		dark_white = 7,
		gray = 8,
		blue = 9,
		green = 10,
		aqua = 11, cyan = 11,
		red = 12,
		purple = 13, pink = 13, magenta = 13,
		yellow = 14,
		white = 15
	};
#endif //CONCOL

	HANDLE std_con_out;
	//Standard Output Handle
	bool colorprotect = false;
	//If colorprotect is true, background and text colors will never be the same
	concol textcol, backcol, deftextcol, defbackcol;
	/*textcol - current text color
	backcol - current back color
	deftextcol - original text color
	defbackcol - original back color*/

	inline void update_colors()
	{
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(std_con_out, &csbi);
		textcol = concol(csbi.wAttributes & 15);
		backcol = concol((csbi.wAttributes & 0xf0) >> 4);
	}

	inline void setcolor(concol textcolor, concol backcolor)
	{
		if (colorprotect && textcolor == backcolor)return;
		textcol = textcolor;backcol = backcolor;
		unsigned short wAttributes = ((unsigned int)backcol << 4) | (unsigned int)textcol;
		SetConsoleTextAttribute(std_con_out, wAttributes);
	}

	inline void settextcolor(concol textcolor)
	{
		if (colorprotect && textcolor == backcol)return;
		textcol = textcolor;
		unsigned short wAttributes = ((unsigned int)backcol << 4) | (unsigned int)textcol;
		SetConsoleTextAttribute(std_con_out, wAttributes);
	}

	inline void setbackcolor(concol backcolor)
	{
		if (colorprotect && textcol == backcolor)return;
		backcol = backcolor;
		unsigned short wAttributes = ((unsigned int)backcol << 4) | (unsigned int)textcol;
		SetConsoleTextAttribute(std_con_out, wAttributes);
	}

	inline void concolinit()
	{
		std_con_out = GetStdHandle(STD_OUTPUT_HANDLE);
		update_colors();
		deftextcol = textcol;defbackcol = backcol;
	}

	template<class elem, class traits>
	inline std::basic_ostream<elem, traits>& operator<<(std::basic_ostream<elem, traits>& os, concol col)
	{
		os.flush();settextcolor(col);return os;
	}

	template<class elem, class traits>
	inline std::basic_istream<elem, traits>& operator>>(std::basic_istream<elem, traits>& is, concol col)
	{
		std::basic_ostream<elem, traits>* p = is.tie();
		if (p != NULL)p->flush();
		settextcolor(col);
		return is;
	}

}

#endif	 


#include<iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>
#include <cstdlib>
using namespace eku;
using namespace std;

void gotoxy(int x, int y)
{
	COORD coordinates;     // coordinates is declared as COORD
	coordinates.X = x;     // defining x-axis
	coordinates.Y = y;     //defining  y-axis
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}
void labels(int& life, int& dots, int& level)
{
	gotoxy(17, 0);
	cout << yellow << "Life Count: " << life;
	gotoxy(33, 0);
	cout << white << "Dots eaten: " << dots;
	gotoxy(50, 0);
	cout << green << "Level: " << level;

}
void movePacMan(char a[20][35], int& X, int& Y, int& dots, int& life, int& level)
{
	while (true)
	{
		labels(life, dots, level);
		{

			if (_kbhit())
			{
				char key = _getch();


				cout << red;
				if (key == 'w')
				{
					if (Y == 2 || a[Y - 2][X] == '#')
						continue;

					gotoxy(X, Y);
					if (a[Y - 2][X] == '.')
					{
						dots++;
					}
					else if (a[Y - 2][X] == 'O')
					{
						life++;
					}
					a[Y - 2][X] = ' ';
					cout << ' ';

					Y--;
					gotoxy(X, Y);
					cout << red << "P";


				}

				else if (key == 's')
				{
					if (Y == 19 || a[Y][X] == '#')
						continue;

					gotoxy(X, Y);
					if (a[Y][X] == '.')
					{
						dots++;
					}
					else if (a[Y][X] == 'O')
					{
						life++;
					}
					a[Y][X] = ' ';
					cout << ' ';

					Y++;
					gotoxy(X, Y);
					cout << red << "P";


				}

				else if (key == 'a')
				{

					if (X == 1 || a[Y - 1][X - 1] == '#')
						continue;

					gotoxy(X, Y);
					if (a[Y - 1][X - 1] == '.')
					{
						dots++;
					}
					else if (a[Y - 1][X - 1] == 'O')
					{
						life++;
					}
					a[Y - 1][X - 1] = ' ';
					cout << ' ';

					X--;
					gotoxy(X, Y);
					cout << red << "P";
				}

				else if (key == 'd')
				{
					if (X == 33 || a[Y-1][X+1] == '#')
						continue;
					cout << red;
					gotoxy(X, Y);
					if (a[Y-1][X+1] == '.')
					{
						dots++;
					}
					else if (a[Y-1][X+1] == 'O')
					{
						life++;
					}
					a[Y - 1][X + 1] = ' ';
					cout << ' ';

					X++;
					gotoxy(X, Y);
					cout << "P";
				}

			}

			break;
		}


	}


}

void right(char a[20][35], int& X, int& Y, int& x1, int& y1, int& life)
{

	gotoxy(x1, y1);
	Sleep(250);
	if (a[y1][x1] == '.')
	{
		cout << blue << '.';
	}
	else if (a[y1][x1] == 'O')
	{
		cout << dark_blue << 'O';
	}
	cout << ' ';
	x1++;
	while (x1 < 1)
		x1++;
	while (x1 > 33)
		x1--;

	gotoxy(x1, y1);
	cout << yellow << 'C';
	if (x1 == X && y1 == Y)
	{
		X = 33;
		Y = 19;
		gotoxy(X, Y);
		cout << red << 'P';
		life--;
	}

}
void right1(char a[20][35], int& X, int& Y, int& x2, int& y2, int& life)
{

	gotoxy(x2, y2);
	Sleep(250);
	if (a[y2][x2] == '.')
	{
		cout << blue << '.';
	}
	else if (a[y2][x2] == 'O')
	{
		cout << dark_blue << 'O';
	}
	cout << ' ';
	x2++;
	while (x2 < 1)
		x2++;
	while (x2 > 33)
		x2--;
	gotoxy(x2, y2);
	cout << purple << 'C';
	if (x2 == X && y2 == Y)
	{
		X = 33;
		Y = 19;
		gotoxy(X, Y);
		cout << red << 'P';
		life--;
	}

}
void left(char a[20][35], int& X, int& Y, int& x1, int& y1, int& life)
{
	gotoxy(x1, y1);
	Sleep(250);
	if (a[y1 - 1][x1 - 1] == '.')
	{
		cout << blue << '.';
	}
	else if (a[y1 - 1][x1 - 1] == 'O')
	{
		cout << dark_blue << 'O';
	}
	cout << ' ';
	
	x1--;
	while (x1 < 1)
		x1++;
	while (x1 > 33)
		x1--;
	gotoxy(x1, y1);

	cout << yellow << 'C';

	if (x1 == X && y1 == Y)

	{
		X = 33;
		Y = 19;
		gotoxy(X, Y);
		cout << red << 'P';
		life--;
	}


}
void left1(char a[20][35], int& X, int& Y, int& x2, int& y2, int& life)
{

	gotoxy(x2, y2);
	Sleep(250);
	if (a[y2 - 1][x2 - 1] == '.')
	{
		cout << blue << '.';
	}
	else if (a[y2 - 1][x2 - 1] == 'O')
	{
		cout << dark_blue << 'O';
	}
	cout << ' ';
	x2--;
	while (x2 < 1)
		x2++;
	while (x2 > 33)
		x2--;
	gotoxy(x2, y2);

	cout << purple << 'C';

	if (x2 == X && y2 == Y)

	{
		X = 33;
		Y = 19;
		gotoxy(X, Y);
		cout << red << 'P';
		life--;
	}
}
void up(char a[20][35], int& X, int& Y, int& x1, int& y1, int& life)
{

	gotoxy(x1, y1);
	Sleep(250);
	if (a[y1 - 2][x1] == '.')
	{
		cout << blue << '.';
	}
	else if (a[y1 - 2][x1] == 'O')
	{
		cout << dark_blue << 'O';
	}
	cout << ' ';
	while (y1 < 2)
		y1++;
	while (y1 > 19)
		y1--;

	y1--;
	gotoxy(x1, y1);
	cout << yellow << 'C';
	if (x1 == X && y1 == Y)
	{
		X = 33;
		Y = 19;
		gotoxy(X, Y);
		cout << red << 'P';
		life--;

	}
}
void up1(char a[20][35], int& X, int& Y, int& x2, int& y2, int& life)
{
	gotoxy(x2, y2);
	Sleep(250);
	if (a[y2 - 2][x2] == '.')
	{
		cout << blue << '.';
	}
	else if (a[y2 - 2][x2] == 'O')
	{
		cout << dark_blue << 'O';
	}
	cout << ' ';

	y2--;
	while (y2 < 2)
		y2++;
	while (y2 > 19)
		y2--;
	gotoxy(x2, y2);
	cout << purple << 'C';
	if (x2 == X && y2 == Y)
	{
		X = 33;
		Y = 19;
		gotoxy(X, Y);
		cout << red << 'P';
		life--;

	}
}

void down(char a[20][35], int& X, int& Y, int& x1, int& y1, int& life)
{

	gotoxy(x1, y1);
	Sleep(250);

	if (a[y1][x1] == '.')
	{
		cout << blue << '.';
	}
	else if (a[y1][x1] == 'O')
	{
		cout << dark_blue << 'O';
	}
	cout << ' ';
	y1++;
	while (y1 <= 2)
		y1++;
	while (y1 > 19)
		y1--;

	gotoxy(x1, y1);
	cout << yellow << 'C';
	if (x1 == X && y1 == Y)
	{
		X = 33;
		Y = 19;
		gotoxy(X, Y);
		cout << red << 'P';
		life--;
	}
}
void down1(char a[20][35], int& X, int& Y, int& x2, int& y2, int& life)
{
	gotoxy(x2, y2);
	Sleep(250);

	if (a[y2][x2] == '.')
	{
		cout << blue << '.';
	}
	else if (a[y2][x2] == 'O')
	{
		cout << dark_blue << 'O';
	}
	cout << ' ';

	y2++;
	while (y2 <= 2)
		y2++;
	while (y2 > 19)
		y2--;
	gotoxy(x2, y2);
	cout << purple << 'C';
	if (x2 == X && y2 == Y)
	{
		X = 33;
		Y = 19;
		gotoxy(X, Y);
		cout << red << 'P';
		life--;
	}
}

void ghost(char a[20][35], int& X, int& Y, int& x1, int& y1, int& life)
{
	while (true)
	{
		{

			gotoxy(x1, y1);
			if (Y < y1)
			{
				if (a[y1 - 2][x1] != '#')
				{
					up(a, X, Y, x1, y1, life);

					break;
				}

			}
			else if (Y > y1)
			{
				if (a[y1][x1] != '#')
				{
					down(a, X, Y, x1, y1, life);
					break;
				}

			}

			if (X < x1)
			{
				if (a[y1 - 1][x1 - 1] != '#')
				{
					left(a, X, Y, x1, y1, life);
					break;
				}
			}

			
			else if (X > x1)
			{
				if (a[y1 - 1][x1 + 1] != '#')
				{
					right(a, X, Y, x1, y1, life);
					break;
				}


			}
			if (a[y1 - 2][x1] == '#' && a[y1 - 1][x1 + 1] != '#')
			{
				right(a, X, Y, x1, y1, life);
				break;
			}
			if (a[y1 - 2][x1] == '#' && a[y1 - 1][x1 - 1] != '#')
			{
				left(a, X, Y, x1, y1, life);
				break;
			}
			if (a[y1 - 2][x1] == '#' && a[y1 ][x1] != '#')
			{
				down(a, X, Y, x1, y1, life);
				break;
			}
			if (a[y1 - 1][x1 - 1] == '#' && a[y1 ][x1] != '#')
			{
				down(a, X, Y, x1, y1, life);
				break;
			}
			if (a[y1 - 1][x1 - 1] == '#' && a[y1 - 2][x1] != '#')
			{
				up(a, X, Y, x1, y1, life);

				break;
			}
			if (a[y1 - 1][x1 - 1] == '#' && a[y1-1][x1 + 1] != '#')
			{
				right(a, X, Y, x1, y1, life);
				break;
			}
			if (a[y1][x1] == '#' && a[y1 - 2][x1] != '#')
			{
				up(a, X, Y, x1, y1, life);

				break;
			}
			if (a[y1][x1] == '#' && a[y1-1][x1 + 1] != '#')
			{
				right(a, X, Y, x1, y1, life);
				break;
			}
			if (a[y1][x1] == '#' && a[y1 - 1][x1 - 1] != '#')
			{
				left(a, X, Y, x1, y1, life);
				break;
			}
			if (a[y1-1][x1 + 1] == '#' && a[y1 - 1][x1 - 1] != '#')
			{
				left(a, X, Y, x1, y1, life);
				break;
			}
			if (a[y1-1][x1 + 1] == '#' && a[y1 ][x1] != '#')
			{
				down(a, X, Y, x1, y1, life);
				break;
			}
			if (a[y1-1][x1 + 1] == '#' && a[y1 - 2][x1] != '#')
			{
				up(a, X, Y, x1, y1, life);
				break;
			}
			if (a[y1-1][x1 + 1] == '#' && a[y1 - 2][x1] == '#' && a[y1][x1] != '#')
			{
				down(a, X, Y, x1, y1, life);
				break;
			}
			if (a[y1-1][x1 + 1] == '#' && a[y1][x1] == '#' && a[y1 - 2][x1] != '#')
			{
				up(a, X, Y, x1, y1, life);
				break;
			}
			if (a[y1-1][x1 + 1] == '#' && a[y1][x1] == '#' && a[y1 - 1][x1 - 1] != '#')
			{
				left(a, X, Y, x1, y1, life);
				break;
			}
			if (a[y1][x1] == '#' && a[y1][x1 + 1] == '#' &&  a[y1 - 1][x1 + 1] != '#')
			{
				right(a, X, Y, x1, y1, life);
				break;
			}
			if (a[y1 - 1][x1 + 1] == '#' && a[y1 - 1][x1 - 1] == '#' && a[y1][x1] != '#')
			{
				down(a, X, Y, x1, y1, life);
				break;

			}
			if (a[y1 - 2][x1] == '#' && a[y1 - 1][x1 - 1] == '#' && a[y1 - 1][x1 + 1] == '#')
			{
				down(a, X, Y, x1, y1, life);
				break;
			}

			break;
		}


	}
}
void ghost1(char a[20][35], int& X, int& Y, int& x2, int& y2, int& life)
{

	while (true)

	{

		gotoxy(x2, y2);
		if (Y < y2)
		{
			if (a[y2 - 2][x2] != '#')
			{
				up1(a, X, Y, x2, y2, life);

				break;
			}

		}

		else if (Y > y2)
		{
			if (a[y2][x2] != '#')
			{
				down1(a, X, Y, x2, y2, life);
				break;
			}

		}
	    if (X < x2)
		{
			if (a[y2 - 1][x2 - 1] != '#')
			{
				left1(a, X, Y, x2, y2, life);
				break;
			}
		}

		else if (X > x2)
		{
			if (a[y2-1][x2 + 1] != '#')
			{
				right1(a, X, Y, x2, y2, life);
				break;
			}


		}
		if (a[y2 - 2][x2] == '#' && a[y2-1][x2 + 1] != '#')
		{
			right1(a, X, Y, x2, y2, life);
			break;
		}
		if (a[y2 - 2][x2] == '#' && a[y2 - 1][x2 - 1] != '#')
		{
			left1(a, X, Y, x2, y2, life);
			break;
		}
		if (a[y2 - 2][x2] == '#' && a[y2 ][x2] != '#')
		{
			down1(a, X, Y, x2, y2, life);
			break;
		}
		if (a[y2 - 1][x2 - 1] == '#' && a[y2 ][x2] != '#')
		{
			down1(a, X, Y, x2, y2, life);
			break;
		}
		if (a[y2 - 1][x2 - 1] == '#' && a[y2 - 2][x2] != '#')
		{
			up1(a, X, Y, x2, y2, life);

			break;
		}
		if (a[y2 - 1][x2 - 1] == '#' && a[y2-1][x2 + 1] != '#')
		{
			right1(a, X, Y, x2, y2, life);
			break;
		}
		if (a[y2 - 1][x2 + 1] == '#' && a[y2 - 1][x2 - 1] != '#')
		{
			left1(a, X, Y, x2, y2, life);
			break;
		}
		if (a[y2 - 1][x2 + 1] == '#'&& a[y2][x2] != '#')
		{
			down1(a, X, Y, x2, y2, life);

			break;
		}
		if (a[y2 - 1][x2 + 1] == '#'&& a[y2 - 2][x2] != '#')
		{
			up1(a, X, Y, x2, y2, life);
			break;
		}

		if (a[y2][x2] == '#'&& a[y2 - 2][x2] != '#')
		{
			up1(a, X, Y, x2, y2, life);
			break;
		}
		if (a[y2][x2] == '#'&& a[y2 - 1][x2 + 1] != '#')
		{

			right1(a, X, Y, x2, y2, life);
			break;
		}
		if (a[y2][x2] == '#'&& a[y2 - 1][x2 - 1] != '#')
		{
			left1(a, X, Y, x2, y2, life);
		
			break;
		}
		
		if (a[y2-1][x2 + 1] == '#' && a[y2 - 2][x2] == '#' && a[y2][x2] != '#')
		{
			down1(a, X, Y, x2, y2, life);
			break;
		}
		if (a[y2-1][x2 + 1] == '#' && a[y2][x2] == '#' && a[y2 - 2][x2] != '#')
		{
			up1(a, X, Y, x2, y2, life);
			break;
		}
		if (a[y2-1][x2 + 1] == '#' && a[y2][x2] == '#' && a[y2 - 1][x2 - 1] != '#')
		{
			left1(a, X, Y, x2, y2, life);
			break;
		}

		if (a[y2 - 1][x2 + 1] == '#' && a[y2 - 1][x2 - 1] == '#' && a[y2][x2] != '#')
		{
			down1(a, X, Y, x2, y2, life);
			break;

		}


		if (a[y2][x2] == '#' && a[y2 -2][x2] == '#' && a[y2 - 1][x2 + 1] != '#')
		{
			right1(a, X, Y, x2, y2, life);
			break;
		}
		if (a[y2 - 2][x2] == '#' && a[y2 - 1][x2 - 1] == '#' && a[y2 - 1][x2 + 1] == '#')
		{
			down1(a, X, Y, x2, y2, life);
			break;
		}
		break;
	}


}
int main()
{
	concolinit();
	srand((unsigned)time(NULL));

	int i, j, k, x, y, z, n = 20, count = 0;
	int wid = 33;


	int life = 3, c = 1, steps = 0, level = 1, dots = 0;
	char a[20][35];

	while (c < 5 && life > 0)
	{
		int X = 33, Y = 19;

		int x1 = 1, y1 = 2;
		int  x2 = 33, y2 = 2;

		for (x = 1; x < n - 1; x++)
		{
			for (y = 1; y < 34; y++)
			{
				j = rand() % 45 + 1;
				k = rand() % 45 + 1;

				if (j == 4)
				{
					a[x][y] = '#';
					a[x][y + 1] = '#';
					a[x][y - 1] = '#';
					y++;
				}
				else if (j == 6)
				{
					a[x][y] = '#';
					a[x][y + 1] = '#';
					a[x][y - 1] = '#';
					
					y++;
				}
				else if (j == 3 || j == 2 || j == 10 || j == 15 || j == 1)
				{
					a[x][y] = '.';
					count++;
				}
				else if ((k == 40 || k == 10) && (j == 20 || j == 30))
				{
					a[x][y] = 'O';
				}
				else
				{
					a[x][y] = ' ';
				}

			}
		}
		for (y = 1; y < 35; y++)
		{
			a[1][y] = ' ';
			a[n - 2][y] = ' ';

		}
		for (x = 1;x < n;x++)
		{
			a[x][0] = '|';
			a[x][34] = '|';
		}
		for (x = 1; x < n; x++)
		{
			a[x][1] = ' ';
			a[x][33] = ' ';
		}
		for (y = 0;y < 35;y++)
		{
			a[0][y] = '-';
			a[n - 1][y] = '-';
		}
		cout << endl;
		for (x = 0; x < n; x++)
		{
			for (y = 0; y < 35; y++)
			{
				cout << dark_blue;
				cout << a[x][y];
			}
			cout << endl;
		}



		labels(life, dots, level);

		cout << dark_yellow;
		gotoxy(50, 9);
		cout << "Press 'a','s','d','w' to command the Pac man P.";
		gotoxy(50, 10);
		cout << "Eat dots to go to the next level.";
		gotoxy(50, 11);
		cout << "Eat special dots 'O' to increase life.";
		gotoxy(50, 12);
		cout << "You have 3 lives.";
		gotoxy(50, 13);
		cout << "Pacman will return to starting position after losing one life.";
		cout << yellow;
		gotoxy(x1, y1);
		cout << "C";
		cout << purple;
		gotoxy(x2, y2);
		cout << "C";
		gotoxy(X, Y);
		cout << red << "P";
		Sleep(500);

		while (life > 0 && level == c)
		{
			while (true)
			{
				movePacMan(a, X, Y, dots, life, level);
				if (dots >= count - 10)
				{
					dots = 0;
					level++;

				}
				ghost(a, X, Y, x1, y1, life);
				if (x1 == x2 && y1 == y2)
				{
					x1 = x1 + 2; y1 = y1 + 2;
				}

				movePacMan(a, X, Y, dots, life, level);
				if (dots >= count - 10)
				{
					dots = 0;
					level++;

				}
				ghost1(a, X, Y, x2, y2, life);
				if (x2 == x1 && y1 == y2)
				{
					x2 = x2 - 2; y2 = y2 - 2;
				}
				if (life == 0)
				{
					gotoxy(9, 23);
					cout << white << "GAME END. YOU LOSE AWW :(";
					Sleep(3000);
					break;
				}
				else if (level > c)
				{

					gotoxy(9, 23);
					cout << white << "You passed the level " << level - 1;
					Sleep(3000);
					break;
				}

			}

		}
		c++;
		system("CLS");
	}

	gotoxy(9, 25);

	return 0;
}