/**************************************************************************************************************
** Program name: Final Project
** Author: Derrick Li
** Date: Mar. 21, 2017
** Description:
** This class implementation file contains the member function definitions for the WeaponsLocker class.
***************************************************************************************************************/

#include "WeaponsLocker.hpp"
#include "menu.hpp"

#include <iostream>
#include <algorithm>	//for find()

using std::endl;
using std::cout;
using std::cin;

/***************************************************************************************************************
** Description: WeaponsLocker class constructor. Initializes the roomName data member and adds 1 item to
** the itemsInRoom vector - LASER. The allItemsPickedUp bool flag is set to false to indicate
** there is at least one item in the room.
***************************************************************************************************************/
WeaponsLocker::WeaponsLocker()
{
	roomName = "WEAPONS LOCKER";

	itemsInRoom.push_back("LASER");
	allItemsPickedUp = false;
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
Space * WeaponsLocker::roomWrapper(int inventoryMaxSize, vector<string>& inventory, bool & befriendedBeast, char & lifeStatus)
{
	Space * roomPtr = this;
	char roomChar;

	roomIntro();
	roomChar = roomMenu(inventoryMaxSize, inventory, befriendedBeast);

	switch (roomChar)
	{
	case 'w': roomPtr = this;
		break;
	case 'j': roomPtr = right;
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
char WeaponsLocker::roomMenu(int inventoryMaxSize, vector<string>& inventory, bool & befriendedBeast)
{
	char roomChar = 'w';

	bool validInteger = false;
	bool validChoice = false;
	int choice = 0;

	do
	{
		cout << endl << "Actions available:" << endl;
		cout << "1) Go back to JUNCTION" << endl;
		cout << "2) Interact with WEAPONS LOCKER" << endl;
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
	case 1: roomChar = 'j';
		break;
	case 2: pickUpLaser(inventoryMaxSize, inventory);
		break;
	case 9: roomChar = 'q';
		break;
	}

	return roomChar;
}

/***************************************************************************************************************
** Description: roomIntro() function displays an appropriate description of the current room the player is
** currently in. The function does not take in any arguments and does not have a return type.
***************************************************************************************************************/
void WeaponsLocker::roomIntro()
{
	cout << endl <<
		"A small room. There's a LOCKER against the wall. ";

	if (!isAllItemsPickedUp())   //LASER has not been picked up yet
	{
		cout << "Maybe there's something useful in it." << endl;
	}
	else
	{
		cout << endl;
	}
}

/***************************************************************************************************************
** Description: pickUpLaser() function takes in inventoryMaxSize (int) and inventory (vector<string>).
** The function interacts with the Weapons Locker in the room and adds the LASER to the player's inventory if
** it has not been collected yet. The function doesn't have a return type.
***************************************************************************************************************/
void WeaponsLocker::pickUpLaser(int inventoryMaxSize, vector<string> &inventory)
{
	if (!isAllItemsPickedUp())   //LASER has not been picked up yet
	{
		cout << endl <<
			"You approach the LOCKER and open it. A large cutting LASER sits on a shelf." << endl;

		pressEnterToContinue();

		cout << endl <<
			"You take the LASER from the WEAPONS LOCKER and add it to your INVENTORY." << endl;

		//search itemsInRoom vector for LASER
		vector<string>::iterator roomIter = std::find(itemsInRoom.begin(), itemsInRoom.end(), "LASER");

		if (roomIter != itemsInRoom.end())   //LASER in room
		{
			if (inventory.size() < inventoryMaxSize)   //if space is available in inventory
			{
				inventory.push_back(*roomIter);   //move founded object into inventory

				itemsInRoom.erase(roomIter);   //remove object from itemsInRoom
			}

			if (itemsInRoom.empty())
			{
				allItemsPickedUp = true;   //set allItemsPickedUp bool flag to true if no more items in room
			}
		}

	}
	else   //LASER has been picked up
	{
		cout << endl <<
			"There's nothing else of interest in here." << endl;
	}

	pressEnterToContinue();
}
