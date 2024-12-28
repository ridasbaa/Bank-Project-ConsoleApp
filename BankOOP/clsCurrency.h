#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include"clsString.h"

class clsCurrency
{
private:

	enum enMode { EmptyMode = 0, UpdateMode = 1 };
	enMode _Mode;

	string _Country;
	string _CurrencyCode;
	string _CurrencyName;
	float _Rate;


	static void _SaveCurrenciesDataToFile(vector<clsCurrency>vCurrenciesData) {

		fstream MyFile;

		MyFile.open("Currencies.txt", ios::out);

		if (MyFile.is_open())
		{
			string DataLine = "";
			for (clsCurrency & C : vCurrenciesData)
			{
				DataLine = _ConvertCurrencyObjectToLine(C);
				MyFile << DataLine << endl;
			}
			MyFile.close();
		}

	}

	static string _ConvertCurrencyObjectToLine(clsCurrency Currency, string separator = "#//#") {

		string DataLine = "";

		DataLine += Currency._Country + separator;
		DataLine += Currency._CurrencyCode + separator;
		DataLine += Currency._CurrencyName + separator;
		DataLine += to_string(Currency._Rate);

		return DataLine;
	}

	static clsCurrency _ConvertLineToCurrencyObject(string Line, string separator = "#//#") {

		vector<string>_vTokens = clsString::Split(Line, separator);

		return clsCurrency(enMode::UpdateMode, _vTokens[0], _vTokens[1], _vTokens[2], stof(_vTokens[3]));

	}

	static vector<clsCurrency>_LoadCurrenciesDataFromFile(){

		vector<clsCurrency>_vCurrenciesData;
		fstream MyFile;

		MyFile.open("Currencies.txt", ios::in);

		if (MyFile.is_open())
		{

			string Line;
			while (getline(MyFile, Line))
			{
				clsCurrency Currency = _ConvertLineToCurrencyObject(Line);
				_vCurrenciesData.push_back(Currency);
			}
			MyFile.close();
		}
		return _vCurrenciesData;
	}

	static clsCurrency _GetEmptyCurrencyObject() {
		return clsCurrency(enMode::EmptyMode, "", "", "", 0);
	}

	void _Update(){

		vector<clsCurrency>_vCurrencies;
		_vCurrencies = _LoadCurrenciesDataFromFile();

		for (clsCurrency & C : _vCurrencies)
		{
			if (C.CurrencyCode() == CurrencyCode())
			{
				C = *this;
				break;
			}
		}

		_SaveCurrenciesDataToFile(_vCurrencies);
	}

public:

	clsCurrency(enMode Mode, string Country, string CurrencyCode, string CurrencyName, float Rate) {

		_Mode = Mode;
		_Country = Country;
		_CurrencyCode = CurrencyCode;
		_CurrencyName = CurrencyName;
		_Rate = Rate;
	}

	bool IsEmpty() {

		return (_Mode == enMode::EmptyMode);

	}

	string Country() {
		return _Country;
	}

	string CurrencyCode() {
		return _CurrencyCode;
	}

	string CurrencyName() {
		return _CurrencyName;
	}

	void UpdateRate(float NewRate) {

		_Rate = NewRate;
		_Update();
	}
	
	float Rate() {
		return _Rate;
	}

	static clsCurrency FindByCode(string CurrencyCode) {
		
		CurrencyCode = clsString::UpperAllString(CurrencyCode);

		fstream MyFile;

		MyFile.open("Currencies.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsCurrency Currency = _ConvertLineToCurrencyObject(Line);

				if (clsString::UpperAllString(Currency.CurrencyCode()) == CurrencyCode)
				{
					MyFile.close();
					return Currency;
				}
			}
		}
		return _GetEmptyCurrencyObject();
	}

	static clsCurrency FindByCountry(string Country) {

		Country = clsString::UpperAllString(Country);

		fstream MyFile;

		MyFile.open("Currencies.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsCurrency Currency = _ConvertLineToCurrencyObject(Line);

				if (clsString::UpperAllString(Currency.Country()) == Country)
				{
					MyFile.close();
					return Currency;
				}
			}
		}
		return _GetEmptyCurrencyObject();

	}

	static bool IsCurrencyExist(string CurrencyCode) {
		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
		return (!Currency.IsEmpty());
	}

	static vector<clsCurrency> GetCurrenciesList() {
		
		return _LoadCurrenciesDataFromFile();
	}
		
	float ConvertToUsd(float Amount) {

		return (float)(Amount / Rate());

	}

	float ConvertToAnotherCurrency(float Amount, clsCurrency Currency2) {

		float ExchangeRate;
		ExchangeRate = ConvertToUsd(Amount);

		if (Currency2.CurrencyCode() == "USD")
		{
			return ExchangeRate;
		}

		return (float)(ExchangeRate * Currency2.Rate());

	}

};

