#pragma once
#include <iostream>
#include "clsUser.h"
#include "clsScreen.h"
#include "clsInputValidate.h"


class clsDeleteUserScreen : protected clsScreen
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

	static void ShowDeleteUserScreen() {

		clsScreen::_DrawScreenHeader("Delete User Screen");

		string Username = "";

		cout << "Please Enter the username of the user you want to delete : ";
		Username = clsInputValidate::ReadString();

		while (!clsUser::IsUserExist(Username))
		{
			cout << "\nUser with username [" << Username << "] not exist, please try again : ";
			Username = clsInputValidate::ReadString();
		}

		clsUser User = clsUser::Find(Username);

		_PrintUserCard(User);

		char anwser = 'n';

		cout << "\nAre you sure you want to delete this user [y/n] : ";
		cin >> anwser;

		if (tolower(anwser) == 'y')
		{
			if (User.Delete())
			{
				cout << "\nUser Deleted Successfully!";
				_PrintUserCard(User);
			}
			else
			{
				cout << "\nError, user was not deleted!";
			}
		}

	}



};

