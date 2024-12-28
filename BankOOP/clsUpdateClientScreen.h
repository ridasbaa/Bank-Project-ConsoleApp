#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsInputValidate.h"

using namespace std;

class clsUpdateClientScreen : protected clsScreen
{
private:

	static void _ReadClientInfo(clsBankClient& Client) {

		cout << "\nEnter First Name : ";
		Client.FirstName = clsInputValidate::ReadString();

		cout << "\nEnter Last Name : ";
		Client.LastName = clsInputValidate::ReadString();

		cout << "\nEnter Email : ";
		Client.Email = clsInputValidate::ReadString();

		cout << "\nEnter Phone Number: ";
		Client.Phone = clsInputValidate::ReadString();

		cout << "\nEnter Pin code: ";
		Client.PinCode = clsInputValidate::ReadString();

		cout << "\nEnter Account Balance : ";
		Client.AccountBalance = clsInputValidate::ReadDblNumber();

	}

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

	static void ShowUpdateClientScreen() {

		if (!CheckAccessRight(clsUser::enPermissions::pUpdateClient))
		{
			return;
		}

		clsScreen::_DrawScreenHeader("Update Client Screen");

		string AccountNumber;

		cout << "Enter The Account Number of the client you want to update : ";
		AccountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nAccount Number you entered is not exist, please try again : ";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);

		_PrintClientCard(Client);

		char answer = 'n';
		cout << "\nAre you sure you want to Update this client y/n : ";
		cin >> answer;

		if (tolower(answer) == 'y')
		{
			cout << "\nUpdate Client Info : \n";
			cout << "__________________________\n";

			_ReadClientInfo(Client);
			clsBankClient::enSaveResult SaveResult;
			SaveResult = Client.Save();

			switch (SaveResult)
			{
			case clsBankClient::svFailedObject:
				cout << "\nError, Account was not saved because it's empty!";
				break;
			case clsBankClient::svSucceeded:
				cout << "\nClient Updated successfully!";
				_PrintClientCard(Client);
				break;
			}

		}


	}






};

