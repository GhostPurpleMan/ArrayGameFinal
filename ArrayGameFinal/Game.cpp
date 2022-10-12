#include "Game.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;


constexpr int kOpenDoorColor = 10;
constexpr int kCloseDoorColor = 12;
constexpr int kRegularColor = 7;


Game::Game(): m_isGameOver(false)
{

}
Game::~Game()
{

}
bool Game::Load()
{
    return m_level.Load("level1.txt", m_player.GetXPositionPointer(), m_player.GetYPositionPointer());

}
void Game::Run()
{
    Draw();
    m_isGameOver = Update();

    if (m_isGameOver)
    {
        Draw();
    }
}
bool Game::IsGameOver()
{
    return m_isGameOver;
}
bool Game::Update()
{
	char input = _getch();


	int newPlayerX = m_player.GetXPosition();
	int newPlayerY = m_player.GetYPosition();


	switch (input)
	{
	case 'w':
	case 'W':
	{
		newPlayerY--;
		break;
	}

	case 's':
	case'S':
	{
		newPlayerY++;
		break;
	}
	case'a':
	case'A':
	{
		newPlayerX--;
		break;
	}
	case'd':
	case'D':
	{
		newPlayerX++;
		break;
	}
	default:
	{
		break;
	}
	}

	if (m_level.isSpace(newPlayerX, newPlayerX))
	{
		m_player.setPosition(newPlayerX, newPlayerY);
	}
	else if (m_level.isKey(newPlayerX, newPlayerY))
	{
		m_player.PickupKey();
		m_level.PickUpKey(newPlayerX,newPlayerY);
		//PlayKeyPickupSound();
		m_player.setPosition(newPlayerX, newPlayerY);
	}
	else if (m_level.isDoor(newPlayerX, newPlayerY && m_player.HasKey()))
	{
		m_level.OpenDoor(newPlayerX, newPlayerY);
		m_player.UseKey();
		//PlayDoorOpenSound();
		m_player.setPosition(newPlayerX, newPlayerY);
	}
	else if(m_level.isDoor(newPlayerX, newPlayerY) && !m_player.HasKey())
	{
		//PlayDoorClosedSound();
	}
	else if (m_level.isGoal(newPlayerX, newPlayerY))
	{
		m_level.OpenDoor(newPlayerX, newPlayerY);
		m_player.setPosition(newPlayerX, newPlayerY);
		return true;
	}
	else { return false;  }
}
void Game::Draw()
{
	system("cls");
	for (int y = 0; y < m_level.getHeight(); y++)
	{
		for (int x = 0; x < m_level.getWidth(); x++)
		{

			if (m_player.GetXPosition() == x && m_player.GetYPosition() == y)
			{
				m_player.Draw();
			}
			else
			{

				HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

				if (m_level.isDoor(x, y))
				{
					if (m_player.HasKey())
					{
						
					SetConsoleTextAttribute(console, kOpenDoorColor);

					}
					else
					{
					SetConsoleTextAttribute(console, kCloseDoorColor);

					}
				}
				else
				{
					SetConsoleTextAttribute(console, kRegularColor);

				}
				m_level.Draw(x, y);
			}
		}
		cout << endl;
	}
}