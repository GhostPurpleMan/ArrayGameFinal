#pragma once

struct Point
{

	// by default struct makes a member variables puliblc
	/// if the variables are public theres no need for m_(member variable/function

	int x;
	int y;



	// constructor
	Point()
		: x(0)
		, y(0)
	{

	}
	Point(int x, int y)
	{
		this->y = y;
		this->x = x;
	}
};
