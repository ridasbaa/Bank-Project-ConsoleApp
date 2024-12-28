#pragma once
#include <iostream>
#include <iomanip>
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsMainScreen.h"
#include "clsDepositeScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsTransferScreen.h"
#include "clsTransferLogScreen.h"

using namespace std;


class clsTransactionsScreen : protected clsScreen
{

private:
	enum eTransactionsOption { eDeposite = 1, eWithdraw = 2, eTotalBalances = 3, eTransfer = 4, eTransferLogRegister = 5, eMainMenu = 6 };
	
	static short ReadOption(short From, short To) {

		short Number = clsInputValidate::ReadShortNumber("\n\t\t\t\t     Choose what do you want to do? ", "\n\t\t\t\t     Invalid Number, Please try again : ");

		while (Number < From || Number > To)
		{
			cout << "\n\t\t\t\t     Please enter a number between " << From << " and " << To << " : ";
			Number = clsInputValidate::ReadShortNumber(" ", "\n\t\t\t\t     Invalid Number, Please Enter a valid Number : ");
		}
		return Number;

	}

	static void _GoBackToTransactionsMenu() {
		ShowTransactionsMenu();
	}
	static void _ShowDepositeScreen() {
		clsDepositeScreen::ShowDepositeScreen();
	}
	static void _ShowWithdrawScreen() {

		clsWithdrawScreen::ShowWithdrawScreen();
	}
	static void _ShowTotalBalancesScreen() {
	
		clsTotalBalancesScreen::ShowTotalBalancesScreen();
		system("pause>0");
	}
	static void _ShowTransferScreen() {

		clsTransferScreen::ShowTransferScreen();
		system("pause");
	}
	static void _ShowTransferLogRegisterScreen() {

		clsTransferLogScreen::ShowTransferLogScreen();
		system("pause");
	}

	static void _PerformOption(eTransactionsOption TransactionsOption) {

		switch (TransactionsOption)
		{
		case clsTransactionsScreen::eDeposite:
			system("cls");
			_ShowDepositeScreen();
			_GoBackToTransactionsMenu();
			break;
		case clsTransactionsScreen::eWithdraw:
			system("cls");
			_ShowWithdrawScreen();
			_GoBackToTransactionsMenu();
			break;
		case clsTransactionsScreen::eTotalBalances:
			system("cls");
			_ShowTotalBalancesScreen();
			_GoBackToTransactionsMenu();
			break;
		case clsTransactionsScreen::eTransfer:
			system("cls");
			_ShowTransferScreen();
			_GoBackToTransactionsMenu();
			break;
		case clsTransactionsScreen::eTransferLogRegister:
			system("cls");
			_ShowTransferLogRegisterScreen();
			_GoBackToTransactionsMenu();
			break;
		case clsTransactionsScreen::eMainMenu:
			break;
		}
	}


public:

	static void ShowTransactionsMenu() {

		if (!CheckAccessRight(clsUser::enPermissions::pTransactions))
		{
			return;
		}

		system("cls");
		clsScreen::_DrawScreenHeader("Transactions Screen");

		cout << setw(37) << left << " " << "===================================================\n";
		cout << setw(37) << left << " " << "\t\t\tTransactions Menu\n";
		cout << setw(37) << left << " " << "===================================================\n";
		cout << setw(37) << left << " " << "\t[1] Deposite\n";
		cout << setw(37) << left << " " << "\t[2] Withdraw\n";
		cout << setw(37) << left << " " << "\t[3] Total Balances\n";
		cout << setw(37) << left << " " << "\t[4] Tarnsfer\n";
		cout << setw(37) << left << " " << "\t[5] Tarnsfer Log\n";
		cout << setw(37) << left << " " << "\t[6] Main Menu\n";
		cout << setw(37) << left << " " << "===================================================\n";

		_PerformOption((eTransactionsOption)ReadOption(1, 6));

	}




};

