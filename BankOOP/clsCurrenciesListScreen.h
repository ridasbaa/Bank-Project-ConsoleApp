#pragma once
#include<iostream>
#include<iomanip>
#include<vector>
#include"clsCurrency.h"
#include"clsScreen.h"


class clsCurrenciesListScreen : protected clsScreen
{
private:

	static void _PrintCurrencyRecordLine(clsCurrency Currency) {


		cout << setw(8) << left << "" << "| " << setw(30) << left << Currency.Country();
		cout << "| " << setw(10) << left << Currency.CurrencyCode();
		cout << "| " << setw(32) << left << Currency.CurrencyName();
		cout << "| " << setw(12) << left << Currency.Rate();
		cout << endl;

	}

public:


	static void ShowCurrenciesListScreen() {

		vector<clsCurrency>vCurrecies = clsCurrency::GetCurrenciesList();

		string Title = "Currencies List";
		string SubTitle = "(" + to_string(vCurrecies.size()) + ") Currencies";
		_DrawScreenHeader(Title, SubTitle);

		cout << setw(8) << left << "" << "\n\t________________________________________________________________________________________________\n" << endl;
		cout << setw(8) << left << "" << "| " << left << setw(30) << "Country";
		cout << "| " << left << setw(10) << "Code";
		cout << "| " << left << setw(32) << "Name";
		cout << "| " << left << setw(12) << "Rate";
		cout << setw(8) << left << "" << "\n\t________________________________________________________________________________________________\n" << endl;


		if (vCurrecies.empty())
		{
			cout << "\t\t\t\tNo Client Available in the system!";
		}
		else
		{
			for (clsCurrency& Currency : vCurrecies)
			{
				_PrintCurrencyRecordLine(Currency);
			}
			cout << setw(8) << left << "" << "\n\t________________________________________________________________________________________________\n" << endl;
		}



	}






};

