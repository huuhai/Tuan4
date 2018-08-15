#include "stdafx.h"
#include "Database.h"


Database::Database(void)
{
}


Database::~Database(void)
{
}

void Database::connect()
{
	rc = sqlite3_open("CoSoDuLieu.db", &database);
	if (rc)
	{	   
		sqlite3_close(database);
		//return false;
		cout<<"\tket noi ko thanh cong !!!";
	}
	else{
		//return true;
		//cout<<"\tket noi thanh cong !!!";
	}
}

void Database::close()
{
	sqlite3_close(database);
}

void Database::signUp(string username, string password, string fullname, string birthday, string sex, string address)
{
	if(!check(username, password)){
		string query = "INSERT INTO AccountInfo(username, password, fullname, birthday, sex, address) "
			"VALUES('"+username+"', '"+password+"' ,'"+fullname+"', '"+birthday+"', '"+sex+"', '"+address+"')";

		rc = sqlite3_exec(database, query.c_str(),sqlite3_callback(),0, &zErrMsg);
		if( rc != SQLITE_OK ){
			fprintf(stderr, "\n\tSQL error: %s\n", zErrMsg);
			sqlite3_free(zErrMsg);
		}
		else{
			fprintf(stdout, "\n\t\t\tDang ky thanh cong !!!\n");
		}
	}
	else
	{
		cout<<endl<<"\tDa ton tai trong database. Chon tai khoan khac !!!"<<endl;
	}
}

void Database::logIn(string username, string password){

	Menu menu;
	system("cls");
	if(check(username, password)){
		menu.choice2(username,password);
	}
	else
	{
		cout<<endl<<"Dang nhap ko thanh cong !!!"<<endl;
	}
}	 

bool Database::check(string username, string password){
	string sql = "select username, password from AccountInfo where username = '"+username+"' and password = '"+password+"'";
	SQLITE_CALLBACK (sqlite3_prepare_v2 (database, sql.c_str(), sql.length() + 1, &stmt, NULL));
	int row = 0;
	while (1) {
		int s;
		s = sqlite3_step (stmt);
		if (s == SQLITE_ROW) {
			const unsigned char * text1;
			const unsigned char * text2;

			text1  = sqlite3_column_text (stmt, 0);
			text2  = sqlite3_column_text (stmt, 1);
			sqlite3_finalize(stmt);
			return true;
			row++;
		}
		else if (s == SQLITE_DONE) {
			sqlite3_finalize(stmt);
			return false;
			break;
		}
		else {
			sqlite3_finalize(stmt);
			fprintf (stderr, "Failed.\n");
			exit (1);
		}
	}
}

void Database::addFriend(string username, string Friend){
	// tra ve date/time hien tai dua tren system hien tai
	time_t hientai = time(0);

	// chuyen doi hientai thanh dang chuoi
	char* dt = ctime(&hientai);

	if(!check(Friend)){
		cout<<endl<<"\t\tTai khoan ko ton tai hoac da bi xoa !!!"<<endl;	
	}
	else
	{
		if(!checkTableFriend(username,Friend)){
			string query = "INSERT INTO Friend(username, friend, TimeDate) VALUES ('"+username+"', '"+Friend+"', '"+dt+"')";
			rc = sqlite3_exec(database, query.c_str(),sqlite3_callback(),0, &zErrMsg);
			if( rc != SQLITE_OK ){
				fprintf(stderr, "\n\tSQL error: %s\n", zErrMsg);
				sqlite3_finalize(stmt);
			}
			else{
				fprintf(stdout, "\n\t\t\tThem thanh cong !!!\n");
				sqlite3_finalize(stmt);
			}
		}
		else
		{
			sqlite3_finalize(stmt);
			cout<<endl<<"\tKo the them. Tai khoan nay da nam trong danh sach ban be !!!"<<endl;
		}
	}
}

bool Database::checkTableFriend(string username, string Friend)
{
	string sql = "select friend from Friend where username ='"+username+"' and friend ='"+Friend+"'";
	SQLITE_CALLBACK (sqlite3_prepare_v2 (database, sql.c_str(), sql.length() + 1, &stmt, NULL));
	int row = 0;
	while (1) {
		int s;
		s = sqlite3_step (stmt);
		if (s == SQLITE_ROW) {
			const unsigned char * text0;

			text0  = sqlite3_column_text (stmt, 0);
			return true;
			row++;
			sqlite3_finalize(stmt);
		}
		else if (s == SQLITE_DONE) {
			return false;
			break;
		}
		else {
			sqlite3_finalize(stmt);
			fprintf (stderr, "Failed.\n");
			exit (1);
		}
	}
}

void Database::listFriend(string username){

	string sql = "select id, friend, TimeDate from Friend where username='"+username+"' order by TimeDate desc";
	SQLITE_CALLBACK (sqlite3_prepare_v2 (database, sql.c_str(), sql.length() + 1, &stmt, NULL));
	int row = 0;
	while (1) {
		int s;
		s = sqlite3_step (stmt);
		if (s == SQLITE_ROW) {
			unsigned int id;
			const unsigned char* Friend;
			const unsigned char* TimeDate;

			id  = sqlite3_column_int (stmt, 0);
			Friend  = sqlite3_column_text (stmt, 1);
			TimeDate  = sqlite3_column_text (stmt, 2);
			printf("\tID: %d \tTen ban be: %s \tKet ban luc: %s\n", id,Friend,TimeDate);
			row++;
		}
		else if (s == SQLITE_DONE) {
			sqlite3_finalize(stmt);
			break;
		}
		else {
			sqlite3_finalize(stmt);
			fprintf (stderr, "Failed.\n");
			exit (1);
		}
	}
}

bool Database::check(string username){
	string sql = "select username from AccountInfo where username = '"+username+"'";
	SQLITE_CALLBACK (sqlite3_prepare_v2 (database, sql.c_str(), sql.length() + 1, &stmt, NULL));
	int row = 0;
	while (1) {
		int s;
		s = sqlite3_step (stmt);
		if (s == SQLITE_ROW) {
			const unsigned char * text1;

			text1  = sqlite3_column_text (stmt, 0);
			return true;
			row++;
			sqlite3_finalize(stmt);
		}
		else if (s == SQLITE_DONE) {
			sqlite3_finalize(stmt);
			return false;
			break;
		}
		else {
			sqlite3_finalize(stmt);
			fprintf (stderr, "Failed.\n");
			exit (1);
		}
	}
}

void Database::sendMessage(string sender, string receiver, string content){
	// tra ve date/time hien tai dua tren system hien tai
	time_t hientai = time(0);

	// chuyen doi hientai thanh dang chuoi
	char* dt = ctime(&hientai);

	if(!check(receiver)){
		sqlite3_finalize(stmt);
		cout<<endl<<"Tai khoan ko ton tai hoac da bi xoa !!!"<<endl;
	}
	else
	{
		if (!checkBlock(receiver,sender))
		{
			string query = "INSERT INTO Message(sender, receiver, content, TimeDate) VALUES ('"+sender+"','"+receiver+"','"+content+"', '"+dt+"')";
			rc = sqlite3_exec(database, query.c_str(),sqlite3_callback(),0, &zErrMsg);
			if( rc != SQLITE_OK ){
				sqlite3_finalize(stmt);
				fprintf(stderr, "\n\tSQL error: %s\n", zErrMsg);
			}
			else{
				sqlite3_finalize(stmt);
				fprintf(stdout, "\n\t\tGui thanh cong !!!\n");
			}
		}
		else
		{
			sqlite3_finalize(stmt);
			cout<< "\tKo the gui tin nhan. '"<<receiver<<"' da chan ban !!!";
		}
	}
}

void Database::block(string username, string block){
	if(!check(block)){
		cout<<endl<<"Tai khoan ko ton tai hoac da bi xoa !!!"<<endl;
	}
	else
	{
		if (!checkBlock(username, block))
		{
			string sql = "insert into Block(username, blocked) values ('"+username+"', '"+block+"')";
			rc = sqlite3_exec(database, sql.c_str(),sqlite3_callback(),0, &zErrMsg);
			if( rc != SQLITE_OK ){
				sqlite3_finalize(stmt);
				fprintf(stderr, "\n\tSQL error: %s\n", zErrMsg);
			}
			else{
				sqlite3_finalize(stmt);
				fprintf(stdout, "\n\t\tBlock thanh cong !!!\n");
			}
		}
		else
		{
			cout<<endl<<"\tKo the Block. Tai khoan nay da bi Block truoc do !!!";
		}
	}
}

bool Database::checkBlock(string username, string block)
{
	string sql = "select blocked from Block where username='"+username+"' and blocked='"+block+"'";
	SQLITE_CALLBACK (sqlite3_prepare_v2 (database, sql.c_str(), sql.length() + 1, &stmt, NULL));
	int row = 0;
	while (1) {
		int s;
		s = sqlite3_step (stmt);
		if (s == SQLITE_ROW) {
			int bytes;
			const unsigned char* text0;
			bytes = sqlite3_column_bytes (stmt, 0);
			text0  = sqlite3_column_text (stmt, 0);
			return true;
			row++;
			sqlite3_finalize(stmt);
		}
		else if (s == SQLITE_DONE) {
			return false;
			break;
		}
		else {
			sqlite3_finalize(stmt);
			fprintf (stderr, "Failed.\n");
			exit (1);
		}
	}
}

void Database::showMessageSent(string sender){
	string sql = "select receiver, content, TimeDate, seen from Message where sender = '"+sender+"'";
	SQLITE_CALLBACK (sqlite3_prepare_v2 (database, sql.c_str(), sql.length() + 1, &stmt, NULL));
	int row = 0;
	while (1) {
		int s;
		s = sqlite3_step (stmt);
		if (s == SQLITE_ROW) {
			const unsigned char* receiver;
			const unsigned char* content;
			const unsigned char* TimeDate;
			const unsigned char* seen;

			receiver  = sqlite3_column_text (stmt, 0);
			content  = sqlite3_column_text (stmt, 1);
			TimeDate  = sqlite3_column_text (stmt, 2);
			seen  = sqlite3_column_text (stmt, 3);

			char Ctr_key;
			Ctr_key=_getch();
			if(Ctr_key==14)
			{
				printf("Nguoi nhan: %s  Noi dung: %s  Thoi gian gui: %s  Tinh trang: %s\n", receiver, content, TimeDate, seen);
				row++;
			}
			else if (Ctr_key==2)
			{
				break;
			}
		}
		else if (s == SQLITE_DONE) {
			sqlite3_finalize(stmt);
			break;
		}
		else {
			sqlite3_finalize(stmt);
			fprintf (stderr, "Failed.\n");
			exit (1);
		}
	}
}

void Database::updateSeenMessage(string query)
{
	//string query = "update Message set seen ='da doc' where receiver='"+receiver+"'";
	rc = sqlite3_exec(database, query.c_str(),sqlite3_callback(),0, &zErrMsg);
	if( rc != SQLITE_OK ){
		sqlite3_finalize(stmt);
		fprintf(stderr, "\n\tSQL error: %s\n", zErrMsg);
	}
	else{
		sqlite3_finalize(stmt);
	}
}

void Database::showMessageReceived(string receiver){
	if (checkReceivedMessage(receiver))
	{
		string query = "update Message set seen ='da doc' where receiver='"+receiver+"'";
		updateSeenMessage(query);
		string sql = "select sender, content, TimeDate from Message where receiver = '"+receiver+"'";
		SQLITE_CALLBACK (sqlite3_prepare_v2 (database, sql.c_str(), sql.length() + 1, &stmt, NULL));
		int row = 0;
		while (1) {
			int s;
			s = sqlite3_step (stmt);
			if (s == SQLITE_ROW) {
				const unsigned char* sender;
				const unsigned char* content;
				const unsigned char* TimeDate;

				sender  = sqlite3_column_text (stmt, 0);
				content  = sqlite3_column_text (stmt, 1);
				TimeDate  = sqlite3_column_text (stmt, 2);
				char Ctr_key;
				Ctr_key=_getch();
				if(Ctr_key==14)
				{
					printf("Nguoi gui: %s  Noi dung: %s  Thoi gian gui: %s\n", sender, content, TimeDate);
					row++;
				}
				else if (Ctr_key==2)
				{
					break;
				}
			}
			else if (s == SQLITE_DONE) {
				sqlite3_finalize(stmt);
				break;
			}
			else {
				sqlite3_finalize(stmt);
				fprintf (stderr, "Failed.\n");
				exit (1);
			}
		}
	}
	else
	{
		cout<<endl<<endl<<"\t\tChua nhan duoc tin nhan nao !!!"<<endl<<endl;
	}
}

bool Database::checkReceivedMessage(string receiver)
{
	string sql = "select distinct receiver from Message where receiver ='"+receiver+"'";
	SQLITE_CALLBACK (sqlite3_prepare_v2 (database, sql.c_str(), sql.length() + 1, &stmt, NULL));
	int row = 0;
	while (1) {
		int s;
		s = sqlite3_step (stmt);
		if (s == SQLITE_ROW) {
			int bytes;
			const unsigned char * text1;
			bytes = sqlite3_column_bytes (stmt, 0);
			text1  = sqlite3_column_text (stmt, 0);
			return true;
			row++;
			sqlite3_finalize(stmt);
		}
		else if (s == SQLITE_DONE) {
			sqlite3_finalize(stmt);
			return false;
			break;
		}
		else {
			sqlite3_finalize(stmt);
			fprintf (stderr, "Failed.\n");
			exit (1);
		}
	}
}

void Database::showInfo(string username){
	string sql = "select * from AccountInfo where username = '"+username+"'";
	SQLITE_CALLBACK (sqlite3_prepare_v2 (database, sql.c_str(), sql.length() + 1, &stmt, NULL));
	int row = 0;
	while (1) {
		int s;
		s = sqlite3_step (stmt);
		if (s == SQLITE_ROW) {

			const unsigned char* text0;
			const unsigned char* text1;
			const unsigned char* text2;
			const unsigned char* text3;
			const unsigned char* text4;
			const unsigned char* text5;

			text0  = sqlite3_column_text (stmt, 0);
			text1  = sqlite3_column_text (stmt, 1);
			text2  = sqlite3_column_text (stmt, 2);
			text3  = sqlite3_column_text (stmt, 3);
			text4  = sqlite3_column_text (stmt, 4);
			text5  = sqlite3_column_text (stmt, 5);

			printf ("\nusername: %s\npassword: %s\nfullname: %s\nbirthday: %s\nsex: %s\naddress: %s\n", text0, text1, text2, text3, text4, text5);
			row++;
		}
		else if (s == SQLITE_DONE) {
			sqlite3_finalize(stmt);
			break;
		}
		else {
			sqlite3_finalize(stmt);
			fprintf (stderr, "Failed.\n");
			exit (1);
		}
	}
}

void Database::editInfoFriend(string Friend, string fullname, string birthday, string sex, string address)
{
	string sql="update AccountInfo set fullname='"+fullname+"', birthday='"+birthday+"', sex='"+sex+"', address='"+address+"' where username='"+Friend+"'";
	rc = sqlite3_exec(database, sql.c_str(),sqlite3_callback(),0, &zErrMsg);
	if( rc != SQLITE_OK ){
		sqlite3_finalize(stmt);
		fprintf(stderr, "\n\tSQL error: %s\n", zErrMsg);
	}
	else{
		cout<<endl<<"\t\tUpdate thanh cong !!!"<<endl;
	}
}

void Database::showInfoFriend(string username, string Friend)
{
	string sql = "select AccountInfo.fullname, AccountInfo.birthday, AccountInfo.sex, AccountInfo.address, Friend.TimeDate "
		"from AccountInfo,Friend "
		"where AccountInfo.username=Friend.friend and Friend.username='"+username+"' and Friend.friend='"+Friend+"'";
	SQLITE_CALLBACK (sqlite3_prepare_v2 (database, sql.c_str(), sql.length() + 1, &stmt, NULL));
	int row = 0;
	while (1) {
		int s;
		s = sqlite3_step (stmt);
		if (s == SQLITE_ROW) {
			const unsigned char* text0;
			const unsigned char* text1;
			const unsigned char* text2;
			const unsigned char* text3;
			const unsigned char* text4;

			text0  = sqlite3_column_text (stmt, 0);
			text1  = sqlite3_column_text (stmt, 1);
			text2  = sqlite3_column_text (stmt, 2);
			text3  = sqlite3_column_text (stmt, 3);
			text4  = sqlite3_column_text (stmt, 4);

			printf ("\nHo ten day du: %s\nNgay sinh: %s\nGioi tinh: %s\nDia chi: %s\nThoi gian ket ban: %s\n", text0, text1, text2, text3, text4);
			row++;
		}
		else if (s == SQLITE_DONE) {
			sqlite3_finalize(stmt);
			break;
		}
		else {
			sqlite3_finalize(stmt);
			fprintf (stderr, "Failed.\n");
			exit (1);
		}
	}
}

void Database::Ctrl_L(string username){
	listFriend(username);
	string id;
	cout<<endl<<"Nhap ID de gui tin nhan: ";
	getline(cin,id);
	if(checkID(id)){
		string content;
		cout<< "Noi dung tin nhan: ";
		getline(cin, content);
		fflush(stdin);
		sendMessage_Ctr_L(id, content);
	}
	else
	{
		cout<< "\tNhap sai ID hoac tai khoan ko ton tai !!!"<<endl;
	}
}

void Database::sendMessage_Ctr_L(string id, string content)
{
	string sql = "select username, friend from Friend where id='"+id+"'";
	SQLITE_CALLBACK (sqlite3_prepare_v2 (database, sql.c_str(), sql.length() + 1, &stmt, NULL));
	int row = 0;
	stringstream ss1;
	stringstream ss2;
	string username1="";
	string Friend1="";
	while (1) {
		int s;
		s = sqlite3_step (stmt);
		if (s == SQLITE_ROW) {
			const unsigned char* username;
			const unsigned char* Friend;
			username  = sqlite3_column_text (stmt, 0);
			Friend  = sqlite3_column_text (stmt, 1);
			ss1<<username;
			ss1>>username1;
			ss2<<Friend;
			ss2>>Friend1;
			row++;
		}
		else if (s == SQLITE_DONE) {
			sqlite3_finalize(stmt);
			break;
		}
		else {
			sqlite3_finalize(stmt);
			fprintf (stderr, "Failed.\n");
			exit (1);
		}
	}
	sendMessage(username1,Friend1, content);
}

bool Database::checkID(string id)
{
	string sql = "select id, friend from Friend where id='"+id+"'";
	SQLITE_CALLBACK (sqlite3_prepare_v2 (database, sql.c_str(), sql.length() + 1, &stmt, NULL));
	int row = 0;
	while (1) {
		int s;
		s = sqlite3_step (stmt);
		if (s == SQLITE_ROW) {
			const unsigned char* id;
			const unsigned char* Friend;
			id  = sqlite3_column_text (stmt, 0);
			Friend  = sqlite3_column_text (stmt, 1);
			cout<<"Gui tin nhan den: "<<Friend<<endl;
			return true;
			row++;
			sqlite3_finalize(stmt);
		}
		else if (s == SQLITE_DONE) {
			return false;
			break;
		}
		else {
			sqlite3_finalize(stmt);
			fprintf (stderr, "Failed.\n");
			exit (1);
		}
	}
}

// sắp xếp theo thời gian gửi, nhận tin nhắn mới nhất trước
void Database::sortFriend(string username)
{
	string sql = "select distinct Friend.friend, Friend.TimeDate from Friend, Message "
		"where Friend.username='"+username+"' and Friend.username=Message.sender and Friend.friend=Message.receiver "
		"order by Message.TimeDate desc";
	SQLITE_CALLBACK (sqlite3_prepare_v2 (database, sql.c_str(), sql.length() + 1, &stmt, NULL));
	int row = 0;
	while (1) {
		int s;
		s = sqlite3_step (stmt);
		if (s == SQLITE_ROW) {

			const unsigned char* Friend;
			const unsigned char* TimeDate;

			Friend  = sqlite3_column_text (stmt, 0);
			TimeDate  = sqlite3_column_text (stmt, 1);
			printf ("\tBan be: %s  Ket ban luc: %s\n", Friend, TimeDate);
			row++;
		}
		else if (s == SQLITE_DONE) {
			sqlite3_finalize(stmt);
			break;
		}
		else {
			sqlite3_finalize(stmt);
			fprintf (stderr, "Failed.\n");
			exit (1);
		}
	}
}

// sắp xếp theo thành phố
void Database::sortFriendOfCity(string username)
{
	string sql = "select Friend.id, Friend.friend, AccountInfo.address " 
		"from Friend, AccountInfo "
		"where Friend.username='"+username+"' and Friend.friend=AccountInfo.username " 
		"order by address asc, friend asc";
	SQLITE_CALLBACK (sqlite3_prepare_v2 (database, sql.c_str(), sql.length() + 1, &stmt, NULL));
	int row = 0;
	while (1) {
		int s;
		s = sqlite3_step (stmt);
		if (s == SQLITE_ROW) {

			const unsigned char* id;
			const unsigned char* Friend;
			const unsigned char* address;

			id  = sqlite3_column_text (stmt, 0);
			Friend  = sqlite3_column_text (stmt, 1);
			address  = sqlite3_column_text (stmt, 2);
			printf ("ID: %s  Ban be: %s  Dia chi: %s\n", id, Friend, address);
			row++;
		}
		else if (s == SQLITE_DONE) {
			sqlite3_finalize(stmt);
			break;
		}
		else {
			sqlite3_finalize(stmt);
			fprintf (stderr, "Failed.\n");
			exit (1);
		}
	}
}