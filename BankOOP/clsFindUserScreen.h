#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"


class clsFindUserScreen : protected clsScreen
{
private:

	static void _PrintUserCard(clsUser User) {

		cout << "\nUser Card : ";
		cout << "\n_______________________";
		cout << "\nFirst Name   : " << User.FirstName;
		cout << "\nLast Name    : " << User.LastName;
		cout << "\nFull Name    : " << User.FullName();
		cout << "\nPhone Number : " << User.Phone;
		cout << "\nE-Mail       : " << User.Email;
		cout << "\nUsername     : " << User.Username;
		cout << "\nPassword     : " << User.Password;
		cout << "\nPermissions  : " << User.Permissions;
		cout << "\n_______________________\n";

	}


public:

	static void ShowFindUserScreen() {

		clsScreen::_DrawScreenHeader("Find User Screen");

		string Username;
		cout << "Enter The Account Number of the User you're looking for : ";
		Username = clsInputValidate::ReadString();

		while (!clsUser::IsUserExist(Username))
		{
			cout << "\nAccount Number you entered is not exist, Please try again : ";
			Username = clsInputValidate::ReadString();
		}

		clsUser UserFound = clsUser::Find(Username);

		if (!UserFound.IsEmpty())
		{
			cout << "\nUser Found :-)";
		}
		else
		{
			cout << "\nUser was not Found :-(";
		}

		_PrintUserCard(UserFound);

	}

};

