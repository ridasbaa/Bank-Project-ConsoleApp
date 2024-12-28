#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class clsString
{

private:
	string _Value;

public:

	clsString() {
		_Value = "";
	}
	clsString(string Value) {
		_Value = Value;
	}

	void SetValue(string Value) {
		_Value = Value;
	}
	string GetValue() {
		return _Value;
	}
	__declspec(property(get = GetValue, put = SetValue)) string Value;

	static short Length(string Text) {
		return Text.length();
	}
	short Length() {
		return _Value.length();
	}

	static string LowerAllString(string Text) {

		for (short i = 0; i < Text.length(); i++) {

			Text[i] = tolower(Text[i]);
		}

		return Text;

	}
	void LowerAllString() {
		_Value = LowerAllString(_Value);
	}

	static string UpperAllString(string Text) {

		for (short i = 0; i < Text.length(); i++) {

			Text[i] = toupper(Text[i]);
		}

		return Text;

	}
	void UpperAllString() {
		_Value = UpperAllString(_Value);
	}

	static string UpperFirstLetterInEachWord(string Text) {

		bool IsFirstLetter = true;

		for (short i = 0; i < Text.length(); i++) {

			if (Text[i] != ' ' && IsFirstLetter) {
				Text[i] = toupper(Text[i]);
			}

			IsFirstLetter = (Text[i] == ' ' ? true : false);

		}

		return Text;

	}
	void UpperFirstLetterInEachWord() {
		_Value = UpperFirstLetterInEachWord(_Value);
	}

	static string LowerFirstLetterInEachWord(string Text) {

		bool IsFirstLetter = true;

		for (short i = 0; i < Text.length(); i++) {

			if (Text[i] != ' ' && IsFirstLetter) {
				Text[i] = tolower(Text[i]);
			}

			IsFirstLetter = (Text[i] == ' ' ? true : false);

		}

		return Text;

	}
	void LowerFirstLetterInEachWord() {
		_Value = LowerFirstLetterInEachWord(_Value);
	}

	static char InvertChar(char Letter) {

		return isupper(Letter) ? tolower(Letter) : toupper(Letter);

	}

	__declspec(property(get = GetMatchCase, put = setMatchCase)) bool MatchCase;

	enum enCountLetters { CapitalLetters = 0, SmallLetters = 1, All = 2 };

	static short CountLetters(string Text, enCountLetters LetterType = enCountLetters::All) {

		int Counter = 0;

		for (int i = 0; i < Text.length(); i++) {

			if (LetterType == enCountLetters::CapitalLetters && isupper(Text[i])) {
				Counter++;
			}

			if (LetterType == enCountLetters::SmallLetters && islower(Text[i])) {
				Counter++;
			}

		}

		return Counter;

	}

	static short CountCapitalLetters(string Text) {

		int CapitalLetterNumber = 0;

		for (int i = 0; i < Text.length(); i++) {

			if (Text[i] != ' ') {
				if (isupper(Text[i])) {
					CapitalLetterNumber++;
				}
			}

		}

		return CapitalLetterNumber;

	}
	short CountCapitalLetters() {
		return CountCapitalLetters(_Value);
	}

	static short CountSmallLetters(string Text) {

		int SmalllLetterNumber = 0;

		for (int i = 0; i < Text.length(); i++) {

			if (Text[i] != ' ') {
				if (!isupper(Text[i])) {
					SmalllLetterNumber++;
				}
			}

		}

		return SmalllLetterNumber;

	}
	short CountSmallLetters() {
		return CountSmallLetters(_Value);
	}

	static short CountSpecificLetter(string Text, char LetterToCheck, bool MatchCase = true) {

		short Counter = 0;
		for (int i = 0; i < Text.length(); i++)
		{
			if (MatchCase)
			{
				if (Text[i] == LetterToCheck)
					Counter++;
			}
			else
			{
				if (tolower(Text[i]) == tolower(LetterToCheck))
					Counter++;
			}

		}
		return Counter;
	}
	short CountSpecificLetter(char LetterToCheck, bool MatchCase = true) {
		return CountSpecificLetter(_Value, LetterToCheck, MatchCase);
	}

	static bool IsVowel(char Letter) {

		Letter = tolower(Letter);

		return ((Letter == 'a') || (Letter == 'e') || (Letter == 'i') || (Letter == 'o') || (Letter == 'u'));
	}

	static short CountVowels(string Text) {

		short Counter = 0;
		for (int i = 0; i < Text.length(); i++)
		{

			if (IsVowel(Text[i]))
			{
				Counter++;
			}

		}

		return Counter;
	}
	short CountVowels() {
		return CountVowels(_Value);
	}

	static vector<string> Split(string Text, string delim) {

		vector<string>vTokens;

		short pos = 0;
		string sWord;

		while ((pos = Text.find(delim)) != std::string::npos)
		{

			sWord = Text.substr(0, pos);
			if (!sWord.empty())
			{
				vTokens.push_back(sWord);
			}

			Text.erase(0, pos + delim.length());

		}

		if (!Text.empty())
		{
			vTokens.push_back(Text);
		}

		return vTokens;
	}
	vector<string> Split(string delim) {
		return Split(_Value, delim);
	}

	static string TrimLeft(string Text) {

		string TextAfterTrim;
		for (short i = 0; i < Text.length(); i++) {

			if (Text[i] != ' ') {
				return Text.substr(i, Text.length() - i);
			}
		}

		return TextAfterTrim;

	}
	void TrimLeft() {
		_Value = TrimLeft(_Value);
	}

	static string TrimRight(string Text) {

		string TextAfterTrim;
		for (short i = Text.length() - 1; i >= 0; i--) {

			if (Text[i] != ' ') {
				return Text.substr(0, i + 1);
			}

		}

		return TextAfterTrim;

	}
	void TrimRight() {
		_Value = TrimRight(_Value);
	}

	static string Trim(string Text) {

		return (TrimLeft(TrimRight(Text)));

	}
	void Trim() {
		_Value = Trim(_Value);
	}

	static string JoinString(vector<string> vData, string delim) {

		string FullString = "";

		for (short i = 0; i < vData.size(); i++) {

			FullString += vData.at(i);

			if (i != vData.size() - 1) {
				FullString += delim;
			}

		}

		return FullString;

		// anothe way : ADVANCED WAY :

		for (string& s : vData) {

			FullString = FullString + s + delim;
		}

		return FullString.substr(0, FullString.length() - delim.length());

	}
	static string JoinString(string arrOfData[], short arrLength, string delim) {

		string FullString = "";

		for (short i = 0; i < arrLength; i++) {

			FullString = FullString + arrOfData[i] + delim;
		}

		return FullString.substr(0, FullString.length() - delim.length());


	}

	static string ReverseWords(string Text) {

		vector<string>vString;
		vString = Split(Text, " ");
		string ReversedString = "";

		vector<string>::iterator iter = vString.end();

		while (iter != vString.begin())
		{
			--iter;
			ReversedString += *iter + " ";
		}
		return ReversedString;

	}
	void ReverseWords() {
		_Value = ReverseWords(_Value);
	}

	static string ReplaceWord(string Text, string StringToReplace, string ReplaceTo, bool MatchCase = true) {


		size_t pos;
		vector<string>vString = Split(Text, " ");

		for (string& s : vString)
		{
			if (MatchCase) {
				if (s == StringToReplace)
				{
					s = ReplaceTo;
				}
			}
			else
			{
				if (LowerAllString(s) == LowerAllString(StringToReplace))
				{
					s = ReplaceTo;
				}
			}
		}

		return JoinString(vString, " ");
	}
	string ReplaceWord(string StringToReplace, string ReplaceTo) {
		return ReplaceWord(_Value, StringToReplace, ReplaceTo);
	}

	static string InvertAllTheLetters(string Text) {

		for (int i = 0; i < Text.length(); i++) {

			Text[i] = InvertChar(Text[i]);

		}

		return Text;
	}
	void InvertAllTheLetters() {
		_Value = InvertAllTheLetters(_Value);
	}

	static string RemoveAllPactuations(string Text) {

		string Text2 = "";

		for (short i = 0; i < Text.length(); i++)
		{

			if (!ispunct(Text[i]))
			{
				Text2 += Text[i];
			}

		}


		return Text2;

	}
	void RemoveAllPactuations() {
		_Value = RemoveAllPactuations(_Value);
	}

	static short CountWords(string Text) {

		short counter = 0;
		string delim = " ";
		short pos = 0;
		string sWord;
		while ((pos = Text.find(delim)) != std::string::npos)
		{
			sWord = Text.substr(0, pos);
			if (sWord != "")
			{
				counter++;
			}

			Text.erase(0, pos + delim.length());
		}

		return ++counter;

	}
	short CountWords() {
		return CountWords(_Value);
	}



};

