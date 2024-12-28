#pragma once
#include<iostream>
#include"clsInputValidate.h"
#include"clsScreen.h"
#include"clsCurrency.h"


class clsFindCurrency : protected clsScreen
{
private:

	static short _ReadSearchMethod() {

		short Number;

		cout << "\nFind by : [1] Code or [2] Country : ";
		Number = clsInputValidate::ReadShortNumber("", "");
		while (Number < 1 || Number > 2)
		{
			cout << "\nYou can only choose [1 or 2] : ";
			Number = clsInputValidate::ReadShortNumber("", "");
		}
		return Number;
	}

	static void _PrintCurrencyInfo(clsCurrency Currency) {

		cout << "\nCurrency Info : ";
		cout << "\n_______________________________";
		cout << "\nCurrency Name : " << Currency.CurrencyName();
		cout << "\nCurrency Code : " << Currency.CurrencyCode();
		cout << "\nCountry       : " << Currency.Country();
		cout << "\nRate          : " << Currency.Rate();
		cout << "\n_______________________________\n";

	}

	static void _ShowResult(clsCurrency Currency) {

		if (!Currency.IsEmpty())
		{
			cout << "\nCurrency Found :-)\n";
			_PrintCurrencyInfo(Currency);
		}
		else
		{
			cout << "\nCurrency was not Found :-(\n";
		}

	}
public:


	static void ShowFindCurrencyScreen() {
		
		_DrawScreenHeader("Find Currency Screen");

		short SearchMethod = _ReadSearchMethod();

		if (SearchMethod == 1)
		{
			string Code;
			cout << "\nPlease Enter Currency Code : ";
			Code = clsInputValidate::ReadString();

			clsCurrency Currency = clsCurrency::FindByCode(Code);
			_ShowResult(Currency);
		}

		if (SearchMethod == 2)
		{
			string Country;
			cout << "\nPlease Enter Currency Code : ";
			Country = clsInputValidate::ReadString();
			clsCurrency Currency = clsCurrency::FindByCountry(Country);
			_ShowResult(Currency);
		}

	}


};

