#pragma once
#include<iostream>
#include"clsCurrency.h"
#include"clsScreen.h"
#include"clsInputValidate.h"


class clsCurrencyCalculator : protected clsScreen
{
private:

	static void _PrintCurrencyCard(clsCurrency Currency, string Title) {

		cout << Title ;
		cout << "\n_______________________________";
		cout << "\nCurrency Name : " << Currency.CurrencyName();
		cout << "\nCurrency Code : " << Currency.CurrencyCode();
		cout << "\nCountry       : " << Currency.Country();
		cout << "\nRate (1$) =   : " << Currency.Rate();
		cout << "\n_______________________________\n";
	}

	static void _PrintCalculationResult(clsCurrency Currency1, clsCurrency Currency2, float Amount) {
		
		_PrintCurrencyCard(Currency1, "\nConvert From : ");

		float AmountInUsd = Currency1.ConvertToUsd(Amount);

		cout << Amount << " " << Currency1.CurrencyCode() << " = " << AmountInUsd << " USD" << endl;

		if (Currency2.CurrencyCode() == "USD")
		{
			return;
		}

		_PrintCurrencyCard(Currency2, "\nConverting From USD to : ");

		float AmountInCurrency2 = Currency1.ConvertToAnotherCurrency(Amount, Currency2);
		cout << Amount << " " << Currency1.CurrencyCode() << " = " << AmountInCurrency2 << " " << Currency2.CurrencyCode() << endl;

	}

	static float _ReadAmount() {

		float Amount;
		cout << "\nEnter Amount To Exchange : ";
		Amount = clsInputValidate::ReadFloatNumber();
		return Amount;

	}

	static clsCurrency _GetCurrency(string Message) {

		string CurrencyCode;
		cout << Message;
		CurrencyCode = clsInputValidate::ReadString();

		while (!clsCurrency::IsCurrencyExist(CurrencyCode))
		{
			cout << "\nCurrency Not Found, Try Again : ";
			CurrencyCode = clsInputValidate::ReadString();
		}

		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
		return Currency;
	}

public:

	static void ShowCurrencyCalculator() {

		char Continue = 'y';

		while (tolower(Continue) == 'y')
		{
			system("cls");
			_DrawScreenHeader("Currency Calculator");

			clsCurrency CurrencyFrom = _GetCurrency("\nPlease enter currency1 Code : ");
			clsCurrency CurrencyTo = _GetCurrency("\nPlease enter currency2 Code : ");
			float Amount = _ReadAmount();

			_PrintCalculationResult(CurrencyFrom, CurrencyTo, Amount);

			cout << "\nDo you want to perforn another calculation [y/n] : ";
			cin >> Continue;
		}

		





	}






};

