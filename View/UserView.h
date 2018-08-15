#pragma once
#include <iostream>
#include "User.h"

using namespace std;
class UserView: public User{
public:
	UserView(void);
	~UserView(void);

	void nhap();
	void dangKy();

	void nhanTin();
};

