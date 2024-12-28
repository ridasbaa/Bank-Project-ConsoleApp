#pragma once
#include<iostream>
#include"clsCurrency.h"
#include"clsScreen.h"
#include"clsInputValidate.h"


class clsUpdateCurrencyRate : protected clsScreen
{
private:

	static void _PrintCurrencyInfo(clsCurrency Currency) {

		cout << "\nCurrency Info : ";
		cout << "\n_______________________________";
		cout << "\nCurrency Name : " << Currency.CurrencyName();
		cout << "\nCurrency Code : " << Currency.CurrencyCode();
		cout << "\nCountry       : " << Currency.Country();
		cout << "\nRate          : " << Currency.Rate();
		cout << "\n_______________________________\n";

	}


public:

	static void ShowUpdateCurrencyScreen() {

		_DrawScreenHeader("Update Currency Rate");

		cout << "Enter Currency Code : ";
		string CurrencyCode = clsInputValidate::ReadString();

		while (!clsCurrency::IsCurrencyExist(CurrencyCode))
		{
			cout << "\nCurrency Not Found, Please try again : ";
			CurrencyCode = clsInputValidate::ReadString();
		}

		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);

		if (!Currency.IsEmpty())
		{
			_PrintCurrencyInfo(Currency);

			char Answer = 'n';
			cout << "\nAre you sure you want to update the rate of this currency [y/n] : ";
			cin >> Answer;

			if (tolower(Answer) == 'y')
			{
				cout << "\nUpdate Currency Rate:";
				cout << "\n________________________";
				cout << "\nEnter The new Rate : ";
				float Rate;
				Rate = clsInputValidate::ReadFloatNumber();
				Currency.UpdateRate(Rate);
				cout << "\nCurrency Rate Updated Sucessfully!";
				_PrintCurrencyInfo(Currency);
			}
		}

		


	}




};

