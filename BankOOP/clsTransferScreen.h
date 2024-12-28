#pragma once
#include<iostream>
#include"clsUser.h"
#include"clsScreen.h"
#include"clsInputValidate.h"


class clsTransferScreen : protected clsScreen
{

private:

	static void _PrintClientCard(clsBankClient Client) {

		cout << "\n\nClient Card";
		cout << "\n______________________\n";
		cout << "\nFull Name   : " << Client.FullName();
		cout << "\nAcc. Number : " << Client.AccountNumber();
		cout << "\nBalance     : " << Client.AccountBalance;
		cout << "\n\n______________________\n";
	}

	static string _ReadAccountNumber(string Destination) {

		string AccountNumber;
		cout << "Please enter the account Number to  transfer " << Destination << " : ";
		AccountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nClient with account number [" << AccountNumber << "] Not Exist, Please try again: ";
			AccountNumber = clsInputValidate::ReadString();
		}
		return AccountNumber;
	}

	static double _ReadAmount(clsBankClient Client) {

		double Amount = 0;
		cout << "\nEnter transfer Amount : ";
		Amount = clsInputValidate::ReadDblNumber();

		while (Amount > Client.AccountBalance)
		{
			cout << "\nAmount Exceeds the available balance, please enter another amount : ";
			Amount = clsInputValidate::ReadDblNumber();
		}
		return Amount;
	}

public:


	static void ShowTransferScreen() {

		_DrawScreenHeader("Transfer Screen");

		clsBankClient SourceClient = clsBankClient::Find(_ReadAccountNumber("From"));
		_PrintClientCard(SourceClient);

		clsBankClient DestinationClient = clsBankClient::Find(_ReadAccountNumber("To"));
		_PrintClientCard(DestinationClient);

		
		double Amount = _ReadAmount(SourceClient);

		char answer = 'n';
		cout << "\nAre you sure you want to perform this transaction [y/n] : ";
		cin >> answer;

		if (tolower(answer) == 'y')
		{
			if (SourceClient.Transfer(Amount, DestinationClient, CurrentUser.Username))
			{
				cout << "\nTransfer Done Successfully!";
			}
			else
			{
				cout << "\nTransfer Failed!";
			}

		}
		_PrintClientCard(SourceClient);
		_PrintClientCard(DestinationClient);

	}


};

