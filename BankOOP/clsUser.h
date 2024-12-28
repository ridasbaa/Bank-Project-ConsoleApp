#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include "clsDate.h"
#include "clsUtil.h"

using namespace std;

class clsUser : public clsPerson
{

private:
	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
	enMode _Mode;
	string _Username;
	string _Password;
	int _Permissions = 0;

	bool _MarkedForDelete = false;

	struct stLoginRegisterRecord;

	static stLoginRegisterRecord _ConvertLoginRegisterLine(string Line) {

		stLoginRegisterRecord LoginRegisterRecord;

		vector<string>vLoginRegistrationDataLine = clsString::Split(Line, "#//#");

		LoginRegisterRecord.DateTime = vLoginRegistrationDataLine[0];
		LoginRegisterRecord.Username = vLoginRegistrationDataLine[1];
		LoginRegisterRecord.Password = vLoginRegistrationDataLine[2];
		LoginRegisterRecord.Permissions = stoi(vLoginRegistrationDataLine[3]);

		return LoginRegisterRecord;

	}

	string _PrepareLoginRecord(string Separator = "#//#") {

		string Line = "";

		Line += clsDate::GetCurrentTime() + Separator;
		Line += Username + Separator;
		Line += clsUtil::EncryptText(Password, 3) + Separator;
		Line += to_string(Permissions);

		return Line;

	}

	static clsUser _ConvertLineToUserObject(string Line, string Separator = "#//#") {

		vector<string>_vUsers;
		_vUsers = clsString::Split(Line, Separator);

		return clsUser(enMode::UpdateMode, _vUsers[0], _vUsers[1], _vUsers[2], _vUsers[3], _vUsers[4], clsUtil::DecryptText(_vUsers[5],3), stoi(_vUsers[6]));
	}

	static string _ConvertUserObjectToLine(clsUser User, string Separator = "#//#") {

		string Line = "";

		Line = User.FirstName + Separator;
		Line += User.LastName + Separator;
		Line += User.Email + Separator;
		Line += User.Phone + Separator;
		Line += User._Username + Separator;
		Line += clsUtil::EncryptText(User._Password, 3) + Separator;
		Line += to_string(User._Permissions);

		return Line;
	}

	static clsUser _GetEmptyUserObject() {
		return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	static vector<clsUser>_LoadUsersDataFromFile() {

		vector<clsUser>_vUsers;

		fstream MyFile;

		MyFile.open("Users.txt", ios::in);

		if (MyFile.is_open()) {

			string Line;
			while (getline(MyFile, Line)) {

				clsUser User = _ConvertLineToUserObject(Line);
				_vUsers.push_back(User);
			}
			MyFile.close();
		}

		return _vUsers;
	}

	static void _SaveClientsDataToFile(vector<clsUser>_vUsers) {

		fstream MyFile;

		MyFile.open("Users.txt", ios::out);

		if (MyFile.is_open())
		{
			string DataLine = "";
			for (clsUser U : _vUsers)
			{
				if (U.MarkedForDelete() == false)
				{
					DataLine = _ConvertUserObjectToLine(U);
					MyFile << DataLine << endl;
				}
			}
			MyFile.close();
		}

	}

	void _AddDataLineToFile(string stDataLine) {

		fstream MyFile;
		MyFile.open("Users.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << stDataLine << endl;

			MyFile.close();
		}


	}

	void _Update() {

		vector<clsUser>_vUsers;
		_vUsers = _LoadUsersDataFromFile();

		for (clsUser& U : _vUsers)
		{
			if (U.Username == Username)
			{
				U = *this;
				break;
			}
		}
		_SaveClientsDataToFile(_vUsers);
	}

	void _AddNew() {

		_AddDataLineToFile(_ConvertUserObjectToLine(*this));

	}

public:

	enum enPermissions { eAll = -1, pClientList = 1, pAddClient = 2, pDeleteClient = 4, pUpdateClient = 8, pFindClient = 16, pTransactions = 32, pManageUsers = 64, eLoginRegister = 128 };

	struct stLoginRegisterRecord {
		string DateTime;
		string Username;
		string Password;
		int Permissions;
	};

	clsUser(enMode Mode, string FirstName, string LastName, string Email, string Phone, string Username, string Password, int Permissions)
			: clsPerson (FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_Username = Username;
		_Password = Password;
		_Permissions = Permissions;
	}

	bool IsEmpty() {
		return (_Mode == enMode::EmptyMode);
	}

	bool MarkedForDelete() {
		return _MarkedForDelete;
	}

	void SetUsername(string Username) {
		_Username = Username;
	}
	string GetUsername() {
		return _Username;
	}
	__declspec(property(get = GetUsername, put = SetUsername)) string Username;

	void SetPasssword(string Password) {
		_Password = Password;
	}
	string GetPassword() {
		return _Password;
	}
	__declspec(property(get = GetPassword, put = SetPasssword)) string Password;

	void SetPermissions(int Permissions) {
		_Permissions = Permissions;
	}
	int GetPermissions() {
		return _Permissions;
	}
	__declspec(property(get = GetPermissions, put = SetPermissions)) int Permissions;

	static clsUser Find(string Username) {

		fstream MyFile;

		MyFile.open("Users.txt", ios::in);

		if (MyFile.is_open())
		{

			string Line;
			while (getline(MyFile, Line))
			{
				clsUser User = _ConvertLineToUserObject(Line);
				if (User.Username == Username)
				{
					MyFile.close();
					return User;
				}
			}

			MyFile.close();
		}

		return _GetEmptyUserObject();
	}

	static clsUser Find(string Username, string Password) {

		fstream MyFile;

		MyFile.open("Users.txt", ios::in);

		if (MyFile.is_open())
		{

			string Line;
			while (getline(MyFile, Line))
			{
				clsUser User = _ConvertLineToUserObject(Line);
				if (User.Username == Username && User.Password == Password)
				{
					MyFile.close();
					return User;
				}
			}

			MyFile.close();
		}

		return _GetEmptyUserObject();
	}

	static bool IsUserExist(string Username) {

		clsUser User = clsUser::Find(Username);
		return (!User.IsEmpty());

	}

	static bool IsUserExist(string Username, string Password) {

		clsUser User = clsUser::Find(Username, Password);
		return (!User.IsEmpty());

	}

	enum enSaveResult { svFailedEmptyObject = 0, svSuccessded = 1, svFailedUserExists = 2 };

	enSaveResult Save() {

		switch (_Mode)
		{
		case clsUser::EmptyMode:
			if (IsEmpty())
			{
				return enSaveResult::svFailedEmptyObject;
			}
			break;
		case clsUser::UpdateMode:
			_Update();
			return enSaveResult::svSuccessded;
			break;
		case clsUser::AddNewMode:
			if (clsUser::IsUserExist(_Username))
			{
				enSaveResult::svFailedUserExists;
			}
			else
			{
				_AddNew();
				_Mode = enMode::UpdateMode;
				return enSaveResult::svSuccessded;
			}
			break;
		}

	}

	bool Delete() {

		vector<clsUser>vUsers = _LoadUsersDataFromFile();

		for (clsUser& U : vUsers)
		{

			if (U.Username == _Username)
			{
				U._MarkedForDelete = true;
				break;
			}

		}

		_SaveClientsDataToFile(vUsers);
		*this = _GetEmptyUserObject();
		return true;
	}

	static clsUser GetAddNewUserObject(string UserName)
	{
		return clsUser(enMode::AddNewMode, "", "", "", "", UserName, "", 0);
	}

	static vector <clsUser> GetUsersList()
	{
		return _LoadUsersDataFromFile();
	}

	bool _CheckAccessPermission(enPermissions Permission) {

		if (this->Permissions == clsUser::enPermissions::eAll) {
			return true;
		}
		else if ((Permission & this->Permissions) == Permission) {
			return true;
		}
		return false;
	}

	void RegisterLogin() {

		string stDataLine = _PrepareLoginRecord();

		fstream MyFile;
		MyFile.open("LoginRegister.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << stDataLine << endl;
			MyFile.close();
		}

	}

	static vector<stLoginRegisterRecord> GetRegistrationsList() {

		vector<stLoginRegisterRecord>_vRegistrations;
		fstream MyFile;

		MyFile.open("LoginRegister.txt", ios::in);

		if (MyFile.is_open()) {

			stLoginRegisterRecord Record;
			string Line;
			while (getline(MyFile, Line)) {

				Record = _ConvertLoginRegisterLine(Line);
				_vRegistrations.push_back(Record);
			}
			MyFile.close();
		}

		return _vRegistrations;

	}




};

