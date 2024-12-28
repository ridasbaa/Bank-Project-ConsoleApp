#pragma once
#include <iostream>
#include "clsUser.h"
#include "Global.h"
#include "clsDate.h"

class clsScreen
{
protected:

	static void _DrawScreenHeader(string Title, string SubTitle = "") {

		cout << "\t\t\t\t     ---------------------------------------------------\n";
		cout << "\t\t\t\t\t\t" << Title << endl;
		if (SubTitle != "")
		{
			cout << "\t\t\t\t\t\t " << SubTitle << endl;
		}
		cout << "\t\t\t\t     ---------------------------------------------------\n\n";
		cout << "\t\t\t\t\t\tUser : " << CurrentUser.Username << endl;
		cout << "\t\t\t\t\t\tDate : " << clsDate::DateToString(clsDate()) << endl << endl;

	}

	static bool CheckAccessRight(clsUser::enPermissions Permission) {

		if (!CurrentUser._CheckAccessPermission(Permission))
		{
			cout << "\t\t\t\t\t_____________________________________________________\n\n";
			cout << "\t\t\t\t\t\t   Access Denied! Contact your Admin" << endl;
			cout << "\t\t\t\t\t_____________________________________________________\n\n";
			return false;
		}
		else
		{
			return true;
		}
	}


};

