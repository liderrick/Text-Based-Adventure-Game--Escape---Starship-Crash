/**************************************************************************************************************
** Program name: Final Project
** Author: Derrick Li
** Date: Mar. 21, 2017
** Description:
** This class specification file contains the Space abstract base class declaration. The classes that derive
** from the Space base class are: 1) BeastCell class, 2) CargoStorage class, 3) Junction class, 4) PrisonerCell class,
** 5) SurveillanceRoom class, and 6) WeaponsLocker. In a 2D map visualization, a Space object has pointers to the Space
** class object to its immediate top, bottom, left, and right in the 2D plane.
***************************************************************************************************************/

#ifndef SPACE_HPP
#define SPACE_HPP

#include <vector>
#include <string>

using std::vector;
using std::string;

class Space
{
protected:
	Space* top;
	Space* bottom;
	Space* left;
	Space* right;
	
	string roomName;

	vector<string> itemsInRoom;
	bool allItemsPickedUp;

public:
	Space();
	
	void setTop(Space *top);
	void setBottom(Space *bottom);
	void setLeft(Space *left);
	void setRight(Space *right);

	string getRoomName();

	bool isAllItemsPickedUp();

	//virtual functions for the derived classes to override
	virtual Space* roomWrapper(int inventoryMaxSize, vector<string> &inventory, bool &befriendedBeast, char &lifeStatus) = 0;
	virtual char roomMenu(int inventoryMaxSize, vector<string> &inventory, bool &befriendedBeast) = 0;
	virtual void roomIntro() = 0;
};

#endif