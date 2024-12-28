#pragma once
#include <iostream>
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include "clsScreen.h"

using namespace std;


class clsDeleteClientScreen : protected clsScreen
{
private:

	static void _PrintClientCard(clsBankClient Client) {

		cout << "\n\nClient Card : ";
		cout << "\n______________________________";
		cout << "\nFirst Name      : " << Client.FirstName;
		cout << "\nLast Name       : " << Client.LastName;
		cout << "\nFull Name       : " << Client.FullName();
		cout << "\nPhone Number    : " << Client.Phone;
		cout << "\nE-Mail          : " << Client.Email;
		cout << "\nAccount Number  : " << Client.AccountNumber();
		cout << "\nPin Code        : " << Client.PinCode;
		cout << "\nAccount Balance : " << Client.AccountBalance;
		cout << "\n______________________________\n\n";


	}

public:

	static void ShowDeleteClientScreen() {

		if (!CheckAccessRight(clsUser::enPermissions::pDeleteClient))
		{
			return;
		}

		clsScreen::_DrawScreenHeader("Delete Client Screen");

		string AccountNumber;
		cout << "Enter The account Number of the client you want to delete: ";
		AccountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nThe account number you entered is not Found, please enter another one : ";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient ClientToDelete = clsBankClient::Find(AccountNumber);

		_PrintClientCard(ClientToDelete);

		char answer = 'n';

		cout << "\nAre you sure you want to delete this client y/n : ";
		cin >> answer;

		if (tolower(answer) == 'y')
		{
			if (ClientToDelete.Delete())
			{
				cout << "\nClient Deleted successfully!";
				_PrintClientCard(ClientToDelete);
			}
			else
			{
				cout << "\nFailed to delete this client!";
			}
		}
	}







};

