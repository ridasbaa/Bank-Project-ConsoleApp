#pragma once
#include<iostream>
#include"clsBankClient.h"
#include"clsScreen.h"


class clsTransferLogScreen : protected clsScreen
{

private:

	static void _PrintTransgerLogRegisterLine(clsBankClient::stTransferLogRecord TransferLog) {

		cout << setw(8) << left << "" << "| " << setw(28) << left << TransferLog.DateTime;
		cout << "| " << setw(8) << left << TransferLog.SourceClientAccountNumber;
		cout << "| " << setw(8) << left << TransferLog.DestinationClientAccountNumber;
		cout << "| " << setw(10) << left << TransferLog.Amount;
		cout << "| " << setw(10) << left << TransferLog.SourceClientAccountBalanceAfter;
		cout << "| " << setw(10) << left << TransferLog.DestinationClientAccountBalanceAfter;
		cout << "| " << setw(10) << left << TransferLog.Implementer;
		cout << endl;

	}



public:

	static void ShowTransferLogScreen() {

		vector < clsBankClient::stTransferLogRecord>vTransferLogList = clsBankClient::GetTransferLogList();
		string Title = "Transfer History Screen";
		string SubTitle = "(" + to_string(vTransferLogList.size()) + ") Log (s)";

		_DrawScreenHeader(Title, SubTitle);

		cout << setw(8) << left << "" << "\n\t____________________________________________________________________________________________________\n" << endl;
		cout << setw(8) << left << "" << "| " << left << setw(28) << "Date/Time";
		cout << "| " << left << setw(8) << "s.Acct";
		cout << "| " << left << setw(8) << "d.Acct";
		cout << "| " << left << setw(10) << "Amount";
		cout << "| " << left << setw(10) << "s.Balance";
		cout << "| " << left << setw(10) << "d.Balance";
		cout << "| " << left << setw(10) << "Implementer";
		cout << setw(8) << left << "" << "\n\t____________________________________________________________________________________________________\n" << endl;


		if (vTransferLogList.empty())
		{
			cout << "\t\t\t\tNo Registrations Available in the system!";
		}
		else
		{
			for (clsBankClient::stTransferLogRecord& TransferLog : vTransferLogList)
			{
				_PrintTransgerLogRegisterLine(TransferLog);
			}
			cout << setw(8) << left << "" << "\n\t____________________________________________________________________________________________________\n" << endl;
		}



	}







};

