#include <iostream>
#include <time.h>
#include <conio.h>
#include <Windows.h>

using namespace std;

// enum for movement
enum eDir { STOP = 0, LEFT = 1, UPLEFT = 2, DOWNLEFT = 3, RIGHT = 4, UPRIGHT = 5, DOWNRIGHT = 6};

// Clear Screen
void clrscr()
{
	CONSOLE_SCREEN_BUFFER_INFO	csbiInfo;
	HANDLE	hConsoleOut;
	COORD	Home = { 0,0 };
	DWORD	dummy;

	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOut, &csbiInfo);

	FillConsoleOutputCharacter(hConsoleOut, ' ', csbiInfo.dwSize.X * csbiInfo.dwSize.Y, Home, &dummy);
	csbiInfo.dwCursorPosition.X = 0;
	csbiInfo.dwCursorPosition.Y = 0;
	SetConsoleCursorPosition(hConsoleOut, csbiInfo.dwCursorPosition);
}

// Change theme color
void TextColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Hide Cursor
void Nocursortype()
{
	CONSOLE_CURSOR_INFO Info;
	Info.bVisible = FALSE;
	Info.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}



// Create Ball
class cBall
{
private:
	int x, y;
	int originalX, originalY;
	eDir direction;
public:

	cBall(int posX, int posY)
	{
		originalX = posX;
		originalY = posY;
		x = posX; y = posY;
		direction = STOP;
	}

	// Reset location 
	void Reset()
	{
		x = originalX; y = originalY;
		direction = STOP;
	}

	// Setter
	void changeDirection(eDir d)
	{
		direction = d;
	}
	void randomDirection()
	{
		direction = (eDir)((rand() % 6) + 1);
	}

	// Getter
	inline int getX() { return x; }
	inline int getY() { return y; }
	inline eDir getDirection() { return direction; }

	// Set movement for ball
	void Move()
	{
		switch (direction)
		{
		case STOP:
			break;
		case LEFT:
			x--;
			break;
		case RIGHT:
			x++;
			break;
		case UPLEFT:
			x--; y--;
			break;
		case DOWNLEFT:
			x--; y++;
			break;
		case UPRIGHT:
			x++; y--;
			break;
		case DOWNRIGHT:
			x++; y++;
			break;
		default:
			break;
		}
	}
};



// Create Players 
class cPLAYER
{
private:
	int x, y;		// Player1's location
	int originalX, originalY;
	int x1, y1;		// Player2's location
public:
	cPLAYER()
	{
		x = y = 0;
		x1 = y1 = 0;
	}
	cPLAYER(int posX, int posY) : cPLAYER()
	{
		originalX = posX;
		originalY = posY;
		x = posX;
		y = posY;
		x1 = posX;
		y1 = posY;
	}


	// P1
	inline void Reset() { x = originalX; y = originalY; }		// Back to beginning 
	inline int getX() { return x; }								// Getter
	inline int getY() { return y; }								// Getter
	inline int moveUp() { return y--; }							// Move Up
	inline int moveDown() { return y++; }						// Move Down


	// P2
	inline void Reset1() { x1 = originalX; y1 = originalY; }	// Back to beginning 
	inline int getX1() { return x1; }							// Getter
	inline int getY1() { return y1; }							// Getter
	inline int moveUp1() { return y1--; }						// Move Up
	inline int moveDown1() { return y1++; }						// Move Down

};



// Manager : Display, Control and Set Rules
class cGameManger
{
private:
	int width, height;		// Console's Width and Height
	int score1, score2;		// Score
	bool quit;				// quit game
	cBall * ball;
	cPLAYER *player1;
	cPLAYER *player2;
public:
	cGameManger(int w, int h)
	{
		srand(time(NULL));
		quit = false;								// keep going
		score1 = score2 = 0;						// score = 0 at the beginning
		width = w; height = h;
		ball = new cBall(w / 2, h / 2);				// In the middle of console's screen
		player1 = new cPLAYER(1, h / 2 - 3);		// Oxy : A(1, y/2)	
		player2 = new cPLAYER(w - 2, h / 2 - 3);	// Oxy : B(x/2, y/2 - █ * 3)
	}
	~cGameManger()
	{
		delete ball, player1, player2;				
	}
	void ScoreUp(cPLAYER * player)
	{
		if (player == player1)
			score1++;
		else if (player == player2)
			score2++;

		// score++, reset locations of players and ball
		ball->Reset();
		player1->Reset();
		player2->Reset1();
	}
	void Draw()
	{
		// fence : top
		for (int i = 0; i < width + 2; i++)
			putchar(220);
		cout << endl;

		for (int i = 0; i <= height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				int ballx = ball->getX();
				int bally = ball->getY();
				int player1x = player1->getX();
				int player2x = player2->getX1();
				int player1y = player1->getY();
				int player2y = player2->getY1();

				// fence : bottom left
				if (j == 0)
					putchar(220);

				if (ballx == j && bally == i)
					cout << "O"; //ball
				else if (player1x == j && player1y == i)
					putchar(219); //player1
				else if (player2x == j && player2y == i)
					putchar(219); //player2

				else if (player1x == j && player1y + 1 == i)
					putchar(219); //player1
				else if (player1x == j && player1y + 2 == i)
					putchar(219); //player1
				else if (player1x == j && player1y + 3 == i)
					putchar(219); //player1

				else if (player2x == j && player2y + 1 == i)
					putchar(219); //player2
				else if (player2x == j && player2y + 2 == i)
					putchar(219); //player2
				else if (player2x == j && player2y + 3 == i)
					putchar(219); //player2
				else
					cout << " ";
				
				// fence : bottom right
				if (j == width - 1)
					putchar(220);
			}
			cout << endl;
		}

		// fence : top
		for (int i = 0; i < width + 2; i++)
			putchar(220);
		cout << endl;

		cout << "Score 1: " << score1 << endl << "Score 2: " << score2 << endl;
	}
	void Input()
	{
		// In while()... this will work constantly
		ball->Move();

		// Get location for players and ball
		int ballx = ball->getX();
		int bally = ball->getY();
		int player1x = player1->getX();
		int player2x = player2->getX1();
		int player1y = player1->getY();
		int player2y = player2->getY1();

		// _kbhit() : keyboard hit
		if (_kbhit())
		{
			char current = _getch();

			// Player 2
			if (current == 'i' || current == 'I') {
				player2->moveUp1();
			}
			else if (current == 'k' || current == 'K') {
				player2->moveDown1();
			}


			// Player 1
			if (current == 'w' || current == 'W') {
				player1->moveUp();
			}
			else if (current == 's' || current == 'S') {
				player1->moveDown();
			}


			// Ball : hit P1, hit P2 and bottom (top) fence
			if (ball->getDirection() == STOP)
				ball->randomDirection();

			// press "q" to quit
			if (current == 'q')
				quit = true;
		}
	}
	void Logic()
	{
		// Get location for players and ball
		int ballx = ball->getX();
		int bally = ball->getY();
		int player1x = player1->getX();
		int player2x = player2->getX1();
		int player1y = player1->getY();
		int player2y = player2->getY1();

		// hit P1
		for (int i = 0; i < 4; i++)
			if (ballx == player1x + 1)
				if (bally == player1y + i)
					ball->changeDirection((eDir)((rand() % 3) + 4));

		// hit P2
		for (int i = 0; i < 4; i++)
			if (ballx == player2x - 1)
				if (bally == player2y + i)
					ball->changeDirection((eDir)((rand() % 3) + 1));

		// hit bottom wall
		if (bally == height - 1)
			ball->changeDirection(ball->getDirection() == DOWNRIGHT ? UPRIGHT : UPLEFT);
		// hit top wall
		if (bally == 0)
			ball->changeDirection(ball->getDirection() == UPRIGHT ? DOWNRIGHT : DOWNLEFT);



		// out of right wall <=> P2 lost
		if (ballx == width - 1)
			ScoreUp(player1);
		// out of left wall <=> P1 lost
		if (ballx == 0)
			ScoreUp(player2);

		// Series BO5 : Best of five
		if (cGameManger::score1 == 3) {
			cout << "Player 1 win !!";
			system("pause");
		}
		else if (cGameManger::score2 == 3) {
			cout << "Player 2 win !!";
			system("pause");
		}
	}
	void Run()
	{
		Nocursortype();

		// unlimited loop
		while (!quit)
		{
			system("cls");
			Draw();
			Input();
			Logic();
		}
	}
};



// Run game
int main()
{
	TextColor(3);
	// Set consoleWidth and consoleHeight for main game
	cGameManger c(40, 20);
	c.Run();
	return 0;
}