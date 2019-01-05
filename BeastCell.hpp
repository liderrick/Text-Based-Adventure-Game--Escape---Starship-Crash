/**************************************************************************************************************
** Program name: Final Project
** Author: Derrick Li
** Date: Mar. 21, 2017
** Description:
** This class specification file contains the BeastCell class declaration. BeastCell is a derived class of the
** Space base class. The BeastCell class represents the room in which the Beast is contained in. It is where
** The player will befriend the Beast.
***************************************************************************************************************/

#ifndef BEASTCELL_HPP
#define BEASTCELL_HPP

#include "Space.hpp"

class BeastCell : public Space
{
protected:
	bool beastInCell;

public:
	BeastCell();

	virtual Space* roomWrapper(int inventoryMaxSize, vector<string> &inventory, bool &befriendedBeast, char &lifeStatus) override;
	virtual char roomMenu(int inventoryMaxSize, vector<string> &inventory, bool &befriendedBeast) override;
	virtual void roomIntro() override;

	char interactWithBeast(vector<string> &inventory, bool &befriendedBeast);
};

#endif