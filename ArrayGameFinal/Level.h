#pragma once
#include <string>



class Level
{
	char* m_pLevelData;
	int m_height;
	int m_width;


public:
	Level();
	~Level();

	bool Load(std::string LevelName, int* playerX, int* playery);
	void Draw(int x, int y);
	bool isSpace(int x, int y);
	bool isDoor(int x, int y);
	bool isKey(int x, int y);
	bool isGoal(int x, int y);

	void PickUpKey(int x, int y);
	void OpenDoor(int x, int y);
	
	int getHeight() { return m_height; }
	int getWidth() { return m_width; }

private:
	bool Convert(int* playerX, int* playerY);
	int GetIndexFromCordinates(int x, int y);





};