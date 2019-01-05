/**************************************************************************************************************
** Program name: Final Project
** Author: Derrick Li
** Date: Mar. 21, 2017
** Description:
** This class implementation file contains the member function definitions for the Space abstract base class.
***************************************************************************************************************/

#include "Space.hpp"

/***************************************************************************************************************
** Description: Space abstract base class constructor. Initializes all Space pointers to nullptr, set the
** roomName data member to an empty string, and allItemPickedUp bool flag to default true (to indicate there
** is nothing in the room).
***************************************************************************************************************/
Space::Space()
{
	top = nullptr;
	bottom = nullptr;
	left = nullptr;
	right = nullptr;

	roomName = "";

	allItemsPickedUp = true;
}

/***************************************************************************************************************
** Description: setTop() function takes in a pointer to a Space class object and sets the top Space pointer.
** The top Space pointer represents the room that is to the immediate north of the current room. The function 
** does not have a return type.
***************************************************************************************************************/
void Space::setTop(Space * top)
{
	this->top = top;
}

/***************************************************************************************************************
** Description: setBottom() function takes in a pointer to a Space class object and sets the bottom Space pointer.
** The bottom Space pointer represents the room that is to the immediate south of the current room. The function 
** does not have a return type.
***************************************************************************************************************/
void Space::setBottom(Space * bottom)
{
	this->bottom = bottom;
}

/***************************************************************************************************************
** Description: setLeft() function takes in a pointer to a Space class object and sets the left Space pointer.
** The left Space pointer represents the room that is to the immediate west of the current room. The function 
** does not have a return type.
***************************************************************************************************************/
void Space::setLeft(Space * left)
{
	this->left = left;
}

/***************************************************************************************************************
** Description: setRight() function takes in a pointer to a Space class object and sets the right Space pointer.
** The right Space pointer represents the room that is to the immediate east of the current room. The function 
** does not have a return type.
***************************************************************************************************************/
void Space::setRight(Space * right)
{
	this->right = right;
}

/***************************************************************************************************************
** Description: getRoomName() function returns roomName (string). The function does not take in any arguments.
***************************************************************************************************************/
string Space::getRoomName()
{
	return roomName;
}

/***************************************************************************************************************
** Description: isAllItemsPickedUp() function returns allItemsPickedUp (bool). The function does not take in any arguments.
***************************************************************************************************************/
bool Space::isAllItemsPickedUp()
{
	return allItemsPickedUp;
}
