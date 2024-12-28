#pragma once
#include<iostream>
#include"clsBankClient.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUtil.h"


class clsTotalBalancesScreen : protected clsScreen
{
private:

	static void PrintClientRecordLine(clsBankClient Client) {

		cout << setw(24) << left << "" << "| " << left << setw(20) << Client.AccountNumber();
		cout << "| " << left << setw(26) << Client.FullName();
		cout << "| " << left << setw(12) << Client.AccountBalance;
		cout << endl;

	}

public:

	static void ShowTotalBalancesScreen() {

		vector<clsBankClient>vClients = clsBankClient::GetClientList();

		string SubTitle = "  (" + to_string(vClients.size()) + ") Client (s).";
		clsScreen::_DrawScreenHeader("Total Balances Screen", SubTitle);

		cout << setw(8) << left << "" << "\n\t\t______________________________________________________________________________________\n" << endl;
		cout << setw(24) << left << "" << "| " << left << setw(20) << "Accout Number";
		cout << "| " << left << setw(26) << "Client Name";
		cout << "| " << left << setw(12) << "Balance";
		cout << setw(8) << left << "" << "\n\t\t______________________________________________________________________________________\n" << endl;

		double TotalBalances = clsBankClient::GetTotalBalances();
		if (vClients.empty())
		{
			cout << "\t\t\t\tNo Client Available in the system!";
		}
		else
		{
			for (clsBankClient& C : vClients)
			{
				PrintClientRecordLine(C);
			}
		}
		cout << setw(8) << left << "" << "\n\t\t______________________________________________________________________________________\n" << endl;
		cout << "\n\t\t\t\t\tTotal Balances  = " << TotalBalances << endl;
		cout << "\n\t\t\t[ " << clsUtil::NumberToText(TotalBalances) << " ]" << endl;
	}



};

