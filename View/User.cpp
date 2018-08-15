#include "stdafx.h"
#include "User.h"


User::User(void)
{
}


User::~User(void)
{
}

User::User(string username, string password, string fullname, string address, string birthday, string sex){
	this->username=username;
	this->password=password;
	this->fullname=fullname;
	this->address=address;
	this->birthday=birthday;
	this->sex=sex;
}

User::User(string username, string password){
	this->username=username;
	this->password=password;
}