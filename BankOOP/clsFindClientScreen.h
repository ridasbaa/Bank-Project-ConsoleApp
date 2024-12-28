#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsInputValidate.h"


class clsFindClient : protected clsScreen
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

	static  void ShowFindClientScreen() {

		if (!CheckAccessRight(clsUser::enPermissions::pFindClient))
		{
			return;
		}

		clsScreen::_DrawScreenHeader("Find Client Screen");

		string AccountNumber;
		cout << "Enter The Account Number of the client you're looking for : ";
		AccountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nAccount Number you entered is not exist, Please try again : ";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient ClientFound = clsBankClient::Find(AccountNumber);

		if (!ClientFound.IsEmpty())
		{
			cout << "\nClient Found :-)";
		}
		else
		{
			cout << "\nClient was not Found :-(";
		}

		_PrintClientCard(ClientFound);


	}



};

