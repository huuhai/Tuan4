#include "stdafx.h"
#include "Controller.h"

Database database;

Controller::Controller(void)
{
}


Controller::~Controller(void)
{
}


void Controller::signUp()
{
	database.connect();
	userView.dangKy();
	database.signUp(userView.username, userView.password, userView.fullname, userView.birthday, userView.sex, userView.address);
}

void Controller::logIn()
{
	database.connect();
	userView.nhap();
	database.logIn(userView.username, userView.password);
}

void Controller::close()
{
	database.close();
}

void Controller::showMessageSent(string username)
{
	//database.connect();
	cout<<endl;
	system("cls");
	cout<<endl<<"Nhan Ctr+N de hien thi danh sach hoac nhan Ctr+B de tro ve MENU TIN NHAN !!!"<<endl<<endl;
	database.showMessageSent(username);
}

void Controller::showMessageReceiver(string username)
{
	//database.connect();
	cout<<endl;
	system("cls");
	cout<<endl<<"Nhan Ctr+N de hien thi danh sach hoac nhan Ctr+B de tro ve MENU TIN NHAN !!!"<<endl<<endl;
	database.showMessageReceived(username);
	cout<<endl<<"Neu muon tra loi tin nhan thi nhan Ctr+R hoac an phim bat ky de thoat !!!"<<endl;
	fflush(stdin);
	char Ctr_R;
	Ctr_R=_getch();
	if (Ctr_R==18)
	{
		cout<<endl;
		cout<<endl<<"Co 2 cach de gui tin nhan:\n1. Nhap vao tai khoan nguoi nhan\n2. Bam truc tiep Ctrl+L"<<endl<<endl;
		fflush(stdin);
		char Ctr_L;
		cout<< "Nhap ten nguoi nhan: ";
		// ctrl+L nằm ở đây
		Ctr_L=_getch();
		if(Ctr_L==12){
			cout<<endl<<endl;
			database.Ctrl_L(username);
		}
		else
		{
			userView.nhanTin();
			database.sendMessage(username, userView.receiver, userView.content);
		}
	}
}

void Controller::sendMessage(string username)
{
	//database.connect();
	cout<<endl;
	cout<<endl<<"Co 2 cach de gui tin nhan:\n1. Nhap vao tai khoan nguoi nhan\n2. Bam truc tiep Ctrl+L"<<endl<<endl;
	fflush(stdin);
	char Ctr_L;
	cout<< "Nhap ten nguoi nhan: ";
	// ctrl+L nằm ở đây
	Ctr_L=_getch();
	if(Ctr_L==12){
		cout<<endl<<endl;
		database.Ctrl_L(username);
	}
	else
	{
		userView.nhanTin();
		database.sendMessage(username, userView.receiver, userView.content);
	}
}

void Controller::addFriend(string username)
{
	//database.connect();
	fflush(stdin);
	cout<< "Nhap ten ban be muon them: ";
	getline(cin, userView.Friend);
	fflush(stdin);
	database.addFriend(username,userView.Friend);
}

void Controller::listFriend(string username)
{
	//database.connect();
	database.listFriend(username);
}

void Controller::sortFriend(string username)
{
	//database.connect();
	database.sortFriend(username);
}

void Controller::sortFriendOfCity(string username)
{
	//database.connect();
	database.sortFriendOfCity(username);
}

void Controller::block(string username)
{
	//database.connect();
	fflush(stdin);
	cout<< "Nhap ten ban be muon block: ";
	getline(cin, userView.block);
	database.block(username, userView.block);
}

void Controller::showInfo(string username)
{
	//database.connect();
	database.showInfo(username);
}

void Controller::editInfoFriend(string username)
{
	//database.connect();
	fflush(stdin);
	cout<< "Nhap ten nguoi ban muon sua thong tin: ";
	getline(cin,userView.editInfoFriend);
	fflush(stdin);
	if(database.check(userView.editInfoFriend)){
		if (database.checkTableFriend(username, userView.editInfoFriend))
		{
			database.showInfoFriend(username, userView.editInfoFriend);
			cout<<endl<<"\t\t-----------SUA THONG TIN BAN BE-----------"<<endl;
			fflush(stdin);
			cout<< "Nhap day du ho va ten: ";
			getline(cin, userView.fullname);
			fflush(stdin);
			cout<< "Ngay sinh: ";
			getline(cin, userView.birthday);
			fflush(stdin);
			cout<< "Gioi tinh: ";
			getline(cin, userView.sex);
			fflush(stdin);
			cout<< "Dia chi: ";
			getline(cin, userView.address);
			fflush(stdin);
			database.editInfoFriend(userView.editInfoFriend, userView.fullname, userView.birthday, userView.sex, userView.address);
		}
		else
		{
			cout<<endl<<"\t\tChua ket ban. Ko the sua !!!"<<endl;
		}
	}
	else
	{
		cout<<endl<<"\t\tTai khoan ko ton tai hoac da bi xoa !!!"<<endl;
	}
}

void Controller::Ctr_L(string username)
{
	//database.connect();
	cout<<endl;
	cout<<endl<<"Co 2 cach de gui tin nhan:\n1. Nhap vao tai khoan nguoi nhan\n2. Bam truc tiep Ctrl+L de hien thi danh sach ban be"<<endl<<endl;
	fflush(stdin);
	char Ctr_L;
	cout<< "Nhap ten nguoi nhan: ";
	// ctrl+L nằm ở đây
	Ctr_L=_getch();
	if(Ctr_L==12){
		cout<<endl<<endl;
		database.Ctrl_L(username);
	}
	else
	{
		userView.nhanTin();
		database.sendMessage(username, userView.receiver, userView.content);
	}
}