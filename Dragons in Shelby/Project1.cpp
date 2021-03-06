/*
Author: James Malloy
email:	jem0044@tigermail.auburn.edu
id:		903518039

FileName: Project1.cpp


Compilation:
g++ -Wall -std=c++11 -c -o resources.o resources.cpp
g++ -Wall -std=c++11 -c -o MMC.o MenuManagerClass.cpp
g++ -Wall -std=c++11 -c -o SMC.o ScoreManagerClass.cpp
g++ -Wall -std=c++11 -c -o EN.o Encounters.cpp
g++ -Wall -std=c++11 -c -o EMC.o EncounterManagerClass.cpp
g++ -Wall -std=c++11 -c -o PCC.o PlayerCharacterClass.cpp
g++ -Wall -std=c++11 -c -o GIC.o GameInstanceClass.cpp
g++ -Wall -std=c++11 -c -o Project1.o Project1.cpp

g++ -Wall -std=c++11 -o EX02 resources.o MMC.o SMC.o EN.o EMC.o PCC.o GIC.o Project1.o

Yes I'm sorry about all this. Visual studio makes it a lot
easier to use a bunch of files, so I wasn't thinking about the
pain of command line compilation for my program.


Sources:
https://msdn.microsoft.com/en-us/library/cc953fe1.aspx
http://www.cprogramming.com/tutorial/bitwise_operators.html
http://www.cplusplus.com/reference/cstdlib/rand/
http://stackoverflow.com/questions/134731/returning-a-const-reference-to-an-object-instead-of-a-copy
http://stackoverflow.com/questions/1143262/what-is-the-difference-between-const-int-const-int-const-and-int-const
http://stackoverflow.com/questions/8280023/does-a-c-struct-have-a-default-constructor
https://www.visualstudio.com/en-us/docs/git/tutorial/merging
https://www.tutorialspoint.com/cplusplus/cpp_arrays.htm
http://www.cprogramming.com/tutorial/lesson9.html
http://stackoverflow.com/questions/3323675/c-fastest-method-to-return-a-c-string
http://stackoverflow.com/questions/4847100/c-inheritance-inaccessible-base
http://www.studytonight.com/cpp/virtual-functions.php
http://www.cplusplus.com/reference/ios/left/


Description:
This file contains the main function for the game Shelby Center and Dragons.

This is a game where you are supposed to reach the end of a hall in Shelby.
You have a limited amount of intelligence, money, time. If any of these
reach 0, you lose the game. 

The structure of the game uses an object oriented structure. See the header
files for comments about the purpose of each of these classes.

*/

#define VersionNumber 0.90

#ifdef _WIN32
#include "stdafx.h"
#include <Windows.h>
#endif

#define FONT_SIZE 25

#include "resources.h"
#include "MenuManagerClass.h"
#include "PlayerCharacterClass.h"
#include "EncounterManagerClass.h"
#include "GameInstanceClass.h"
#include "ScoreManagerClass.h"

HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

int main()
{
#ifdef _WIN32 //code used from http://mycodecollection.blogspot.com/2015/01/c-console-change-font-size.html
	PCONSOLE_FONT_INFOEX lpConsoleCurrentFontEx = new CONSOLE_FONT_INFOEX();
	lpConsoleCurrentFontEx->cbSize = sizeof(CONSOLE_FONT_INFOEX);
	GetCurrentConsoleFontEx(out, 0, lpConsoleCurrentFontEx);
	lpConsoleCurrentFontEx->dwFontSize.X = FONT_SIZE;
	lpConsoleCurrentFontEx->dwFontSize.Y = FONT_SIZE;
	SetCurrentConsoleFontEx(out, 0, lpConsoleCurrentFontEx);

	system("color F0");
#endif

	string name;

	cout << "Welcome to the game!\n";
	cout << "Please enter your name: ";
	cin >> name;
	cout << endl;



	srand(time(0));

	int i = 0;

	MenuManagerClass * menuInterface = new MenuManagerClass();
	GameInstanceClass * gameInstance = 0;
	ScoreManagerClass * scoreInterface = new ScoreManagerClass();

	flag gameStatus;


	while (i != UserExitCode)
	{
		cout << "================================================\n";
		cout << "        Shelby Center and Dragons v" << VersionNumber;

#if DEBUG_MODE
		cout << "\n		DEBUG MODE";
#endif
		cout << endl;

		cout << "            Unholy Pact Edition\n";

		cout << "================================================\n";
		cout << "		Player: " << name << endl << endl;

		i = menuInterface->DisplayMainMenu();

		if (i == 0)
		{

			gameInstance = new GameInstanceClass(name, menuInterface, scoreInterface);
			gameStatus = gameInstance->run();
			gameInstance->clean();
			delete gameInstance;
			gameInstance = 0;


			if ((gameStatus & FunctionErrorFlag) != 0)
			{
				system("pause");
				return 1;
			}


		}
		else if (i == 1)
		{
			scoreInterface->outputScores();
		}

		cout << endl;
	}


	delete menuInterface;
	delete scoreInterface;
	

    return 0;
}

