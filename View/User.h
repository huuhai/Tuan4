#pragma once
#include <iostream>
#include <string>
#include <string.h>

using namespace std;
class User
{
public:
	string username;
	string password;
	string fullname;
	string address;
	string birthday;
	string sex;
	string Friend;
	string receiver;
	string content;
	string block;
	string editInfoFriend;

public:
	User(void);
	~User(void);

	User(string username, string password, string fullname, string birthday, string sex, string address);
	User(string username, string password);
};
