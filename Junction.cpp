/**************************************************************************************************************
** Program name: Final Project
** Author: Derrick Li
** Date: Mar. 21, 2017
** Description:
** This class implementation file contains the member function definitions for the Junction class.
***************************************************************************************************************/

#include "Junction.hpp"
#include "menu.hpp"

#include <iostream>
#include <algorithm>	//for find()

using std::endl;
using std::cout;
using std::cin;

/***************************************************************************************************************
** Description: Junction class constructor. Initializes the roomName data member and sets the lockedWeaponsLocker bool
** flag to true -- representing that the door to the Weapons Locker is locked.
***************************************************************************************************************/
Junction::Junction()
{
	lockedWeaponsLocker = true;
	roomName = "JUNCTION";
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
Space * Junction::roomWrapper(int inventoryMaxSize, vector<string>& inventory, bool & befriendedBeast, char & lifeStatus)
{
	Space * roomPtr = this;
	char roomChar;

	roomIntro();
	roomChar = roomMenu(inventoryMaxSize, inventory, befriendedBeast);

	switch (roomChar)
	{
	case 'j': roomPtr = this;
		break;
	case 'c': roomPtr = top;
		break;
	case 'p': roomPtr = bottom;
		break;
	case 'w': roomPtr = left;
		break;
	case 's': roomPtr = right;
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
char Junction::roomMenu(int inventoryMaxSize, vector<string> &inventory, bool &befriendedBeast)
{
	char roomChar = 'j';

	bool validInteger = false;
	bool validChoice = false;
	int choice = 0;

	if (isLockedWeaponsLocker())	//Weapons Locker Door is locked
	{
		do
		{
			cout << endl << "Actions available:" << endl;
			cout << "1) Go to PRISONER CELL" << endl;
			cout << "2) Interact with door to WEAPONS LOCKER" << endl;
			cout << "3) Go to SURVEILLANCE ROOM" << endl;
			cout << "4) Go to CARGO STORAGE" << endl;
			cout << "9) Quit game" << endl;
			cout << "Choice: ";
			validInteger = inputIntegerValidationV3(choice);

			if (validInteger && (choice >= 1 && choice <= 4 || choice == 9))
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
		case 1: roomChar = 'p';
			break;
		case 2: weaponsLockerDoorInteraction(befriendedBeast);
			break;
		case 3: roomChar = 's';
			break;
		case 4: roomChar = 'c';
			break;
		case 9: roomChar = 'q';
			break;
		}
	}
	else   //Weapons Locker Door is unlocked
	{
		do
		{
			cout << endl << "Actions available:" << endl;
			cout << "1) Go to PRISONER CELL" << endl;
			cout << "2) Go to WEAPONS LOCKER" << endl;
			cout << "3) Go to SURVEILLANCE ROOM" << endl;
			cout << "4) Go to CARGO STORAGE" << endl;
			cout << "9) Quit game" << endl;
			cout << "Choice: ";
			validInteger = inputIntegerValidationV3(choice);

			if (validInteger && (choice >= 1 && choice <= 4 || choice == 9))
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
		case 1: roomChar = 'p';
			break;
		case 2: roomChar = 'w';
			break;
		case 3: roomChar = 's';
			break;
		case 4: roomChar = 'c';
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
void Junction::roomIntro()
{
	cout << endl <<
		"A junction of hallways. Behind you is the PRISONER CELL. To your left is the WEAPONS LOCKER." << endl <<
		"Ahead of you is the CARGO STORAGE. And to your right is the SURVEILLANCE ROOM." << endl;
	
	if (isLockedWeaponsLocker())   //Weapons Locker Door is locked
	{
		cout <<
			"You can see from afar that the door to the WEAPONS LOCKER appears to be locked." << endl;
	}
	else   //Weapons Locker Door is unlocked
	{
		cout <<
			"The door to the WEAPONS LOCKER is unlocked." << endl;
	}
}

/***************************************************************************************************************
** Description: isLockedWeaponsLocker() function returns lockedWeaponsLocker (bool). The function doesn't take in any
** argument. 
***************************************************************************************************************/
bool Junction::isLockedWeaponsLocker()
{
	return lockedWeaponsLocker;
}

/***************************************************************************************************************
** Description: weaponsLockerDoorInteraction() function takes in befriendedBeast (bool). The function unlocks
** the door to the Weapons Locker if befriendedBeast is true, otherwise it provides a hint to the player
** as to what they can do to get the door unlocked.
***************************************************************************************************************/
void Junction::weaponsLockerDoorInteraction(bool befriendedBeast)
{
	if (befriendedBeast)   //Befriended beast
	{
		cout << endl <<
			"You notice that BEAST has MASSIVE hands and CLAWS. " << endl <<
			"You think to yourself that BEAST may be able to break this LOCK on the door to the WEAPONS LOCKER." << endl;
		
		pressEnterToContinue();

		cout << endl <<
			"You gesture to the LOCK and made a few swiping motions with your fist. BEAST seems to understand." << endl <<
			"BEAST approaches the LOCK and gives it a heavy swipe with it CLAWS! The LOCK snaps in half." << endl;

		pressEnterToContinue();

		cout << endl <<
			"The door to the WEAPONS LOCKER is now unlocked." << endl;

		lockedWeaponsLocker = false;
	}
	else    //Did not befriend beast
	{
		cout << endl <<
			"The door to the WEAPONS LOCKER is locked. You notice that there is a HEAVY LOCK on the door. " << endl <<
			"Perhaps if you had something that can generate a lot of FORCE, you might be able to break the LOCK." << endl;
	}

	pressEnterToContinue();
}
