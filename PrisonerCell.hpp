/**************************************************************************************************************
** Program name: Final Project
** Author: Derrick Li
** Date: Mar. 21, 2017
** Description:
** This class specification file contains the PrisonerCell class declaration. PrisonerCell is a derived class of the
** Space base class. The PrisonerCell class represents a room containing a PrisonerCell. It is where the
** player initially starts in. The room also contains the Main Door. The objective of the game is for the
** player to escape through the Main Door.
***************************************************************************************************************/

#ifndef PRISONERCELL_HPP
#define PRISONERCELL_HPP

#include "Space.hpp"

class PrisonerCell : public Space
{
protected:
	bool lockedHallwayDoor;
	bool lockedMainDoor;
	bool visitedMainDoor;

public:
	PrisonerCell();

	virtual Space* roomWrapper(int inventoryMaxSize, vector<string> &inventory, bool &befriendedBeast, char &lifeStatus) override;
	virtual char roomMenu(int inventoryMaxSize, vector<string> &inventory, bool &befriendedBeast) override;
	virtual void roomIntro() override;

	bool isLockedHallwayDoor();
	bool isLockedMainDoor();

	void computerInteraction();
	void mainDoorInteraction(vector<string> &inventory, bool befriendedBeast);
	void hallwayDoorInteraction();
};

#endif