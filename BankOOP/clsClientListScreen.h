#pragma once
#include<iostream>
#include<iomanip>
#include"clsBankClient.h"
#include"clsScreen.h"

using namespace std;

class clsClientListScreen : protected clsScreen
{

private:

	static void PrintClientRecordLine(clsBankClient Client) {


		cout << setw(8) << left << "" << "| " << setw(15) << left << Client.AccountNumber();
		cout << "| " << setw(20) << left << Client.FullName();
		cout << "| " << setw(12) << left << Client.Phone;
		cout << "| " << setw(20) << left << Client.Email;
		cout << "| " << setw(10) << left << Client.PinCode;
		cout << "| " << setw(12) << left << Client.AccountBalance;
		cout << endl;

	}

public:

	static void ShowClientListScreen() {


		if (!CheckAccessRight(clsUser::enPermissions::pClientList))
		{
			return;
		}


		vector<clsBankClient>vClients = clsBankClient::GetClientList();

		string Title = "Client List Screen";
		string SubTitle = "( " + to_string(vClients.size()) + ") Clients";

		clsScreen::_DrawScreenHeader(Title, SubTitle);

		cout << setw(8) << left << "" << "\n\t________________________________________________________________________________________________\n" << endl;
		cout << setw(8) << left << "" << "| " << left << setw(15) << "Accout Number";
		cout << "| " << left << setw(20) << "Client Name";
		cout << "| " << left << setw(12) << "Phone";
		cout << "| " << left << setw(20) << "Email";
		cout << "| " << left << setw(10) << "Pin Code";
		cout << "| " << left << setw(12) << "Balance";
		cout << setw(8) << left << "" << "\n\t________________________________________________________________________________________________\n" << endl;


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
			cout << setw(8) << left << "" << "\n\t________________________________________________________________________________________________\n" << endl;
		}

	}











};

