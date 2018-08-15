#pragma once
#include "UserView.h"
#include <iostream>
#include "Database.h"
#include "Menu.h"

using namespace std;

class Controller
{
public:
	Controller(void);
	~Controller(void);

	UserView userView;

	 void signUp();

	 void logIn();

	 void close();

	 void showMessageSent(string username);

	 void showMessageReceiver(string username);

	 void sendMessage(string username);

	 void addFriend(string username);

	 void listFriend(string username);

	 void sortFriend(string username);

	 void sortFriendOfCity(string username);

	 void block(string username);

	 void showInfo(string username);

	 void editInfoFriend(string username);

	 void Ctr_L(string username);
};

