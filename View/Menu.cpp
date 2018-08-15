#include "stdafx.h"
#include "Menu.h"

Menu::Menu(void)
{
}

Menu::~Menu(void)
{
}

Controller controller;

void Menu::choice1(){
	char chosse1;
	do
	{
		menu_Display.menu_Display1();
		cout<<endl<<"\tNhap vao lua chon: ";
		fflush(stdin);
		cin>>chosse1;
		switch (chosse1)
		{
		case '1':
			controller.signUp();
			break;
		case '2':
			system("cls");
			controller.logIn();
			break;
		case '3':
			controller.close();
			cout<<endl<< "Da Thoat !!!"<<endl;
			break;
		default:
			cout<<endl<< "Chon sai. An mot phim bat ky de chon lai !!!"<<endl;
			_getch();
		}
		if (chosse1=='3')
		{
			break;
		}
	} while (true);
}

void Menu::choice2(string username, string password)
{
	char chosse2;
	do
	{
		menu_Display.menu_Main();
		cout<<endl<<"\tNhap vao lua chon: ";
		fflush(stdin);
		cin>>chosse2;
		switch (chosse2)
		{
		case '1':	
			system("cls");
			choice3(username);
			break;
		case '2':
			controller.addFriend(username);
			break;
		case '3': 
			system("cls");
			choice5(username);
			break;
		case '4':
			controller.block(username);
			break;
		case '5': 
			controller.showInfo(username);
			break;
		case '6':
			system("cls");
			choice4(username);
			break;
		case '7':
			controller.close();
			break;
		default:
			cout<<endl<< "Chon sai. An mot phim bat ky de chon lai !!!"<<endl;
			_getch();
		}
		if (chosse2=='7')
		{
			break;
		}
	} while (true);
}

void Menu::choice3(string username)
{
	char chosse3;
	do
	{
		menu_Display.menu_Message();
		cout<<endl<<"\tNhap vao lua chon: ";
		fflush(stdin);
		cin>>chosse3;
		switch (chosse3)
		{
		case '1':
			controller.showMessageSent(username);
			break;
		case '2': 
			controller.showMessageReceiver(username);
			break;
		case '3':
			controller.sendMessage(username);
			break;
		case '4':
			system("cls");
			break;
		default:
			cout<<endl<<"Chon sai. An mot phim bat ky de chon lai !!!"<<endl;
			_getch();
			break;
		}
		if(chosse3=='4')
		{
			break;
		}
	} while (true);
}

void Menu::choice4(string username){
	char chosse4;
	do
	{
		menu_Display.menu_InfoFriend();
		cout<<endl<<"\tNhap vao lua chon: ";
		fflush(stdin);
		cin>>chosse4;
		switch (chosse4)
		{
		case '1': 
			controller.editInfoFriend(username);
			break;
		case '2':
			controller.Ctr_L(username);
			break;
		case '3':
			system("cls");
			break;
		default:
			cout<<endl<<"Chon sai. An mot phim bat ky de chon lai !!!"<<endl;
			_getch();
			break;
		}
		if(chosse4=='3')
		{
			break;
		}
	} while (true);
}

void Menu::choice5(string username)
{
	char chosse5;
	do
	{
		menu_Display.menu_ListFriend();
		cout<<endl<<"\tNhap vao lua chon: ";
		fflush(stdin);
		cin>>chosse5;
		switch (chosse5)
		{
		case '1':
			controller.listFriend(username);
			break;
		case '2':
			controller.sortFriend(username);
			break;
		case '3':
			controller.sortFriendOfCity(username);
			break;
		case '4':
			system("cls");
			break;
		default:
			cout<<endl<<"Chon sai. An mot phim bat ky de chon lai !!!"<<endl;
			_getch();
			break;
		}
		if(chosse5=='4')
		{
			break;
		}
	} while(true);
}