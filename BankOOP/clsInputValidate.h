#pragma once
#include<iostream>
#include<string>
#include"clsDate.h"
#include"clsString.h"

using namespace std;

class clsInputValidate
{
public:
	static bool IsNumberBetween(short Number, short From, short To) {

		if (Number >= From && Number <= To)
			return true;
		else
			return false;
	}

	static bool IsNumberBetween(int Number, int From, int To) {

		if (Number >= From && Number <= To)
			return true;
		else
			return false;
	}

	static bool IsNumberBetween(float Number, float From, float To) {

		if (Number >= From && Number <= To)
			return true;
		else
			return false;
	}

	static bool IsNumberBetween(double Number, double From, double To) {

		if (Number >= From && Number <= To)
			return true;
		else
			return false;
	}

	static bool IsDateBetween(clsDate DateToCheck, clsDate Date1, clsDate Date2) {

		if (clsDate::IsDate1BeforeDate2(Date1, Date2))
		{
			if (clsDate::IsDate1BeforeDate2(DateToCheck, Date1) || clsDate::IsDate1EqualsDate2(DateToCheck, Date1))
			{
				return false;
			}
			else if (clsDate::IsDate1BeforeDate2(DateToCheck, Date2))
			{
				return true;
			}
		}
		else
		{
			if (clsDate::IsDate1BeforeDate2(DateToCheck, Date2) || clsDate::IsDate1EqualsDate2(DateToCheck, Date2))
			{
				return false;
			}
			else if (clsDate::IsDate1BeforeDate2(DateToCheck, Date1))
			{
				return true;
			}
		}

		return false;

	}

	static short ReadShortNumber(string Message = "Please enter an int number : \n", string ErrorMessage = "\nInvalid Number, Please try again : ") {

		short Number;
		cout << Message;
		cin >> Number;

		while (cin.fail())
		{

			cin.clear();
			cin.ignore(std::numeric_limits < std::streamsize>::max(), '\n');
			cout << ErrorMessage;
			cin >> Number;

		}

		return Number;


	}

	static int ReadIntNumber(string Message = "Please enter an int number : \n", string ErrorMessage = "\nInvalid Number, Please try again : ") {

		int Number;
		cout << Message;
		cin >> Number;

		while (cin.fail())
		{

			cin.clear();
			cin.ignore(std::numeric_limits < std::streamsize>::max(), '\n');
			cout << ErrorMessage;
			cin >> Number;

		}

		return Number;


	}

	static int ReadIntNumberInRange(int From, int To, string ErrorMessage = "") {

		int Number = ReadIntNumber();

		while (!IsNumberBetween(Number, From, To))
		{
			cout << ErrorMessage << endl;
			cout << "Please enter a number between " << From << " and " << To << " : ";
			cin >> Number;

		}

		return Number;


	}

	static short ReadShortNumberInRange(short From, short To, string ErrorMessage = "") {

		short Number = ReadShortNumber();

		while (!IsNumberBetween(Number, From, To))
		{
			cout << ErrorMessage << endl;
			cout << "Please enter a number between " << From << " and " << To << " : ";
			cin >> Number;

		}

		return Number;


	}

	static double ReadFloatNumber(string Message = "", string ErrorMessage = "\nInvalid Number, Please try again : ") {

		float Number;
		cout << Message;
		cin >> Number;

		while (cin.fail())
		{
			cin.clear();
			cin.ignore(std::numeric_limits < std::streamsize>::max(), '\n');
			cout << ErrorMessage << endl;
			cin >> Number;

		}

		return Number;


	}

	static float ReadFloatNumberInRange(float From, float To, string ErrorMessage) {

		float Number = ReadDblNumber();
		while (!IsNumberBetween(Number, From, To))
		{
			cout << ErrorMessage << endl;
			cout << "Please enter a number between " << From << " and " << To << " : ";
			cin >> Number;

		}

		return Number;


	}

	static double ReadDblNumber(string ErrorMessage = "\nInvalid Number, Please try again : ") {

		double Number;
		cout << "Please enter a double number : ";
		cin >> Number;

		while (cin.fail())
		{
			cin.clear();
			cin.ignore(std::numeric_limits < std::streamsize>::max(), '\n');
			cout << ErrorMessage << endl;
			cin >> Number;

		}

		return Number;


	}

	static double ReadDblNumberInRange(double From, double To, string ErrorMessage) {

		double Number = ReadDblNumber();
		while (!IsNumberBetween(Number, From, To))
		{
			cout << ErrorMessage << endl;
			cout << "Please enter a number between " << From << " and " << To << " : ";
			cin >> Number;

		}

		return Number;


	}

	template <typename T> static T ReadNumberInRange(T From, T To, string ErrorMessage) {

		T Number = ReadDblNumber();
		while (!IsNumberBetween(Number, From, To))
		{
			cout << ErrorMessage << endl;
			cout << "Please enter a number between " << From << " and " << To << " : ";
			cin >> Number;

		}

		return Number;

	}

	static bool IsValideDate(clsDate Date) {

		return clsDate::IsValideDate(Date);
	}

	static string ReadString() {
		string text = "";
		getline(cin >> ws, text);
		return text;
	}

};

