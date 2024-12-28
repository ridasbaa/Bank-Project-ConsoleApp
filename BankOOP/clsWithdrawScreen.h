#pragma once
#include<iostream>
#include"clsBankClient.h"
#include "clsScreen.h"
#include "clsInputValidate.h"


class clsWithdrawScreen : protected clsScreen
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

	static void ShowWithdrawScreen() {

		clsScreen::_DrawScreenHeader("Withdraw Screen");

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

		double AmountToWithdraw = 0;
		cout << "\nPlease Amount to withdraw : ";
		AmountToWithdraw = clsInputValidate::ReadDblNumber();

		char answer = 'n';

		cout << "\nAre you sure you want to perform this transaction? [y/n]: ";
		cin >> answer;

		if (tolower(answer) == 'y')
		{
			if (Client.Withdraw(AmountToWithdraw))
			{
				cout << "\nAmount Withdrawn Successfully!" << endl;
				cout << "\nNew Balance is = " << Client.AccountBalance << endl;
			}
			else
			{
				cout << "\nCannot withdraw, Insufficiet Balance!\n";
				cout << "\nAmount To Withdraw : " << AmountToWithdraw;	
				cout << "\nYour Balance is : " << Client.AccountBalance;
			}
		}
		else
		{
			cout << "\nOperation was cancelled!\n" << endl;
		}


	}





};

