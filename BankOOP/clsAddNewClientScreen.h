#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsScreen.h"

using namespace std;

class clsAddNewClientScreen : protected clsScreen
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

	static void ShowAddNewClientScreen() {
		
		if (!CheckAccessRight(clsUser::enPermissions::pAddClient))
		{
			return;
		}

		clsScreen::_DrawScreenHeader("Add New Client Screen");

		string AccountNumber;
		cout << "Enter Account Number : ";
		AccountNumber = clsInputValidate::ReadString();

		while (clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nThe account number you entered already exist, please enter another one : ";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccountNumber);

		_ReadClientInfo(NewClient);

		clsBankClient::enSaveResult SaveResult;

		SaveResult = NewClient.Save();

		switch (SaveResult)
		{
		case clsBankClient::svFailedObject:
			cout << "\nError! account was not saved because it's Empty";
			break;
		case clsBankClient::svSucceeded:
			cout << "\nClient Added successfully!";
			_PrintClientCard(NewClient);
			break;
		case clsBankClient::svFailedAccNumberExist:
			cout << "\nError! account was not saved because account number already Exist!\n";
			break;
		}

	}


};

