/**************************************************************************************************************
** Program name: Final Project
** Author: Derrick Li
** Date: Mar. 21, 2017
** Description:
** This implementation file contains definitions for menu-related and input/output functions.
***************************************************************************************************************/

#include "menu.hpp"

#include <iostream>
#include <string>
#include <exception>

using std::endl;
using std::cout;
using std::cin;

using std::string;
using std::exception;

/***************************************************************************************************************
** Description: gameIntro() function prints a brief introduction to the game. The function does not take in any
** arguments and does not have a return type.
***************************************************************************************************************/
void gameIntro()
{
	cout << endl <<
		"-----------------------------------------------------------------------------" << endl <<
		"Welcome to ESCAPE: STARSHIP CRASH!" << endl << endl <<
		"You're a PRISONER onboard a STARSHIP. You've just CRASH LANDED." << endl <<
		"There's an opportunity for you to ESCAPE! Will you take it?" << endl;
}

/***************************************************************************************************************
** Description: mainMenu() function displays the main menu and prompts the user to select an option. The
** input validation ensures a valid option has been chosen. The function returns this integer value.
** It does not take any argument. Revision 06Feb17 to work with inputIntegerValidationV2 function.
***************************************************************************************************************/
int mainMenu()
{
	bool validInteger = false;
	bool validChoice = false;
	int choice = 0;

	do
	{
		cout << endl << "Please select an option:" << endl;
		cout << "1) Play the game" << endl;
		cout << "9) Exit" << endl;
		cout << "Choice: ";
		validInteger = inputIntegerValidationV3(choice);

		if (validInteger && (choice == 1 || choice == 9))
		{
			validChoice = true;
		}
		else
		{
			cout << "Invalid choice. Try again." << endl;
		}

	} while (validChoice == false);

	return choice;
}

/***************************************************************************************************************
** Description: inputIntegerValidationV3() function validates an integer has been entered. If
** it has, the integer is returned as a reference parameter and true is returned as a bool from the function.
** If not, 0 is returned to its reference parameter and false is returned as a bool from the function.
** Based on original function, inputIntegerValidation.
** V2 version can validate negative values. Revision 06Feb17.
** V3 version does not consider floating point values as valid integers. Revision 16Mar17
***************************************************************************************************************/
bool inputIntegerValidationV3(int &num)
{
	num = 0; //initialize 0 as default

	bool validInteger = false;

	string inputString;
	getline(cin, inputString);

	//searches inputString for decimal
	//if no decimal found, attempt stoi
	if (inputString.find(".") == std::string::npos)  
	{
		try   
		{
			num = stoi(inputString);
			validInteger = true;
		}
		catch (exception e)
		{
			validInteger = false;
		}
	}

	return validInteger;
}

/***************************************************************************************************************
** Description: promptAuthorizationCode() function prompts the user to enter a non-negative integer. The
** input is validated to ensure a valid integer has been entered. The function returns this integer value.
** It does not take any argument.
***************************************************************************************************************/
int promptAuthorizationCode()
{
	bool validInteger = false;
	bool validChoice = false;
	int choice = 0;

	do
	{
		cout <<"   SYSTEM: Enter Authorization Code: ";
		validInteger = inputIntegerValidationV3(choice);

		if (validInteger && choice >= 0)
		{
			validChoice = true;
		}
		else
		{
			cout << "   SYSTEM: Invalid entry. Try again." << endl << endl;
		}

	} while (validChoice == false);

	return choice;
}

/***************************************************************************************************************
** Description: pressEnterToContinue() function prompts the user to press [Enter] to continue.
** The function does not take in any arguments and does not have a return type.
***************************************************************************************************************/
void pressEnterToContinue()
{
	cout << endl <<
		"-----------------------------------------------------------------------------" << endl <<
		"Press [ENTER] to continue." << endl;
	cin.ignore();
}