#include "stdafx.h"
#include "UserView.h"

UserView::UserView(void)
{
}


UserView::~UserView(void)
{
}

void UserView::nhap(){
	fflush(stdin);
	cout<< "Nhap username: ";
	getline(cin, username);
	fflush(stdin);
	cout<< "Nhap password: ";
	getline(cin, password);
	fflush(stdin);
}

void UserView::dangKy(){
	fflush(stdin);
	cout<< "Nhap username: ";
	getline(cin, username);
	fflush(stdin);
	cout<< "Nhap password: ";
	getline(cin, password);
	fflush(stdin);
	cout<< "Nhap day du ho va ten: ";
	getline(cin, fullname);
	fflush(stdin);
	cout<< "Nhap ngay, thang, nam sinh(dd/mm/yyyy): ";
	getline(cin, birthday);
	fflush(stdin);
	cout<< "Nhap gioi tinh: ";
	getline(cin, sex);
	fflush(stdin);
	cout<< "Nhap dia chi: ";
	getline(cin, address);
	fflush(stdin);
}

void UserView::nhanTin()
{
	fflush(stdin);
	getline(cin, receiver);
	fflush(stdin);
	cout<< "Noi dung tin nhan: ";
	getline(cin, content);
	fflush(stdin);	
}
