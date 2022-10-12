//#include <windows.h>

#include <iostream>
#include "Game.h"
using namespace std;

// void PlayDoorOpenSound()
// {
// 	Beep(1397, 200);
// }
// void PlayKeyPickupSound()
// {
// 	Beep(1568, 200);
// }
// void PlayDoorClosedSound()
// {
// 	Beep(500, 75);
// 	Beep(500, 75);
// }
// void PlayWinSound()

// {
// 	Beep(1568, 200);
// 	Beep(1568, 200);
// 	Beep(1568, 200);
// 	Beep(1245, 1000);
// 	Beep(1568, 200);
// 	Beep(1568, 200);
// 	Beep(1568, 200);
// 	Beep(1245, 1000);
// }
int main()
{
	Game myGame;
	if (myGame.Load())
	{
		while(!myGame.IsGameOver())
		{
			myGame.Run();
			//PlayWinSound();
		}
	}
	else
	{
		cout << "game not loaded" << endl;
	}

}