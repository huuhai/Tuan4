#pragma once
#include <iostream>
#include <conio.h>
#include "Menu_Display.h"
#include <sstream>
#include "Controller.h"

using namespace std;

class Menu
{
public:

	Menu(void);
	~Menu(void);

	UserView userView;

	Menu_Display menu_Display;

	void choice1();

	void choice2(string username, string password);

	void choice3(string username);

	void choice4(string username);

	void choice5(string username);
};