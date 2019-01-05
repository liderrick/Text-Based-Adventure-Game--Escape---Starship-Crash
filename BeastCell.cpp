/**************************************************************************************************************
** Program name: Final Project
** Author: Derrick Li
** Date: Mar. 21, 2017
** Description:
** This class implementation file contains the member function definitions for the BeastCell class.
***************************************************************************************************************/

#include "BeastCell.hpp"
#include "menu.hpp"

#include <iostream>
#include <algorithm>	//for find()

using std::endl;
using std::cout;
using std::cin;

/***************************************************************************************************************
** Description: BeastCell class constructor. Initializes the roomName data member and sets the beastInCell bool
** flag to true -- representing the Beast is contained within its cell.
***************************************************************************************************************/
BeastCell::BeastCell()
{
	roomName = "BEAST CELL";
	beastInCell = true;
}

/***************************************************************************************************************
** Description: roomWrapper() takes in inventoryMaxSize (int), inventory (vector<string>), befriendedBeast (bool),
** and lifeStatus (char). It passes these parameters to the roomMenu() function in the derived class. The
** roomChar that is returned from the roomMenu() function is used to decide what actions the player wants to do
** (i.e. interact with object, or move between rooms) or a status of the player (i.e. has died, or wants to quit).
** A pointer to a Space object is returned from the roomWrapper() function. If the player remains in the room,
** the roomWrapper() returns a pointer to itself. If the player wishes to move between rooms, the function
** returns the pointer to the room the player wishes to move into.
***************************************************************************************************************/
Space * BeastCell::roomWrapper(int inventoryMaxSize, vector<string>& inventory, bool & befriendedBeast, char & lifeStatus)
{
	Space * roomPtr = this;
	char roomChar;

	roomIntro();
	roomChar = roomMenu(inventoryMaxSize, inventory, befriendedBeast);

	switch (roomChar)
	{
	case 'b': roomPtr = this;
		break;
	case 'c': roomPtr = bottom;
		break;
	case 'd': lifeStatus = 'd';
		break;
	case 'q': lifeStatus = 'q';
		break;
	}

	return roomPtr;
}

/***************************************************************************************************************
** Description: roomMenu() takes in inventoryMaxSize (int), inventory (vector<string>), and befriendedBeast (bool).
** It prompts the player with choices appropriate to the current status of the game, i.e. whether certain
** doors are unlocked or certain actions have been performed. After taking in an input, the function either performs
** a function call for item interaction or returns a char that represents the room the player selected to move into.
** The returned char is handled in the roomWrapper() function.
***************************************************************************************************************/
char BeastCell::roomMenu(int inventoryMaxSize, vector<string>& inventory, bool & befriendedBeast)
{
	char roomChar = 'b';

	bool validInteger = false;
	bool validChoice = false;
	int choice = 0;

	if (beastInCell)   //Beast is in cell
	{
		do
		{
			cout << endl << "Actions available:" << endl;
			cout << "1) Go back to CARGO ROOM" << endl;
			cout << "2) Take a closer look at the BEAST" << endl;
			cout << "9) Quit game" << endl;
			cout << "Choice: ";
			validInteger = inputIntegerValidationV3(choice);

			if (validInteger && (choice >= 1 && choice <= 2 || choice == 9))
			{
				validChoice = true;
			}
			else
			{
				cout << "Invalid choice. Try again." << endl;
			}

		} while (validChoice == false);

		switch (choice)
		{
		case 1: roomChar = 'c';
			break;
		case 2: roomChar = interactWithBeast(inventory, befriendedBeast);
			break;
		case 9: roomChar = 'q';
			break;
		}
	}
	else   //Beast is no longer in cell
	{
		do
		{
			cout << endl << "Actions available:" << endl;
			cout << "1) Go back to CARGO ROOM" << endl;
			cout << "9) Quit game" << endl;
			cout << "Choice: ";
			validInteger = inputIntegerValidationV3(choice);

			if (validInteger && (choice == 1 || choice == 9))
			{
				validChoice = true;
			}
			else
			{
				cout << "Invalid choice. Try again." << endl;
			}

		} while (validChoice == false);

		switch (choice)
		{
		case 1: roomChar = 'c';
			break;
		case 9: roomChar = 'q';
			break;
		}
	}

	return roomChar;
}

/***************************************************************************************************************
** Description: roomIntro() function displays an appropriate description of the current room the player is
** currently in. The function does not take in any arguments and does not have a return type.
***************************************************************************************************************/
void BeastCell::roomIntro()
{
	if (beastInCell)   //Beast is in cell
	{
		cout << endl <<
			"A ENERGY SHIELD partitions the large room. On the other side of the ENERGY SHIELD is a massive creature." << endl <<
			"It lays still with its eyes closed. You can tell it's alive because you can see its chest move from breathing." << endl <<
			"Although you can't tell if it's sleeping or unconscious. You notice it has sharp CLAWS." << endl;
	}
	else   //Beast is no longer in cell
	{
		cout << endl <<
			"Not much here. Was a containment for BEAST. Its ENERGY SHIELD didn't really hold up." << endl;
	}
}

/***************************************************************************************************************
** Description:interactWithBeast() function takes in inventory (vector<string>) and befriendedBeast (bool).
** The function displays the narrative between the player and the Beast. During the narration, the player is
** prompted with several options on how they would like to interact with the Beast. Depending on the player's
** reponse, it may result in their death, which immediate ends the game, or if they choose correctly, they
** live and befriend the Beast--which will be needed later on in the game. The function returns a char,
** either 'd' for dead/died, or 'b' for BeastCell to indicate they are still alive.
** Right answer to prompt: 2) Throw the MEAT at BEAST.
** Wrong answers to prompt: 1) Run the hell away, or 3) Shoot BEAST using your PISTOL.
***************************************************************************************************************/
char BeastCell::interactWithBeast(vector<string>& inventory, bool & befriendedBeast)
{
	char results;

	//search inventory vector for PISTOL
	vector<string>::iterator inventoryIterPistol = std::find(inventory.begin(), inventory.end(), "PISTOL");

	//search inventory vector for MEAT
	vector<string>::iterator inventoryIterMeat = std::find(inventory.begin(), inventory.end(), "MEAT");

	if (inventoryIterPistol != inventory.end() && inventoryIterMeat != inventory.end())   //PISTOL and MEAT are in inventory
	{
		bool validInteger = false;
		bool validChoice = false;
		int choice = 0;
		
		cout << endl <<
			"You slowly get closer to the ENERGY SHIELD, staring at the Creature." << endl <<
			"\"This must be the BEAST the DOOR mentioned,\" you think to yourself." << endl;

		pressEnterToContinue();

		cout << endl <<
			"As you continue to walk closer to the ENERGY SHIELD, the BEAST suddenly wakes up and charges towards you!" << endl;

		pressEnterToContinue();

		cout << endl <<
			"It is stopped as it thunderously slams into the ENERGY SHIELD. As the BEAST slammed into the ENERGY SHIELD," << endl <<
			"the SHIELD experienced a weakening in its intesity. The BEAST shakes off the impact and gets ready to charge again." << endl <<
			"You start to panic. But then you remembered you recently acquired a PISTOL." << endl <<
			"You dive both hands into your INVENTORY to search for it." << endl;
		
		pressEnterToContinue();

		cout << endl <<
			"The BEAST charges towards you again." << endl <<
			"In one hand, you pulled out the piece of MEAT. In the other hand, you pulled out the PISTOL." << endl <<
			"The BEAST slams into the ENERGY SHIELD again. The tremendous magnitude of the impact causes the ENERGY SHIELD to fail." << endl <<
			"The BEAST has broken though the ENERGY SHIELD and is heading straight towards you." << endl;

		pressEnterToContinue();

		do   //prompts player with options on how to interact with the Beast
		{
			cout << endl <<
				"You have three choices:" << endl <<
				"   1) Run the hell away," << endl <<
				"   2) Throw the MEAT at BEAST, or " << endl <<
				"   3) Shoot BEAST using your PISTOL." << endl <<
				"   9) Quit game" << endl;
			cout << endl << "Enter the number corresponding to the action you wish to execute: ";
			validInteger = inputIntegerValidationV3(choice);

			if (validInteger && (choice >= 1 && choice <= 3 || choice == 9))
			{
				validChoice = true;
			}
			else
			{
				cout << "Invalid choice. Try again." << endl;
			}

		} while (validChoice == false);


		if (choice == 2)   //Correct answer is to throw MEAT at BEAST.
		{
			cout << endl <<
				"You throw the MEAT at the BEAST and close your eyes -- hoping that death will come quickly." << endl;

			pressEnterToContinue();

			cout << endl <<
				"Nothing happens for a few moments. You wonder why aren't you dead yet. You open your eyes and see the BEAST" << endl <<
				"eating the MEAT you've thrown at it." << endl;

			pressEnterToContinue();

			cout << endl <<
				"In shock, you remain where you stand. Your grip on the PISTOL tightens." << endl <<
				"The BEAST finishes the MEAT quickly. It then sits down in a dog-like manner and looks at you contently." << endl;

			pressEnterToContinue();

			cout << endl <<
				"\"I think I made a friend,\" you think to yourself." << endl;

			pressEnterToContinue();

			cout << endl <<
				"You have befriended the BEAST. This may come in handy later." << endl;

			pressEnterToContinue();

			cout << endl <<
				"MEAT has been removed from your inventory." << endl;

			inventory.erase(inventoryIterMeat);   //Removes MEAT from your inventory

			beastInCell = false;   //set beastInCell bool flag to false

			befriendedBeast = true;   //set befriendedBeast bool flag to true

			results = 'b';   //'b' for BeastCell, to indicate they are still alive in the room

			pressEnterToContinue();
		}
		else if (choice == 1)   //Run away (wrong answer)
		{
			cout << endl <<
				"You start to run away as fast as you can. The BEAST quickly catches up to you." << endl <<
				"It sinks its CLAWS through your back and into your heart. You take your last gasp of breath as you drop to the floor." << endl;
			
			results = 'd';    //Defeated. Killed by BEAST

			pressEnterToContinue();
		}
		else if (choice == 3)   //Shoot at BEAST with PISTOL (wrong answer)
		{
			cout << endl <<
				"You bring the PISTOL up and aim at the BEAST. You pull the trigger two times." << endl <<
				"The PISTOL goes off twice. But this did nothing to stop the BEAST. It continues to charge at you." << endl;

			pressEnterToContinue();

			cout << endl <<
				"You continue to shoot as the BEAST lunges towards you with its CLAWS ready." << endl <<
				"The CLAWS dig deep through your heart and your entire body is slammed to the ground as the BEAST lands on you." << endl;
		
			results = 'd';    //Defeated. Killed by BEAST

			pressEnterToContinue();
		}
		else if (choice == 9)   //quit
		{
			results = 'q';
		}
	}
	else    //PISTOL or MEAT are not in inventory. Player should not see this message, but it acts as an additional safeguard.
	{
		cout << endl <<
			"You feel as if you missed something. You decide to go look around before interacting with the BEAST CELL." << endl;
		
		results = 'b';

		pressEnterToContinue();
	}

	return results;
}
