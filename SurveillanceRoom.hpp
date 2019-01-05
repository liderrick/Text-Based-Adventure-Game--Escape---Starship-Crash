/**************************************************************************************************************
** Program name: Final Project
** Author: Derrick Li
** Date: Mar. 21, 2017
** Description:
** This class specification file contains the SurveillanceRoom class declaration. SurveillanceRoom is a derived class
** of the Space base class. The SurveillanceRoom class represents a surveillance room. It is where the player obtains
** the Keycard to add to their inventory.
***************************************************************************************************************/

#ifndef SURVEILLANCEROOM_HPP
#define SURVEILLANCEROOM_HPP

#include "Space.hpp"

class SurveillanceRoom : public Space
{
public:
	SurveillanceRoom();

	virtual Space* roomWrapper(int inventoryMaxSize, vector<string> &inventory, bool &befriendedBeast, char &lifeStatus) override;
	virtual char roomMenu(int inventoryMaxSize, vector<string> &inventory, bool &befriendedBeast) override;
	virtual void roomIntro() override;

	void noteInteraction();
	void pickUpKey(int inventoryMaxSize, vector<string> &inventory);
};

#endif