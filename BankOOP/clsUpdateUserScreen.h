#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"


class clsUpdateUserScreen : protected clsScreen
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

	static void _ReadUserInfo(clsUser& User) {

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
		User.Permissions = _ReadPermissionsToSet();

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


	static void ShowUpdateUserScreen() {

		clsScreen::_DrawScreenHeader("Update User Screen");

		string Username = "";

		cout << "Please Enter the username of the user you want to Update : ";
		Username = clsInputValidate::ReadString();

		while (!clsUser::IsUserExist(Username))
		{
			cout << "\nUser with username [" << Username << "] not exist, please try again : ";
			Username = clsInputValidate::ReadString();
		}

		clsUser User = clsUser::Find(Username);
		_PrintUserCard(User);

		char answer = 'n';
		cout << "\nAre you sure you want to update this user Info [y/n] : ";
		cin >> answer;



		if (tolower(answer) == 'y')
		{

			cout << "\nUpdate Client Info : \n";
			cout << "__________________________\n";
			_ReadUserInfo(User);

			clsUser::enSaveResult SaveResult;
			SaveResult = User.Save();

			switch (SaveResult)
			{
			case clsUser::svFailedEmptyObject:
				cout << "\nError, Account was not saved because it's empty!";
				break;
			case clsUser::svSuccessded:
				cout << "\nUser Updated successfully!";
				_PrintUserCard(User);
				break;
			}
		}




	}




};

