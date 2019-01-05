/**************************************************************************************************************
** Program name: Final Project
** Author: Derrick Li
** Date: Mar. 21, 2017
** Description:
** This class specification file contains the Game class declaration. It constructs a map out of the Space
** dervied classes. The class keeps track of the playing mechanics - i.e. the player's current room, whether
** or not the player has befriended the Beast, the player's inventory, and the amount of "time" the player has.
** In this game, "time" is a measure of the number of actions the player does, i.e. travel to another room or
** interact with an item.
***************************************************************************************************************/

#ifndef GAME_HPP
#define GAME_HPP

#include "Space.hpp"
#include "PrisonerCell.hpp"
#include "Junction.hpp"
#include "SurveillanceRoom.hpp"
#include "WeaponsLocker.hpp"
#include "CargoStorage.hpp"
#include "BeastCell.hpp"

#include <string>
#include <vector>

using std::string;
using std::vector;

class Game
{
private:
	PrisonerCell pCell;
	Junction junct;
	WeaponsLocker wLocker;
	SurveillanceRoom sRoom;
	CargoStorage cStorage;
	BeastCell bCell;
	
	Space* playerPosition;

	bool befriendedBeast;
	char lifeStatus;

	vector<string> inventory;
	int inventoryMaxSize;

	int stepsTaken;

public:
	Game();

	void printInventory();

	void timeMechanism();
	void testLifeStatus();
	
	char playGame();
};

#endif