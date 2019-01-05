/**************************************************************************************************************
** Program name: Final Project
** Author: Derrick Li
** Date: Mar. 21, 2017
** Description:
** This class specification file contains the Junction class declaration. Junction is a derived class of the
** Space base class. The Junction class represents an intersection of hallways. It provides four paths
** for the player to travel to: the Prisoner Cell, the Surveillance Room, the Weapons Locker, and the Cargo
** Storage room.
***************************************************************************************************************/

#ifndef JUNCTION_HPP
#define JUNCTION_HPP

#include "Space.hpp"

class Junction : public Space
{
protected:
	bool lockedWeaponsLocker;

public:
	Junction();

	virtual Space* roomWrapper(int inventoryMaxSize, vector<string> &inventory, bool &befriendedBeast, char &lifeStatus) override;
	virtual char roomMenu(int inventoryMaxSize, vector<string> &inventory, bool &befriendedBeast) override;
	virtual void roomIntro() override;

	bool isLockedWeaponsLocker();

	void weaponsLockerDoorInteraction(bool befriendedBeast);
};

#endif