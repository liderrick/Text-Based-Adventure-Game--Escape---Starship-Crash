/**************************************************************************************************************
** Program name: Final Project
** Author: Derrick Li
** Date: Mar. 21, 2017
** Description:
** This class implementation file contains the member function definitions for the PrisonerCell class.
***************************************************************************************************************/

#include "PrisonerCell.hpp"
#include "menu.hpp"

#include <iostream>
#include <algorithm>	//for find()

using std::endl;
using std::cout;
using std::cin;

/***************************************************************************************************************
** Description: PrisonerCell class constructor. Initializes the roomName data member and sets serveral bool
** flags: 1) lockedHallwayDoor to true (representing the the locked hallway door), 2) lockedMainDoor to true
** (representing the locked Main Door), and 3) visitedMainDoor to false (representing if the player has visited
** the main door yet - it is used to display the appropriate narration during the game).
***************************************************************************************************************/
PrisonerCell::PrisonerCell()
{
	lockedHallwayDoor = true;
	lockedMainDoor = true;
	visitedMainDoor = false;

	roomName = "PRISONER CELL";
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
Space * PrisonerCell::roomWrapper(int inventoryMaxSize, vector<string>& inventory, bool & befriendedBeast, char &lifeStatus)
{
	Space * roomPtr = this;
	char roomChar;

	roomIntro();
	roomChar = roomMenu(inventoryMaxSize, inventory, befriendedBeast);

	switch (roomChar)
	{
	case 'p': roomPtr = this;
		break;
	case 'j': roomPtr = top;
		break;
	case 'v': lifeStatus = 'v';
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
char PrisonerCell::roomMenu(int inventoryMaxSize, vector<string> &inventory, bool &befriendedBeast)
{
	char roomChar = 'p';

	bool validInteger = false;
	bool validChoice = false;
	int choice = 0;

	if (isLockedHallwayDoor())	//Hallway Door is locked
	{
		do
		{
			cout << endl << "Actions available:" << endl;
			cout << "1) Interact with MAIN DOOR" << endl;
			cout << "2) Interact with HALLWAY DOOR" << endl;
			cout << "3) Interact with COMPUTER CONSOLE" << endl;
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
		case 1: mainDoorInteraction(inventory, befriendedBeast);
			break;
		case 2: hallwayDoorInteraction();
			break;
		case 3: computerInteraction();
			break;
		case 9: roomChar = 'q';
			break;
		}
	}
	else   //Hallway Door is unlocked
	{
		do
		{
			cout << endl << "Actions available:" << endl;
			cout << "1) Interact with MAIN DOOR" << endl;
			cout << "2) Go through HALLWAY DOOR" << endl;
			cout << "3) Interact with COMPUTER CONSOLE" << endl;
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
		case 1: mainDoorInteraction(inventory, befriendedBeast);
			break;
		case 2: roomChar = 'j';
			break;
		case 3: computerInteraction();
			break;
		case 9: roomChar = 'q';
			break;
		}
	}

	//If main door is unlocked, then player wins the game. 'v' is returned for victory.
	if (isLockedMainDoor() == false)
	{
		roomChar = 'v';
	}

	return roomChar;
}

/***************************************************************************************************************
** Description: roomIntro() function displays an appropriate description of the current room the player is
** currently in. The function does not take in any arguments and does not have a return type.
***************************************************************************************************************/
void PrisonerCell::roomIntro()
{
	if (isLockedHallwayDoor())	//Hallway door is locked
	{
		cout << endl <<
			"A large room with a single PRISONER CELL. There's a large MAIN DOOR and a smaller HALLWAY DOOR." << endl <<
			"They both appear to be locked. A COMPUTER CONSOLE can be seen with a blinking light." << endl;
	}
	else   ////Hallway door is unlocked
	{
		cout << endl <<
			"A large room with a single PRISONER CELL. The MAIN DOOR is locked." << endl <<
			"The HALLWAY DOOR is unlocked." << endl;
	}

}

/***************************************************************************************************************
** Description: isLockedHallwayDoor() function returns lockedHallwayDoor (bool). The function doesn't take in any
** argument. 
***************************************************************************************************************/
bool PrisonerCell::isLockedHallwayDoor()
{
	return lockedHallwayDoor;
}

/***************************************************************************************************************
** Description: isLockedMainDoor() function returns lockedMainDoor (bool). The function doesn't take in any
** argument. 
***************************************************************************************************************/
bool PrisonerCell::isLockedMainDoor()
{
	return lockedMainDoor;
}

/***************************************************************************************************************
** Description: computerInteraction() function unlocks the Hallway Door if it has not been unlocked yet. It
** also displays a short narration regarding how the Starship crash landed. The function does not take in
** any arguments and it does not have a return type.
***************************************************************************************************************/
void PrisonerCell::computerInteraction()
{
	cout << endl <<
		"You walk over and take a closer look at the COMPUTER CONSOLE." << endl <<
		"It displays: " << endl << endl <<
		"   . . ." << endl <<
		"   ----------SYSTEMS LOG----------" << endl <<
		"   0734 -- SENSOR: Strong gravitional anomaly detected." << endl <<
		"   0735 -- SYSTEM: Large object warning." << endl <<
		"   0736 -- SYSTEM: WARNING! COLLISION IMMINENT." << endl <<
		"   0737 -- LEFT ENGINE: DAMAGED." << endl <<
		"   0737 -- LEFT ENGINE: Thrust level suboptimal." << endl <<
		"   0738 -- LEFT ENGINE: FAILURE." << endl <<
		"   0739 -- SENSOR: Gravitional field strength increasing." << endl <<
		"   0741 -- RIGHT ENGINE: Thrust level at 220%. Overheat warning." << endl <<
		"   0742 -- RIGHT ENGINE: WARNING! OVERHEAT IMMINENT. REDUCE THRUST NOW." << endl <<
		"   0742 -- RIGHT ENGINE: FAILURE." << endl <<
		"   0743 -- SYSTEM: Entering stratosphere." << endl <<
		"   0744 -- SYSTEM: Emergency landing procedure activated." << endl <<
		"   0745 -- SYSTEM: COLLSION IMMINENT." << endl <<
		"   0745 -- SYSTEM: COLLISION DETECTED. SYSTEM-WIDE FAILURE." << endl <<
		"   0745 -- EMERGENCY PROTOCOL: Distress signal sent." << endl <<
		"   . . ." << endl;

	if (isLockedHallwayDoor())   ////Hallway door is locked
	{
		cout << endl <<
			"You look to the right and see a flashing green button that reads \"OPEN DOOR\"." << endl <<
			"You immediately realize this is your chance to ESCAPE." << endl;

		cout << endl <<
			"-----------------------------------------------------------------------------" << endl <<
			"Press [ENTER] to press OPEN DOOR button." << endl;
		cin.ignore();

		cout <<
			"You hear an unlocking sound. You thought it was the MAIN DOOR. " << endl <<
			"But it came from the HALLWAY DOOR instead." << endl;

		lockedHallwayDoor = false;

		pressEnterToContinue();
	}
	else   //Hallway door is unlocked
	{
		cout << endl <<
			"You see that the \"OPEN DOOR\" button has already been depressed." << endl;

		pressEnterToContinue();
	}
}

/***************************************************************************************************************
** Description: mainDoorInteraction() function takes in inventory (vector<string>) and befriendedBeast (bool).
** The function unlocks the Main Door (the objective of the game) if the player has LASER in their inventory
** and has befriended Beast (i.e. befriendedBeast is true). The function also considers other scenarios
** (i.e. befriended Beast but does not have Laser, or both, did not befriend Beast and do not have Laser) and
** displays an appropriate hint to the player. The function doesn't have a return type.
***************************************************************************************************************/
void PrisonerCell::mainDoorInteraction(vector<string> &inventory, bool befriendedBeast)
{
	//search inventory for LASER
	vector<string>::iterator iter = std::find(inventory.begin(), inventory.end(), "LASER");
	
	if (iter != inventory.end() && befriendedBeast) //LASER is in inventory and befriended Beast
	{
		cout << endl <<
			"You approach the MAIN DOOR. You use the LASER to cut the remainder of the door HINGES off." << endl <<
			"The MAIN DOOR still seemed somewhat immobile." << endl <<
			"You ram your body a few times against the door to get loose but it doesn't budge." << endl;

		pressEnterToContinue();

		cout << endl <<
			"Suddenly you hear a thumping sound behind you. You turn around and see BEAST charging at you!" << endl <<
			"You quickly dive out the way! Nearly missing the trainwreck you were about to become." << endl;

		pressEnterToContinue();

		cout << endl <<
			"BEAST hits the MAIN DOOR with such great force the door blows wide open." << endl <<
			"You gaze in awe as you see BEAST run straight into the forest and quickly disappear." << endl;

		pressEnterToContinue();

		cout << endl <<
			"You quickly collect yourself and escape outside as well. \"Not today,\" you say to yourself." << endl;

		lockedMainDoor = false;

		pressEnterToContinue();
	}
	else if (iter == inventory.end() && befriendedBeast)   //Laser is in not inventory but befriended Beast
	{
		cout << endl <<
			"You approach the MAIN DOOR. \"Maybe BEAST can CUT the HINGES,\" you think to yourself." << endl <<
			"You point to the damaged HINGES. BEAST stares at you blankly." << endl <<
			"You then imitate a few punching motions at the HINGES. BEAST'S primal instincts quickly kicks in." << endl;

		pressEnterToContinue();

		cout << endl <<
			"BEAST uses its CLAWS and gives the HINGES a few heavy swipes!" << endl;

		pressEnterToContinue();
		
		cout << endl <<
			"But the HINGES doesn't appear to be damaged any further." << endl <<
			"There must be something else you can use to CUT the HINGES." << endl;

		pressEnterToContinue();

	}
	else   //Laser is in not inventory and did not befriended Beast
	{
		if (!visitedMainDoor)
		{
			cout << endl <<
				"You approach the MAIN DOOR. It looks heavy and solid with no means of opening it." << endl <<
				"However you notice that that HINGES were damaged in the collision." << endl <<
				"Maybe you can use something to CUT the HINGES and get the door to open." << endl;

			visitedMainDoor = true;
		}
		else
		{
			cout << endl <<
				"Maybe you can find something to CUT the HINGES on the MAIN DOOR and get it open." << endl;
		}

		pressEnterToContinue();
	}
}

/***************************************************************************************************************
** Description: hallwayDoorInteraction() function allows the player to interact with the Hallway Door when
** it is locked. It displays a hint to the player on how to get it open. The function does not take in any
** arguments and it does not have a return type.
***************************************************************************************************************/
void PrisonerCell::hallwayDoorInteraction()
{
	cout << endl <<
		"You approach the HALLWAY DOOR. You attempt to push it open. But it does not move." << endl <<
		"Perhaps it can be controlled by something." << endl;

	pressEnterToContinue();
}
