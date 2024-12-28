#pragma once
#include <iostream>
#include <iomanip>
#include "clsUser.h"
#include "clsScreen.h"
#include "clsString.h"

class clsLoginRegisterScreen : protected clsScreen
{
private:

	static void _PrintLoginRegisterLine(clsUser::stLoginRegisterRecord RegisterRecord) {

		cout << setw(8) << left << "" << "| " << setw(28) << left << RegisterRecord.DateTime;
		cout << "| " << setw(20) << left << RegisterRecord.Username;
		cout << "| " << setw(12) << left << RegisterRecord.Password;
		cout << "| " << setw(20) << left << RegisterRecord.Permissions;
		cout << endl;

	}


public:


	static void ShowLogInRegisterScreen() {

		if (!CheckAccessRight(clsUser::enPermissions::eLoginRegister))
		{
			return;
		}

		vector<clsUser::stLoginRegisterRecord>vRegistrations = clsUser::GetRegistrationsList();

		string Title = "Login Registration Lists";
		string SubTitle = "(" + to_string(vRegistrations.size()) + ") Registration (s)";
		_DrawScreenHeader(Title, SubTitle);

		cout << setw(8) << left << "" << "\n\t____________________________________________________________________________________________________\n" << endl;
		cout << setw(8) << left << "" << "| " << left << setw(28) << "Date/Time";
		cout << "| " << left << setw(20) << "Username";
		cout << "| " << left << setw(12) << "Password";
		cout << "| " << left << setw(20) << "Permissions";
		cout << setw(8) << left << "" << "\n\t____________________________________________________________________________________________________\n" << endl;


		if (vRegistrations.empty())
		{
			cout << "\t\t\t\tNo Registrations Available in the system!";
		}
		else
		{
			for (clsUser::stLoginRegisterRecord & R : vRegistrations)
			{
				_PrintLoginRegisterLine(R);
			}
			cout << setw(8) << left << "" << "\n\t____________________________________________________________________________________________________\n" << endl;
		}

	}



};

