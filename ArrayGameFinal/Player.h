#pragma once
#include "Point.h"



class Player
{

	// represent position of player
	Point m_Position;
	bool m_hasKey;


public:
	Player();

	~Player();


	/// for trivial functions ,code can be inplemented in header file
	int GetXPosition() { return m_Position.x; }
	int GetYPosition() { return m_Position.y; }

	int* GetXPositionPointer() { return &(m_Position.x); }
	int* GetYPositionPointer() { return &(m_Position.y); }

	void setPosition(int x, int y);

	bool HasKey();
	void PickupKey();
	void UseKey();
	void Draw();
};