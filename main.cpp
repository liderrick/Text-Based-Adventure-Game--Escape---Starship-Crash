/**************************************************************************************************************
** Program name: Final Project
** Author: Derrick Li
** Date: Mar. 21, 2017
** Description:
** The program is a text-based adventure game titled "ESCAPE: STARSHIP CRASH!" The objective of the game is to
** escape the Starship before time runs out. The player travels through various rooms and interact with items
** and events via text-based menus and inputs to achieve their objective.
***************************************************************************************************************/

#include "Game.hpp"
#include "Space.hpp"
#include "PrisonerCell.hpp"
#include "Junction.hpp"
#include "SurveillanceRoom.hpp"
#include "WeaponsLocker.hpp"
#include "CargoStorage.hpp"
#include "BeastCell.hpp"
#include "menu.hpp"

#include <iostream>

using std::endl;
using std::cout;
using std::cin;

int main()
{
	char playAgain = 'N';
	bool playedAtLeastOnce = false;

	int userChoice = 0;

	do
	{
		gameIntro();
		userChoice = mainMenu();

		if (userChoice == 1)
		{
			Game game;
			playAgain = game.playGame();
			playedAtLeastOnce = true;
		}
		else
		{
			if (!playedAtLeastOnce)
			{
				cout << endl << "Goodbye." << endl;
				pressEnterToContinue();
			}
		}

	} while (playAgain == 'Y' && userChoice != 9);

	if (playedAtLeastOnce)
	{
		cout << endl << "Thank you for playing!" << endl;
		pressEnterToContinue();
	}

	return 0;
}