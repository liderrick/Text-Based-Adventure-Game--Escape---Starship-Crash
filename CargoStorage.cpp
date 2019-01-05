/**************************************************************************************************************
** Program name: Final Project
** Author: Derrick Li
** Date: Mar. 21, 2017
** Description:
** This class implementation file contains the member function definitions for the CargoStorage class.
***************************************************************************************************************/

#include "CargoStorage.hpp"
#include "menu.hpp"

#include <iostream>
#include <algorithm>	//for find()

using std::endl;
using std::cout;
using std::cin;

/***************************************************************************************************************
** Description: CargoStorage class constructor. Initializes the roomName data member and adds two items to
** the itemsInRoom vector - PISTOL and MEAT. The allItemsPickedUp bool flag is set to false to indicate
** there are items in the room.
***************************************************************************************************************/
CargoStorage::CargoStorage()
{
	lockedBeastRoom = true;
	
	roomName = "CARGO STORAGE";
	
	itemsInRoom.push_back("PISTOL");
	itemsInRoom.push_back("MEAT");

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
Space * CargoStorage::roomWrapper(int inventoryMaxSize, vector<string>& inventory, bool & befriendedBeast, char & lifeStatus)
{
	Space * roomPtr = this;
	char roomChar;

	roomIntro();
	roomChar = roomMenu(inventoryMaxSize, inventory, befriendedBeast);

	switch (roomChar)
	{
	case 'c': roomPtr = this;
		break;
	case 'b': roomPtr = top;
		break;
	case 'j': roomPtr = bottom;
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
char CargoStorage::roomMenu(int inventoryMaxSize, vector<string>& inventory, bool &befriendedBeast)
{	
	char roomChar = 'c';

	bool validInteger = false;
	bool validChoice = false;
	int choice = 0;
	
	if (isLockedBeastRoom())   //Beast room door is locked
	{
		do
		{
			cout << endl << "Actions available:" << endl;
			cout << "1) Go back to JUNCTION" << endl;
			cout << "2) Interact with door to BEAST CELL" << endl;
			cout << "3) Interact with COOLER" << endl;
			cout << "4) Interact with TOOL CHEST" << endl;
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
		case 1: roomChar = 'j';
			break;
		case 2: beastRoomDoorInteraction(inventory);
			break;
		case 3: pickUpMeat(inventoryMaxSize, inventory);
			break;
		case 4: pickUpPistol(inventoryMaxSize, inventory);
			break;
		case 9: roomChar = 'q';
			break;
		}
	}
	else   //Beast room door is unlocked
	{
		do
		{
			cout << endl << "Actions available:" << endl;
			cout << "1) Go back to JUNCTION" << endl;
			cout << "2) Go through door to BEAST CELL" << endl;
			cout << "3) Interact with COOLER" << endl;
			cout << "4) Interact with TOOL CHEST" << endl;
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
		case 1: roomChar = 'j';
			break;
		case 2: roomChar = beastRoomCheck(inventory);
			break;
		case 3: pickUpMeat(inventoryMaxSize, inventory);
			break;
		case 4: pickUpPistol(inventoryMaxSize, inventory);
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
void CargoStorage::roomIntro()
{
	cout << endl <<
		"A large space that looks like it holds the ship's CARGO. At the moment it's pretty empty." << endl <<
		"You see there's a COOLER and TOOL CHEST lying on the ground." << endl <<
		"At the far end, you see a door that reads in large letters, \"CAUTION: DANGEROUS BEAST!\"" << endl;
}

/***************************************************************************************************************
** Description: pickUpPistol() function takes in inventoryMaxSize (int) and inventory (vector<string>).
** The function interacts with the Tool Chest in the room and adds the PISTOL to the player's inventory if
** it has not been collected yet. The function doesn't have a return type.
***************************************************************************************************************/
void CargoStorage::pickUpPistol(int inventoryMaxSize, vector<string>& inventory)
{
	//search itemsInRoom vector for PISTOL
	vector<string>::iterator roomIter = std::find(itemsInRoom.begin(), itemsInRoom.end(), "PISTOL");

	if (roomIter != itemsInRoom.end())   //PISTOL in tool chest
	{
		cout << endl <<
			"You walk over to the single-compartment TOOL CHEST. You open it and see a PISTOL in it along with some ammo." << endl <<
			"\"Better take this just in case,\" you say to yourself." << endl;

		pressEnterToContinue();

		cout << endl <<
			"You load the PISTOL with ammo and add the PISTOL to your INVENTORY." << endl;
		
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
	else   //PISTOL has already been picked up
	{
		cout << endl <<
			"There's nothing else of interest in the TOOL CHEST." << endl;
	}

	pressEnterToContinue();
}

/***************************************************************************************************************
** Description: pickUpMeat() function takes in inventoryMaxSize (int) and inventory (vector<string>).
** The function interacts with the Cooler in the room and adds the MEAT to the player's inventory if
** it has not been collected yet. The function doesn't have a return type.
***************************************************************************************************************/
void CargoStorage::pickUpMeat(int inventoryMaxSize, vector<string>& inventory)
{
	//search itemsInRoom vector for MEAT
	vector<string>::iterator roomIter = std::find(itemsInRoom.begin(), itemsInRoom.end(), "MEAT");

	if (roomIter != itemsInRoom.end())   //MEAT in cooler
	{
		cout << endl <<
			"Your stomach growls. You hope there's some food in that COOLER." << endl <<
			"You approach the COOLER and open it. You find a large, cold piece of cooked MEAT in a ziplock plastic bag." << endl <<
			"\"Guess it's something at least,\" you think to yourself." << endl;

		pressEnterToContinue();

		cout << endl <<
			"You take the MEAT and add it to your INVENTORY." << endl;

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
	else   //MEAT has already been picked up
	{
		cout << endl <<
			"There's nothing else in the COOLER." << endl;
	}

	pressEnterToContinue();
}

/***************************************************************************************************************
** Description: isLockedBeastRoom() function returns lockedBeastRoom (bool). The function doesn't take in any
** argument.
***************************************************************************************************************/
bool CargoStorage::isLockedBeastRoom()
{
	return lockedBeastRoom;
}

/***************************************************************************************************************
** Description: beastRoomDoorInteraction() function takes the player's inventory (vector<string>). The function
** interacts with the door leading to the Beast Cell. If the KEYCARD is in the player's inventory, it is used
** to open the door. The function doesn't have a return type.
***************************************************************************************************************/
void CargoStorage::beastRoomDoorInteraction(vector<string> &inventory)
{
	//search inventory vector for KEYCARD
	vector<string>::iterator inventoryIter = std::find(inventory.begin(), inventory.end(), "KEYCARD");

	cout << endl <<
		"You approach the large DOOR with the words \"CAUTION: DANGEROUS BEAST!\" written on it." << endl <<
		"You become more curious than afraid. To the right of the door is an electronic SLOT." << endl;

	pressEnterToContinue();

	if (inventoryIter != inventory.end())   //KEYCARD is in inventory
	{
		cout <<
			"You wonder if maybe the KEYCARD you have in your INVENTORY will open the DOOR." << endl <<
			"You take the KEYCARD from your INVENTORY and push it into the SLOT." << endl;

		pressEnterToContinue();

		cout << endl <<
			"The electronic SLOT beeps and small light is lit green. You hear the locking mechanism of the door work." << endl <<
			"The DOOR to BEAST is now unlocked." << endl;

		pressEnterToContinue();

		cout << endl <<
			"KEYCARD has been removed from your INVENTORY." << endl;

		inventory.erase(inventoryIter);   //Removed KEYCARD from inventory

		lockedBeastRoom = false;
	}
	else   //KEYCARD is not in inventory
	{
		cout <<
			"You don't seem to have anything suitable in your INVENTORY that can be used to open the DOOR." << endl <<
			"Maybe you can find something." << endl;
	}

	pressEnterToContinue();
}

/***************************************************************************************************************
** Description: beastRoomDoorInteraction() function takes the player's inventory (vector<string>). The function
** checks the player's inventory to see if they have PISTOL and MEAT in their inventory. If present, the player is
** allowed to enter the Beast Cell. If either or both items are absent, a message is displayed to the player
** suggesting they look at things within this room. A char is returned to indicate whether they are allowed to
** go to the Beast Cell ('b') or they cannot go to the Beast Cell because they are lacking certain items ('c').
***************************************************************************************************************/
char CargoStorage::beastRoomCheck(vector<string>& inventory)
{
	char roomChar;

	if (isAllItemsPickedUp())   //PISTOL and MEAT have been picked up. Allowed to continue to BEAST CELL.
	{
		roomChar = 'b';
	}
	else    //PISTOL and MEAT have not been picked up. Not allowed to continue.
	{
		cout << endl <<
			"You get a feeling you're forgetting something. Maybe there is a thing or two you've overlooked in this room." << endl;

		pressEnterToContinue();

		roomChar = 'c';
	}

	return roomChar;
}
