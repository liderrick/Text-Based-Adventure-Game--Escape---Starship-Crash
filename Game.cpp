/**************************************************************************************************************
** Program name: Final Project
** Author: Derrick Li
** Date: Mar. 21, 2017
** Description:
** This class implementation file contains the member function definitions for the Game class.
***************************************************************************************************************/

#include "Game.hpp"
#include "menu.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <cctype>

using std::endl;
using std::cout;
using std::cin;
using std::string;
using std::vector;
using std::toupper;

const int INVENTORY_MAX_SIZE = 4;   //the maximum number of items the player can carry
const int STEPS_TO_FIRST_WARNING = 5;   //the number of steps to the first time warning
const int STEPS_TO_FINAL_WARNING = 50;   //the number of steps to the final time warning
const int MAX_NUMBER_OF_STEPS = 60;   //the maximum number of steps the player is allowed to play the game
									  //if player does not escape in time, they lose

/***************************************************************************************************************
** Description: Game class constructor. It builds the map of the rooms and initializes other data members,
** i.e. player's starting position to Prisoner Cell, befriendedBeast to false, maximum inventory size to the
** defined constant (default is 4), and stepsTaken to 0.
***************************************************************************************************************/
Game::Game()
{
	//Building the map
	pCell.setTop(&junct);   //Connecting PrisonerCell pCell
	
	junct.setTop(&cStorage);   //Connecting Junction junct
	junct.setBottom(&pCell);
	junct.setLeft(&wLocker);
	junct.setRight(&sRoom);

	wLocker.setRight(&junct);   //Connecting WeaponsLocker wLocker

	sRoom.setLeft(&junct);   //Connecting SurveillanceRoom sRoom

	cStorage.setTop(&bCell);   //Connecting CargoStorage cStorage
	cStorage.setBottom(&junct);

	bCell.setBottom(&cStorage);   //Connecting BeastCell bCell
	
	//Initialize other data members
	playerPosition = &pCell;   //initial starting position

	befriendedBeast = false;   //initially BEAST is not friend yet

	lifeStatus = 'a';   //'a' for alive

	inventoryMaxSize = INVENTORY_MAX_SIZE;

	stepsTaken = 0;
}

/***************************************************************************************************************
** Description: printInventory() function prints the inventory of the player to screen.  The function does not
** take in any arguments and does not have a return type.
***************************************************************************************************************/
void Game::printInventory()
{	
	cout << endl << "INVENTORY (Your Pockets):  ";

	if (inventory.size() != 0)
	{
		for (int i = 0; i < inventory.size(); i++)
		{
			cout << inventory.at(i) << "  ";
		}
	}
	else
	{
		cout << "<empty>";
	}

	cout << endl;
}

/***************************************************************************************************************
** Description: timeMechanism() function keeps track of the number of steps the player takes. It displays the
** warning messages to the player at the set time/steps. If the player reaches maximum allowable steps,
** the lifeStatus is set to 't'-- to indicate the player has ran out of time and has failed to escape, thereby
** losing the game. The function does not take in any arguments and does not have a return type.
***************************************************************************************************************/
void Game::timeMechanism()
{
	stepsTaken++;   //increment stepsTaken

	if (stepsTaken == MAX_NUMBER_OF_STEPS)   //if taken max number of steps, then out of time.
	{
		lifeStatus = 't';
	}
	else if (stepsTaken == STEPS_TO_FIRST_WARNING)   //first warning
	{
		cout << endl <<
			"-----------------------------------------------------------------------------" << endl <<
			"The INTERCOM goes off. A robotic voice says, \"HQ RECEIVED DISTRESS CALL. SUPPORT EN ROUTE.\"" << endl <<
			"Better hurry up if you want to escape! The cavalry has been notified." << endl;

		pressEnterToContinue();
	}
	else if (stepsTaken == STEPS_TO_FINAL_WARNING)   //final warning
	{
		cout << endl <<
			"-----------------------------------------------------------------------------" << endl <<
			"The INTERCOM goes off again. A robotic voice says, \"SUPPORT ARRIVING MOMENTARILY.\"" << endl <<
			"HURRY!" << endl;

		pressEnterToContinue();
	}

}

/***************************************************************************************************************
** Description: testLifeStatus() function evaluates the lifeStatus (bool) data member at the end of the game.
** An appropriate message is displayed to the user to indicate whether they have won, died, or ran out of time.
** The function does not take in any arguments and does not have a return type.
***************************************************************************************************************/
void Game::testLifeStatus()
{
	if (lifeStatus == 'v')   //'v' for victory
	{
		cout << endl <<
			"VICTORY! You've successfully escaped the ship." << endl;
	}
	else if (lifeStatus == 'd')   //'d' for died
	{
		cout << endl <<
			"YOU LOSE! The BEAST killed you." << endl;
	}
	else if (lifeStatus == 't')   //'t' for out of time
	{
		cout << endl <<
			"Out of Time! The SUPPORT TEAM arrived, incapacitated you, and locked you up again. YOU LOSE!" << endl;
	}
	else if (lifeStatus == 'q')
	{
		//no need to print anything. condition is handled in main().
	}
}

/***************************************************************************************************************
** Description: playGame() function plays the game while the player is still alive. The function handles the
** iteration of roomWrapper() function calls and updates the playerPosition (Space *) as necessary. It also calls
** timeMechanism() function to keep track of the player's time/steps left in the game. At the very end, the
** player is prompted if they would like to play again, the char is returned from the function. The function
** does not take in any argument.
***************************************************************************************************************/
char Game::playGame()
{
	char playAgain;
	bool validChoice = false;
	
	while (lifeStatus == 'a')   //while 'a' for alive
	{		
		cout << endl <<
			"-----------------------------------------------------------------------------" << endl;
		cout << "Current Room: " << playerPosition->getRoomName() << endl;

		cout << endl << "TIME REMAINING: " << MAX_NUMBER_OF_STEPS - stepsTaken;

		printInventory();

		playerPosition = playerPosition->roomWrapper(inventoryMaxSize, inventory, befriendedBeast, lifeStatus);
		
		if (lifeStatus == 'a')   //increment time and display warnings only if alive
		{
			timeMechanism();
		}
	}

	testLifeStatus();

	if (lifeStatus != 'q')
	{
		do
		{
			cout << endl <<
				"Would you like to go back to the MAIN MENU to play again [Y/N]? ";
			cin >> playAgain;
			cin.ignore();

			playAgain = toupper(playAgain);

			if (playAgain == 'Y' || playAgain == 'N')
			{
				validChoice = true;
			}
			else
			{
				cout << "Invalid choice. Try again." << endl;
			}

		} while (validChoice == false);
		
	}
	else
	{
		playAgain = 'N';
	}

	return playAgain;
}