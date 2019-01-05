/**************************************************************************************************************
** Program name: Final Project
** Author: Derrick Li
** Date: Mar. 21, 2017
** Description:
** This class specification file contains the WeaponsLocker class declaration. WeaponsLocker is a derived class
** of the Space base class. The WeaponsLocker class represents a room with a weapons locker. It is where the player
** obains the Laser to add to their inventory.
***************************************************************************************************************/

#ifndef WEAPONSLOCKER_HPP
#define WEAPONSLOCKER_HPP

#include "Space.hpp"

class WeaponsLocker : public Space
{
public:
	WeaponsLocker();

	virtual Space* roomWrapper(int inventoryMaxSize, vector<string> &inventory, bool &befriendedBeast, char &lifeStatus) override;
	virtual char roomMenu(int inventoryMaxSize, vector<string> &inventory, bool &befriendedBeast) override;
	virtual void roomIntro() override;

	void pickUpLaser(int inventoryMaxSize, vector<string> &inventory);
};

#endif