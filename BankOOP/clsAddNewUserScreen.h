#pragma once
#include <iostream>
#include "clsUser.h"
#include "clsScreen.h"
#include "clsInputValidate.h"



class clsAddNewUserScreen : protected clsScreen
{

private:

	static void _ReadUserInfo(clsUser &User) {

		cout << "\nEnter the new password : ";
		User.Password = clsInputValidate::ReadString();

		cout << "\nEnter the First Name : ";
		User.FirstName = clsInputValidate::ReadString();

		cout << "\nEnter the Last Name : ";
		User.LastName = clsInputValidate::ReadString();

		cout << "\nEnter Phone : ";
		User.Phone = clsInputValidate::ReadString();

		cout << "\nEnter E-Mail : ";
		User.Email = clsInputValidate::ReadString();

		cout << "\nEnter Permissions : ";
		User.Permissions= _ReadPermissionsToSet();
		
	}

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

	static int _ReadPermissionsToSet() {

		char answer = 'n';
		int Permissions = 0;

		cout << "\nDo you want to give this user full Control [y/n] : ";
		cin >> answer;

		if (tolower(answer) == 'y')
		{
			Permissions += clsUser::enPermissions::eAll;
		}
		else
		{
			cout << "\nDo you want to give this user access to : ";

			cout << "\nShow Client List [y/n] : ";
			cin >> answer;
			if (tolower(answer) == 'y')
			{
				Permissions += clsUser::enPermissions::pClientList;
			}

			cout << "\nAdd Client [y/n] : ";
			cin >> answer;
			if (tolower(answer) == 'y')
			{
				Permissions += clsUser::enPermissions::pAddClient;
			}

			cout << "\nDelete Client [y/n] : ";
			cin >> answer;
			if (tolower(answer) == 'y')
			{
				Permissions += clsUser::enPermissions::pDeleteClient;
			}

			cout << "\nFind Client [y/n] : ";
			cin >> answer;
			if (tolower(answer) == 'y')
			{
				Permissions += clsUser::enPermissions::pFindClient;
			}

			cout << "\nUpdate Client [y/n] : ";
			cin >> answer;
			if (tolower(answer) == 'y')
			{
				Permissions += clsUser::enPermissions::pUpdateClient;
			}

			cout << "\nTransactions [y/n] : ";
			cin >> answer;
			if (tolower(answer) == 'y')
			{
				Permissions += clsUser::enPermissions::pTransactions;
			}

			cout << "\nManage Users [y/n] : ";
			cin >> answer;
			if (tolower(answer) == 'y')
			{
				Permissions += clsUser::enPermissions::pManageUsers;
			}

			cout << "\nLogin Register [y/n] : ";
			cin >> answer;
			if (tolower(answer) == 'y')
			{
				Permissions += clsUser::enPermissions::eLoginRegister;
			}
		}
		return Permissions;

	}

public:

	static void ShowAddNewUserScreen() {

		cout << "Please enter the username : ";
		string Username = clsInputValidate::ReadString();

		while (clsUser::IsUserExist(Username))
		{
			cout << "\nUsername already exist, Please try another one : ";
			Username = clsInputValidate::ReadString();
		}

		clsUser NewUser = clsUser::GetAddNewUserObject(Username);

		_ReadUserInfo(NewUser);

		clsUser::enSaveResult SaveResult;

		SaveResult = NewUser.Save();

		switch (SaveResult)
		{
		case clsUser::svFailedEmptyObject:
			cout << "\nFailed to save the user";
			break;
		case clsUser::svSuccessded:
			cout << "\nUser Added successfully!\n";
			_PrintUserCard(NewUser);
			break;
		case clsUser::svFailedUserExists:
			cout << "\nFailed to save because the user already exist!\n";
			break;
		}

	}

};

