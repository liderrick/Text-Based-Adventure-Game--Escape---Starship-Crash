/**************************************************************************************************************
** Program name: Final Project
** Author: Derrick Li
** Date: Mar. 21, 2017
** Description:
** This class specification file contains the CargoStorage class declaration. CargoStorage is a derived class
** of the Space base class. The CargoStorage class represents a cargo storage room. It is where the player obtains
** the Pistol and Meat to add to their inventory.
***************************************************************************************************************/

#ifndef CARGOSTORAGE_HPP
#define CARGOSTORAGE_HPP

#include "Space.hpp"

class CargoStorage : public Space
{
protected:
	bool lockedBeastRoom;

public:
	CargoStorage();

	virtual Space* roomWrapper(int inventoryMaxSize, vector<string> &inventory, bool &befriendedBeast, char &lifeStatus) override;
	virtual char roomMenu(int inventoryMaxSize, vector<string> &inventory, bool &befriendedBeast) override;
	virtual void roomIntro() override;

	void pickUpPistol(int inventoryMaxSize, vector<string> &inventory);
	void pickUpMeat(int inventoryMaxSize, vector<string> &inventory);

	bool isLockedBeastRoom();

	void beastRoomDoorInteraction(vector<string> &inventory);
	char beastRoomCheck(vector<string> &inventory);
};

#endif