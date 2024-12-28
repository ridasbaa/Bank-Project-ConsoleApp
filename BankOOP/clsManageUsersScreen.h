#pragma once
#include <iostream>
#include <iomanip>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUsersListScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"



class clsManageUsersScreen : protected clsScreen
{
private:

	enum eUserOption { eShowUserList = 1, eAddNewUser = 2, eDeleteUser = 3, eUpdateUser = 4, eFindUser = 5, eMainMenu = 6 };

	static short _ReadOption(short From, short To) {

		short Number = clsInputValidate::ReadShortNumber("\n\t\t\t\t     Choose what do you want to do? ", "\n\t\t\t\t     Invalid Number, Please try again : ");

		while (Number < From || Number > To)
		{
			cout << "\n\t\t\t\t     Please enter a number between " << From << " and " << To << " : ";
			Number = clsInputValidate::ReadShortNumber(" ", "\n\t\t\t\t     Invalid Number, Please Enter a valid Number : ");
		}
		return Number;

	}
	static void _PerformOption(eUserOption UserOption) {

		switch (UserOption)
		{
		case eUserOption::eShowUserList:
			system("cls");
			_ShowwUserListScreen();
			_GobackToManageUsersScreen();
			break;
		case eUserOption::eAddNewUser:
			system("cls");
			_ShowAddNewUserScreen();
			_GobackToManageUsersScreen();
			break;
		case eUserOption::eDeleteUser:
			system("cls");
			_ShowDeleteUserScreen();
			_GobackToManageUsersScreen();
			break;
		case eUserOption::eUpdateUser:
			system("cls");
			_ShowUpdateUserScreen();
			_GobackToManageUsersScreen();
			break;
		case eUserOption::eFindUser:
			system("cls");
			_ShowFindUserScreen();
			_GobackToManageUsersScreen();
			break;
		case eUserOption::eMainMenu:
			break;
		}
	}

	static void _GobackToManageUsersScreen() {
		ShowManageUsersScreen();
	}
	static void _ShowwUserListScreen() {

		clsUsersListScreen::ShowUsersListScreen();
		system("pause");
	}
	static void _ShowAddNewUserScreen() {

		clsAddNewUserScreen::ShowAddNewUserScreen();
		system("pause");
	}
	static void _ShowDeleteUserScreen() {

		clsDeleteUserScreen::ShowDeleteUserScreen();
		system("pause");
	}
	static void _ShowUpdateUserScreen() {

		clsUpdateUserScreen::ShowUpdateUserScreen();
		system("pause");
	}
	static void _ShowFindUserScreen() {

		clsFindUserScreen::ShowFindUserScreen();
		system("pause");
	}


public:


	static void ShowManageUsersScreen() {

		if (!CheckAccessRight(clsUser::enPermissions::pManageUsers))
		{
			return;
		}

		system("cls");
		clsScreen::_DrawScreenHeader("   Manage Users Screen");
		
		cout << setw(37) << left << " " << "===================================================\n";
		cout << setw(37) << left << " " << "\t\t\tManage Users Menu\n";
		cout << setw(37) << left << " " << "===================================================\n";
		cout << setw(37) << left << " " << "\t[1] Show Users List\n";
		cout << setw(37) << left << " " << "\t[2] Add New User\n";
		cout << setw(37) << left << " " << "\t[3] Delete User\n";
		cout << setw(37) << left << " " << "\t[4] Update User\n";
		cout << setw(37) << left << " " << "\t[5] Find User\n";
		cout << setw(37) << left << " " << "\t[6] Main Menu\n";
		cout << setw(37) << left << " " << "===================================================\n";

		_PerformOption((eUserOption)_ReadOption(1, 6));

	}






};

