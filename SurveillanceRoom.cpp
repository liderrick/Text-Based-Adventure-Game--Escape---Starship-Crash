/**************************************************************************************************************
** Program name: Final Project
** Author: Derrick Li
** Date: Mar. 21, 2017
** Description:
** This class implementation file contains the member function definitions for the SurveillanceRoom class.
***************************************************************************************************************/

#include "SurveillanceRoom.hpp"
#include "menu.hpp"

#include <iostream>
#include <algorithm>	//for find()

using std::endl;
using std::cout;
using std::cin;

const int CODE_IN_NOTE = 66008;
const int AUTHORIZATION_CODE = 80099;

/***************************************************************************************************************
** Description: SurveillanceRoom class constructor. Initializes the roomName data member and adds 1 item to
** the itemsInRoom vector - KEYCARD. The allItemsPickedUp bool flag is set to false to indicate
** there is at least one item in the room.
***************************************************************************************************************/
SurveillanceRoom::SurveillanceRoom()
{
	roomName = "SURVEILLANCE ROOM";

	itemsInRoom.push_back("KEYCARD");
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
Space * SurveillanceRoom::roomWrapper(int inventoryMaxSize, vector<string>& inventory, bool & befriendedBeast, char & lifeStatus)
{
	Space * roomPtr = this;
	char roomChar;

	roomIntro();
	roomChar = roomMenu(inventoryMaxSize, inventory, befriendedBeast);

	switch (roomChar)
	{
	case 's': roomPtr = this;
		break;
	case 'j': roomPtr = left;
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
char SurveillanceRoom::roomMenu(int inventoryMaxSize, vector<string>& inventory, bool &befriendedBeast)
{
	char roomChar = 's';

	bool validInteger = false;
	bool validChoice = false;
	int choice = 0;

	do
	{
		cout << endl << "Actions available:" << endl;
		cout << "1) Go back to JUNCTION" << endl;
		cout << "2) Interact with COMPUTER CONSOLE" << endl;
		cout << "3) Interact with PIECE OF PAPER on ground" << endl;
		cout << "9) Quit game" << endl;
		cout << "Choice: ";
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

	switch (choice)
	{
	case 1: roomChar = 'j';
		break;
	case 2: pickUpKey(inventoryMaxSize, inventory);
		break;
	case 3: noteInteraction();
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
void SurveillanceRoom::roomIntro()
{
	cout << endl <<
		"A small room with a few COMPUTER CONSOLES lined up against the wall." << endl <<
		"One of the COMPUTER CONSOLES is on. It looked like someone was in the middle of a task." << endl <<
		"A small PIECE OF PAPER lies on the ground. ";

	if (!isAllItemsPickedUp())   //Keycard has not been picked up
	{
		cout <<
			"A KEYCARD protrudes from a slot on the COMPUTER CONSOLE that is on." << endl;
	}
	else   //Keycard has been picked up
	{
		cout << endl;
	}
}

/***************************************************************************************************************
** Description: noteInteraction() function allows the user to interact with the note. The Authorization
** Code is a rotation of 180 degrees of the number written on the note.  The function does not take in any
** arguments and does not have a return type.
***************************************************************************************************************/
void SurveillanceRoom::noteInteraction()
{
	cout << endl <<
		"You pick up the small PIECE OF PAPER off the ground. It's blank." << endl <<
		"You decide to FLIP it over. It has \"" << CODE_IN_NOTE << "\" written on it." << endl <<
		"You shrug. \"Probably nothing,\" you think to yourself. You let the PAPER fall back to the ground." << endl;

	pressEnterToContinue();
}

/***************************************************************************************************************
** Description: pickUpKey() function takes in inventoryMaxSize (int) and inventory (vector<string>).
** The function interacts with the Computer Console in the room and adds the KEYCARD to the player's inventory if
** the player correctly enters the Authorization code. The function doesn't have a return type.
***************************************************************************************************************/
void SurveillanceRoom::pickUpKey(int inventoryMaxSize, vector<string> &inventory)
{
	int enteredCode;
	
	if (!isAllItemsPickedUp())   //KEYCARD has not been picked up yet
	{

		cout << endl <<
			"You approach the lit COMPUTER CONSOLE. The screen reads: " << endl << endl <<
			"   SYSTEM: Generating KEYCARD Access..." << endl;
		enteredCode = promptAuthorizationCode();

		if (enteredCode == AUTHORIZATION_CODE)
		{
			cout << endl <<
				"   SYSTEM: ACCESS GRANTED." << endl <<
				"   SYSTEM: Writing permissions to KEYCARD..." << endl <<
				"   SYSTEM: Write Completed. Remove KEYCARD." << endl;

			pressEnterToContinue();

			cout << endl <<
				"You remove the KEYCARD from the slot on the COMPUTER CONSOLE and place it into your INVENTORY." << endl;

			//search itemsInRoom vector for KEYCARD
			vector<string>::iterator roomIter = std::find(itemsInRoom.begin(), itemsInRoom.end(), "KEYCARD");

			if (roomIter != itemsInRoom.end())   //KEYCARD in room
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
		else
		{
			cout << endl <<
				"   SYSTEM: ACCESS DENIED. Incorrect Authorization Code." << endl;
		}
	}
	else   //KEYCARD has already been picked up
	{
		cout << endl <<
			"The COMPUTER CONSOLE screen reads:" << endl << endl <<
			"   SYSTEM: KEYCARD Access Generated." << endl;
	}

	pressEnterToContinue();
}
