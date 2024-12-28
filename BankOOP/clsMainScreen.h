#pragma once
#include <iostream>
#include <iomanip>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsClientListScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionsScreen.h"
#include "clsManageUsersScreen.h"
#include "Global.h"
#include "clsLoginScreen.h"
#include "clsLoginRegisterScreen.h"
#include "clsLoginRegisterScreen.h"
#include "clsCurrencyScreen.h"


using namespace std;

class clsMainScreen : protected clsScreen
{

private:
	enum enMainMenuOptions{eListClients = 1, eAddClient = 2, eDeleteClient = 3, eUpdateClient = 4,
		eFindClient = 5, eTransactions = 6, eManageUsers = 7, eRegistrationslist = 8, eCurrencyExchange = 9 ,eLogOut = 10};

	static short ReadOption(short From, short To) {

		short Number = clsInputValidate::ReadShortNumber("\n\t\t\t\t     Choose what do you want to do? ", "\n\t\t\t\t     Invalid Number, Please try again : ");

		while (Number < From || Number > To )
		{
			cout << "\n\t\t\t\t     Please enter a number between " << From << " and " << To << " : ";
			Number = clsInputValidate::ReadShortNumber(" ", "\n\t\t\t\t     Invalid Number, Please Enter a valid Number : ");
		}
		return Number;

	}

	static void _GoBackToMainMenu() {
		MainMenuScreen();
	}
	static void _PauseScreen() {
		system("pause");
	}

	static void _ShowAllClientScreen() {

		clsClientListScreen::ShowClientListScreen();
		_PauseScreen();
	}
	static void _ShowAddNewClientScreen() {

		clsAddNewClientScreen::ShowAddNewClientScreen();
		_PauseScreen();
	}
	static void _ShowDeleteClientScreen() {

		clsDeleteClientScreen::ShowDeleteClientScreen();
		_PauseScreen();
	}
	static void _ShowUpdateClientScreen() {

		clsUpdateClientScreen::ShowUpdateClientScreen();
		_PauseScreen();
	}
	static void _ShowFindCleintScreen() {

		clsFindClient::ShowFindClientScreen();
		_PauseScreen();
	}
	static void _ShowTransactionsMenu() {

		clsTransactionsScreen::ShowTransactionsMenu();
		_PauseScreen();
	}
	static void _ShowManageUsersMenu() {

		clsManageUsersScreen::ShowManageUsersScreen();
		_PauseScreen();
	}
	static void _ShowLoginRegistrationslist() {

		clsLoginRegisterScreen::ShowLogInRegisterScreen();
		_PauseScreen();
	}

	static void _ShowCurrencyExchangeScreen() {

		clsCurrencyScreen::ShowCurrencyExchangeScreen();
	}

	static void _Logout() {

		CurrentUser = clsUser::Find("", "");
	}

	static void _PerformOption(enMainMenuOptions MainMenuOption) {

		switch (MainMenuOption)
		{
		case clsMainScreen::eListClients:
			system("cls");
			_ShowAllClientScreen();
			_GoBackToMainMenu();
			break;
		case clsMainScreen::eAddClient:
			system("cls");
			_ShowAddNewClientScreen();
			_GoBackToMainMenu();
			break;
		case clsMainScreen::eDeleteClient:
			system("cls");
			_ShowDeleteClientScreen();
			_GoBackToMainMenu();
			break;
		case clsMainScreen::eUpdateClient:
			system("cls");
			_ShowUpdateClientScreen();
			_GoBackToMainMenu();
			break;
		case clsMainScreen::eFindClient:
			system("cls");
			_ShowFindCleintScreen();
			_GoBackToMainMenu();
			break;
		case clsMainScreen::eTransactions:
			system("cls");
			_ShowTransactionsMenu();
			_GoBackToMainMenu();
			break;
		case clsMainScreen::eManageUsers:
			system("cls");
			_ShowManageUsersMenu();
			_GoBackToMainMenu();
			break;
		case clsMainScreen::eRegistrationslist:
			system("cls");
			_ShowLoginRegistrationslist();
			_GoBackToMainMenu();
			break;
		case clsMainScreen::eCurrencyExchange:
			system("cls");
			_ShowCurrencyExchangeScreen();
			_GoBackToMainMenu();
			break;
		case clsMainScreen::eLogOut:
			system("cls");
			_Logout();
			break;
		default:
			break;
		}

	}

public:

	static void MainMenuScreen() {

		system("cls");
		_DrawScreenHeader("\t   Main Menu");

		cout << setw(37) << left << " " << "===================================================\n";
		cout << setw(37) << left << " " << "\t\t\t   Main Menu\n";
		cout << setw(37) << left << " " << "===================================================\n";
		cout << setw(37) << left << " " << "\t[1] Show Clients List\n";
		cout << setw(37) << left << " " << "\t[2] Add New Client\n";
		cout << setw(37) << left << " " << "\t[3] Delete Client\n";
		cout << setw(37) << left << " " << "\t[4] Update Clients Info\n";
		cout << setw(37) << left << " " << "\t[5] Find Clients\n";
		cout << setw(37) << left << " " << "\t[6] Transactions\n";
		cout << setw(37) << left << " " << "\t[7] Manage Users\n";
		cout << setw(37) << left << " " << "\t[8] Login Registrations\n";
		cout << setw(37) << left << " " << "\t[9] Currency Exchange\n";
		cout << setw(37) << left << " " << "\t[10] Logout\n";
		cout << setw(37) << left << " " << "===================================================\n";

		_PerformOption((enMainMenuOptions)ReadOption(1, 10));

	}



};

