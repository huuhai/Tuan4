#pragma once
#include <iostream>
#include <stdio.h>
#include <ctime>
#include "sqlite3.h"
#include "Menu.h"
#include <sstream>

using namespace std;

class Database
{	
public:
	sqlite3_stmt* stmt;
	sqlite3 *database;
	int rc;
	char *zErrMsg;
	const char* data;

public:
	Database(void);
	~Database(void);

	void connect();

	void close();
	
	void signUp(string username, string password, string fullname, string birthday, string sex, string address);
	
	void logIn(string username, string password);
	
	bool check(string username, string password);
	
	bool check(string username);

	void listFriend(string username);

	bool checkTableFriend(string username, string Friend);

	void addFriend(string username, string Friend);

	void sendMessage(string sender, string receiver, string content);

	bool checkBlock(string username, string block);

	void block(string username, string block);

	// kiểm tra receiver có tồn tại trong bảng Message ko
	bool checkReceivedMessage(string receiver);

	void showMessageSent(string sender);

	//cập nhật trạng thái đã đọc
	void updateSeenMessage(string sql);

	void showMessageReceived(string receiver);

	void showInfo(string username);

	void showInfoFriend(string username, string Friend);

	void editInfoFriend(string Friend, string fullname, string birthday, string sex, string address);

	void Ctrl_L(string username);

	bool checkID(string id);

	void sendMessage_Ctr_L(string id, string content);

	// sắp xếp theo thời gian gửi, nhận tin nhắn mới nhất trước
	void sortFriend(string username);

	// sắp xếp theo thành phố
	void sortFriendOfCity(string username);
};