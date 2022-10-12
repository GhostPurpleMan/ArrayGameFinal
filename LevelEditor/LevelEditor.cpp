// LevelEditor.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <conio.h>
#include <Windows.h>	
#include <fstream>



using namespace std;




constexpr char kCursor = '_';


constexpr char kTopRightBorder = 187;
constexpr char kTopLeftBorder = 201;
constexpr char kBottonRightBorder = 188;
constexpr char kBottomLeftBorder = 200;
constexpr char kHorizontalBorder = 205;
constexpr char kVerticalBorder = 186;

// const called arrow input
constexpr int kArrowInput = 224;
// individual arrows
constexpr int kLeftArrowInput = 75;
constexpr int kRightArrowInput = 77;
constexpr int kUpArrowInput = 72;
constexpr int kDownArrowInput = 80;

constexpr int kEscape = 27;


int	GetIndexFromXY(int x, int y, int width)
{
	return x + y * width;
}
void DisplayTopBorder(int width)
{
	cout << kTopLeftBorder;
	for (int i = 0; i < width; i++)
	{
		cout << kHorizontalBorder;
	}
	cout << kTopRightBorder << endl;

}
void DisplayBottomBorder(int width)
{
	cout << kBottomLeftBorder;
	for (int i = 0; i < width; i++)
	{
		cout << kHorizontalBorder;
	}
	cout << kBottonRightBorder;

}
void DisplayLeftBorder()
{
	cout << kVerticalBorder;
}
void DisplayRightBorder()
{
	cout << kVerticalBorder << endl;
}
void DisplayLevel(char* pLevel, int width, int height, int cursorX, int cursorY)
{
	DisplayTopBorder(width);

	for (int y = 0; y < height; y++)
	{
		DisplayLeftBorder();

		for (int x = 0; x < width; x++)
		{
			if (cursorX == x && cursorY == y)
			{
				cout << kCursor;
			}
			else
			{
				int index = GetIndexFromXY(x, y, width);
				cout << pLevel[index];


			}

		}
		DisplayRightBorder();
	}
	DisplayBottomBorder(width);



}
void GetLevelDimesions(int& width, int& height)
{
	cout << "enter the width of the level:";
	cin >> width;
	cout << "enter the level height:";
	cin >> height;

}
bool EditLevel(char* plevel, int& cursorX, int& cursorY, int levelWidth, int levelHeight)
{
	int newCursorX = cursorX;
	int newCursorY = cursorY;

	int intInput = _getch();

	if (intInput == kArrowInput)
	{
		int arrowInput = _getch();

		switch (arrowInput)
		{
		case 'a':
		case kLeftArrowInput:
		{
			cout << arrowInput << endl;
			newCursorX--;
			break;
		}
		case 'd':
		case kRightArrowInput:
		{
			cout << arrowInput << endl;
			newCursorX++;
			break;
		}
		case 'w':
		case kUpArrowInput:
		{
			cout << arrowInput << endl;
			newCursorY--;
			break;
		}
		case 's':
		case kDownArrowInput:
		{
			cout << arrowInput << endl;
			newCursorY++;
			break;
		}
		}
		if (newCursorX < 0)
			newCursorX = 0;
		else if (newCursorX == levelWidth)
			newCursorX = levelWidth - 1;
		if (newCursorY < 0)
			newCursorY = 0;
		else if (newCursorY == levelHeight)
			newCursorY = levelHeight - 1;

		cursorX = newCursorX;
		cursorY = newCursorY;
	}
	else if (intInput == kEscape)
	{
		return true;
		cout << intInput << endl;

	}
	else
	{
		int index = GetIndexFromXY(newCursorX, newCursorY, levelWidth);
		plevel[index] = (char)intInput;
	}
	return false;

}
void SaveLevel(char* plevel, int width, int height)
{
	cout << "pick a name for the level (eg: Level1.txt): ";
	string LevelName;
	cin >> LevelName;

	LevelName.insert(0,"../");
	ofstream LevelFile;
	LevelFile.open(LevelName);
	if(!LevelFile)
	{
		cout << "Couldn't open level file " << LevelName << endl;

	}
	else
	{
		LevelFile << width << endl;
		LevelFile << height << endl;
		LevelFile.write(plevel,width * height);
		if (!LevelFile)
		{
			cout << "write failed" << endl;

		}
		LevelFile.close();

	}
	
}
int main()
{

	int levelWidth;
	int levelHeight;

	GetLevelDimesions(levelWidth, levelHeight);

	long int varMult = levelWidth * levelHeight;

	char* plevel = new char [varMult];

	for (int i = 0; i < (varMult); i++)
	{
		plevel[i] = ' ';
	}


	int cursorX = 0;
	int cursorY = 0;
	bool doneEditing = false;

	while (!doneEditing)
	{
		system("cls");   
		DisplayLevel(plevel, levelWidth, levelHeight, cursorX, cursorY);

		doneEditing = EditLevel(plevel, cursorX, cursorY, levelWidth, levelHeight);
	}
	system("cls");
	DisplayLevel(plevel, levelWidth, levelHeight, -1, -1);

	SaveLevel(plevel, levelWidth, levelHeight);

	delete[] plevel;
	//free(plevel);
	plevel = nullptr;

}