#pragma once
#include<iostream>
#include"clsCurrency.h"
#include"iomanip"
#include"clsScreen.h"
#include"clsInputValidate.h"
#include"clsCurrenciesListScreen.h"
#include"clsFindCurrency.h"
#include"clsUpdateCurrencyRate.h"
#include"clsCurrencyCalculator.h"



class clsCurrencyScreen : protected clsScreen
{
private:

	enum enCurrencyMenuOption { eCurrenciesList = 1, eFindCurrencies = 2, eUpdateRate = 3, eCurrencyCalculator = 4, eMainMenu = 5 };

	static short ReadOption(short From, short To) {

		short Number = clsInputValidate::ReadShortNumber("\n\t\t\t\t     Choose what do you want to do? ", "\n\t\t\t\t     Invalid Number, Please try again : ");

		while (Number < From || Number > To)
		{
			cout << "\n\t\t\t\t     Please enter a number between " << From << " and " << To << " : ";
			Number = clsInputValidate::ReadShortNumber(" ", "\n\t\t\t\t     Invalid Number, Please Enter a valid Number : ");
		}
		return Number;

	}

	static void _GoBackToCurrencyExchnageScreen() {
		system("cls");
		ShowCurrencyExchangeScreen();
	}

	static void _ShowCurrenciesListScren() {
		
		clsCurrenciesListScreen::ShowCurrenciesListScreen();
		system("pause");
	}

	static void _ShowFindCurrencyScreen() {

		clsFindCurrency::ShowFindCurrencyScreen();
		system("pause");

	}

	static void _ShowUpdateRateScreen() {

		clsUpdateCurrencyRate::ShowUpdateCurrencyScreen();
		system("pause");
	}

	static void _ShowCurrencyClaculatorScreen() {
		
		clsCurrencyCalculator::ShowCurrencyCalculator();
		system("pause");

	}

	static void _PerformOption(enCurrencyMenuOption CurrencyMenuOption) {

		switch (CurrencyMenuOption)
		{
		case clsCurrencyScreen::eCurrenciesList:
			system("cls");
			_ShowCurrenciesListScren();
			_GoBackToCurrencyExchnageScreen();
			break;
		case clsCurrencyScreen::eFindCurrencies:
			system("cls");
			_ShowFindCurrencyScreen();
			_GoBackToCurrencyExchnageScreen();
			break;
		case clsCurrencyScreen::eUpdateRate:
			system("cls");
			_ShowUpdateRateScreen();
			_GoBackToCurrencyExchnageScreen();
			break;
		case clsCurrencyScreen::eCurrencyCalculator:
			system("cls");
			_ShowCurrencyClaculatorScreen();
			_GoBackToCurrencyExchnageScreen();
			break;
		case clsCurrencyScreen::eMainMenu:
			break;
		}

	}

public:


	static void ShowCurrencyExchangeScreen() {

		_DrawScreenHeader("  Currency Exchange Screen");

		cout << setw(37) << left << " " << "===================================================\n";
		cout << setw(37) << left << " " << "\t\t   Currency Exchange Menu\n";
		cout << setw(37) << left << " " << "===================================================\n";
		cout << setw(37) << left << " " << "\t[1] Currencies List\n";
		cout << setw(37) << left << " " << "\t[2] Find Currency\n";
		cout << setw(37) << left << " " << "\t[3] Update Rate\n";
		cout << setw(37) << left << " " << "\t[4] Currency Calculator\n";
		cout << setw(37) << left << " " << "\t[5] Main Menu\n";
		cout << setw(37) << left << " " << "===================================================\n";

		_PerformOption((enCurrencyMenuOption)ReadOption(1, 10));

	}




};

