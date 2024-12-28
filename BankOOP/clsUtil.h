#pragma once
#include<iostream>
#include"clsDate.h"
#include"clsString.h"

using namespace std;



class clsUtil
{

public:
	static void Srand() {
		srand((unsigned)time(NULL));
	}

	static int RandomNumber(int From, int To) {

		int rundNum = rand() % (To - From + 1) + From;

		return rundNum;
	}

	enum enCharType { SmallLetter = 1, CapitalLetter = 2, Digit = 3, SpecialChar = 4, MixChar = 5 };

	static char GetRandomCharacter(enCharType CharType) {

		if (CharType == enCharType::MixChar)
		{
			CharType = (enCharType)RandomNumber(1, 3);
		}

		switch (CharType)
		{
		case SmallLetter:
			return char(RandomNumber(97, 122));
			break;
		case CapitalLetter:
			return char(RandomNumber(65, 90));
			break;
		case SpecialChar:
			return char(RandomNumber(33, 46));
			break;
		case Digit:
			return char(RandomNumber(48, 57));
			break;
		}

	}

	static string GenerateWord(enCharType CharType, int length) {

		string word;

		for (int i = 1; i <= length; i++) {

			word = word + GetRandomCharacter(CharType);

		}
		return word;
	}

	static string GenerateKey(enCharType CharType) {

		string key = "";

		key = GenerateWord(CharType, 4) + "-";
		key = key + GenerateWord(CharType, 4) + "-";
		key = key + GenerateWord(CharType, 4) + "-";
		key = key + GenerateWord(CharType, 4);

		return key;
	}

	static void GenerateKeys(int Number, enCharType CharType) {


		for (int i = 1; i <= Number; i++)
		{
			string P[4];


			for (int j = 0; j < 4; j++)
			{
				string word = "";

				word = GetRandomCharacter(CharType);
				word = word + GetRandomCharacter(CharType);
				word = word + GetRandomCharacter(CharType);
				word = word + GetRandomCharacter(CharType);

				P[j] = word;

			}

			cout << "Key [" << i << "] " << P[0] << " - " << P[1] << " - " << P[2] << " - " << P[3] << endl;

		}

	}

	static void swap(int& Num1, int& Num2) {
		int Temp;
		Temp = Num1;
		Num1 = Num2;
		Num2 = Temp;
	}

	static void swap(double& Num1, double& Num2) {
		double Temp;
		Temp = Num1;
		Num1 = Num2;
		Num2 = Temp;
	}

	static void swap(string& S1, string& S2) {
		string Temp;
		Temp = S1;
		S1 = S2;
		S2 = Temp;
	}

	static void swap(clsDate& Date1, clsDate& Date2) {
		clsDate::SwapDates(Date1, Date2);
	}

	static void ShuffleArray(int arr[100], int arrLength) {

		for (int i = 0; i < arrLength; i++) {

			swap(arr[RandomNumber(1, arrLength) - 1], arr[RandomNumber(1, arrLength) - 1]);

		}

	}

	static void ShuffleArray(string arr[100], int arrLength) {

		for (int i = 0; i < arrLength; i++) {

			swap(arr[RandomNumber(1, arrLength) - 1], arr[RandomNumber(1, arrLength) - 1]);

		}

	}

	static void FillArrayWithRandomNumbers(int arr[100], int arrLength, int From, int To) {

		for (int i = 0; i < arrLength; i++)
		{
			arr[i] = RandomNumber(From, To);
		}
	}

	static void FillArrayWithRandomWords(string arr[100], int arrLength, enCharType Chartype, int WordLength) {

		for (int i = 0; i < arrLength; i++)
		{
			arr[i] = GenerateWord(Chartype, WordLength);
		}
	}

	static void FillArrayWithRandomKeys(string arr[100], int arrLength, enCharType Chartype) {

		for (int i = 0; i < arrLength; i++)
		{
			arr[i] = GenerateKey(Chartype);
		}
	}

	static string Tabs(int Tabs) {


		string Tab = "";
		for (int i = 0; i <= Tabs; i++)
		{
			Tab += "\t";
		}
		return Tab;
	}

	static string EncryptText(string Text, short EncryptionKey = 2) {
		for (int i = 0; i < Text.length(); i++) {
			if (Text[i] != ' ') {  // Skip the space character
				Text[i] = char(int(Text[i]) + EncryptionKey);
			}
		}
		return Text;
	}

	static string DecryptText(string Text, short EncryptionKey = 2) {
		for (int i = 0; i < Text.length(); i++) {
			if (Text[i] != ' ') {  // Skip the space character
				Text[i] = char(int(Text[i]) - EncryptionKey);
			}
		}
		return Text;
	}

	static string NumberToText(long long int Number) {

		if (Number == 0)
		{
			return "";
		}

		if (Number >= 1 && Number <= 19)
		{
			string arr[] = { "", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine",
				"Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen" };

			return arr[Number] + " ";
		}

		if (Number >= 20 && Number <= 99)
		{
			string arr[] = { "", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety" };

			return arr[Number / 10] + " " + NumberToText(Number % 10);
		}

		if (Number >= 100 && Number <= 999)
		{

			return NumberToText(Number / 100) + "Hundred" + " " + NumberToText(Number % 100);

		}

		if (Number >= 1000 && Number <= 9999)
		{
			return NumberToText(Number / 1000) + "Thousand" + " " + NumberToText(Number % 1000);
		}

		if (Number >= 10000 && Number <= 99999)
		{
			return NumberToText(Number / 1000) + "Thousand" + " " + NumberToText(Number % 1000);
		}

		if (Number >= 100000 && Number <= 999999)
		{
			return NumberToText(Number / 1000) + "Thousand" + " " + NumberToText(Number % 1000);
		}

		if (Number >= 1000000 && Number <= 9999999)
		{
			return NumberToText(Number / 1000000) + "Million" + " " + NumberToText(Number % 1000000);
		}

		if (Number >= 10000000 && Number <= 99999999)
		{
			return NumberToText(Number / 1000000) + "Million" + " " + NumberToText(Number % 1000000);
		}

		if (Number >= 100000000 && Number <= 999999999)
		{
			return NumberToText(Number / 1000000) + "Million" + " " + NumberToText(Number % 1000000);
		}

		if (Number >= 1000000000 && Number <= 9999999999)
		{
			return NumberToText(Number / 1000000000) + "Billion" + " " + NumberToText(Number % 1000000000);
		}

		if (Number >= 10000000000 && Number <= 99999999999)
		{
			return NumberToText(Number / 1000000000) + "Billion" + " " + NumberToText(Number % 1000000000);
		}

		return "";
	}


};

