#pragma once
#include <iostream>
#include <iomanip>
#include "clsUser.h"
#include "clsScreen.h"



class clsUsersListScreen : protected clsScreen
{
private:

	static void _PrintUserRecordLine(clsUser User) {

		cout << setw(8) << left << "" << "| " << setw(15) << left << User.Username;
		cout << "| " << setw(20) << left << User.FullName();
		cout << "| " << setw(12) << left << User.Phone;
		cout << "| " << setw(20) << left << User.Email;
		cout << "| " << setw(10) << left << User.Password;
		cout << "| " << setw(12) << left << User.Permissions;
		cout << endl;

	}

public:

	static void ShowUsersListScreen() {

		vector<clsUser>vUsers = clsUser::GetUsersList();

		string Title = "Users List Screen";
		string SubTitle =  "  (" + to_string(vUsers.size()) + ") Users (s) ";

		clsScreen::_DrawScreenHeader(Title, SubTitle);

		cout << setw(8) << left << "" << "\n\t____________________________________________________________________________________________________\n" << endl;
		cout << setw(8) << left << "" << "| " << left << setw(15) << "Username";
		cout << "| " << left << setw(20) << "Full Name";
		cout << "| " << left << setw(12) << "Phone";
		cout << "| " << left << setw(20) << "Email";
		cout << "| " << left << setw(10) << "Password";
		cout << "| " << left << setw(12) << "Permissions";
		cout << setw(8) << left << "" << "\n\t____________________________________________________________________________________________________\n" << endl;
		

		if (vUsers.empty())
		{
			cout << "\t\t\t\tNo Client Available in the system!";
		}
		else
		{
			for (clsUser & U : vUsers)
			{
				_PrintUserRecordLine(U);
			}
			cout << setw(8) << left << "" << "\n\t____________________________________________________________________________________________________\n" << endl;
		}

	}

};

