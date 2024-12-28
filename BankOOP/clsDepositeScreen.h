#pragma once
#include<iostream>
#include"clsBankClient.h"
#include "clsScreen.h"
#include "clsInputValidate.h"


class clsDepositeScreen : protected clsScreen
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

	static void ShowDepositeScreen() {

		clsScreen::_DrawScreenHeader("Deposite Screen");

		string AccountNumber;
		cout << "Please Enter The Account Number : ";
		AccountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nClient with account Number [" << AccountNumber << "] not exist, Please try again : ";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);

		_PrintClientCard(Client);

		double AmountToDeposite = 0;
		cout << "\nPlease enter Deposite Amount : ";
		AmountToDeposite = clsInputValidate::ReadDblNumber();

		char answer = 'n';

		cout << "\nAre you sure you want to perform this transaction? [y/n]: ";
		cin >> answer;

		if (tolower(answer) == 'y')
		{
			Client.Deposite(AmountToDeposite);

			cout << "\nAmount Deposited Successfully!" << endl;
			cout << "\nNew Balance is = " << Client.AccountBalance << endl;
		}
		else
		{
			cout << "\nOperation was cancelled!\n" << endl;
		}


	}





};

