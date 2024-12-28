#pragma once
#include <iostream>
#include <fstream>
#include "clsUser.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsMainScreen.h"
#include "Global.h"
#include "clsDate.h"



class clsLoginScreen : protected clsScreen
{
private:

	static bool _Login() {

		string Username, Password;
		bool LoginFailed = false;
		short FaiedLoginCount = 0;
		do
		{
			system("cls");
			clsScreen::_DrawScreenHeader("\t Login Screen");

			if (LoginFailed)
			{
				FaiedLoginCount++;
				cout << "\nInvalid Username/Password\n";
				cout << "\nYou have [" << 3 - FaiedLoginCount << "]Trail (s) to login\n";
			}

			if (FaiedLoginCount == 3)
			{
				cout << "\nYou are locked after 3 failed trials\n";
				return false;
			}

			cout << "\nEnter The Username : ";
			Username = clsInputValidate::ReadString();
			cout << "\nEnter The Password : ";
			Password = clsInputValidate::ReadString();

			CurrentUser = clsUser::Find(Username, Password);
			LoginFailed = CurrentUser.IsEmpty();

		} while (LoginFailed);

		CurrentUser.RegisterLogin();

		clsMainScreen::MainMenuScreen();
		return true;
	}

public:


	static bool ShowLoginScreen() {

		system("cls");

		short Trails = 1;
		return _Login();
	}



};

