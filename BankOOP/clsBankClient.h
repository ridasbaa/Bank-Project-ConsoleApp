#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "clsPerson.h"
#include "clsString.h"
#include "clsScreen.h"
#include "clsDate.h"

using namespace std;

class clsBankClient : public clsPerson
{
private:
	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2};
	enMode _Mode;

	string _AccountNumber;
	string _PinCode;
	float _AccountBalance;
	bool _MarkedForDelete = false;

	static clsBankClient _ConvertLineToClientObject(string Line, string Separator = "#//#") {

		vector<string>vClientData;
		vClientData = clsString::Split(Line, Separator);

		return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2], vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));

	}

	static string _ConvertClientObjectToLine(clsBankClient Client, string Separator = "#//#") {
		
		string Line = "";

		Line = Client.FirstName + Separator;
		Line += Client.LastName + Separator;
		Line += Client.Email + Separator;
		Line += Client.Phone + Separator;
		Line += Client.AccountNumber() + Separator;
		Line += Client._PinCode + Separator;
		Line += to_string(Client._AccountBalance);
		return Line;
			
	}

	static clsBankClient _GetEmptyClientObject() {
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "","", 0);
	}

	static vector<clsBankClient> _LoadClientsDataFromFile() {

		vector<clsBankClient>vClients;

		fstream MyFile;

		MyFile.open("Clients.txt", ios::in);

		if (MyFile.is_open())
		{

			string Line;
			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);
				vClients.push_back(Client);
			}

			MyFile.close();

		}
		return vClients;

	}

	static void _SaveClientsDataToFile(vector<clsBankClient>_vClients) {

		fstream MyFile;

		MyFile.open("Clients.txt", ios::out);

		if (MyFile.is_open())
		{
			string DataLine = "";
			for (clsBankClient& C : _vClients)
			{
				if (C.MarkedForDelete() == false)
				{
					DataLine = _ConvertClientObjectToLine(C);
					MyFile << DataLine << endl;
				}
			}
			MyFile.close();
		}

	}

	void _Update() {

		vector<clsBankClient>_vClients;
		_vClients = _LoadClientsDataFromFile();

		for (clsBankClient& C : _vClients)
		{
			if (C.AccountNumber() == AccountNumber())
			{
				C = *this;
				break;
			}
		}
		_SaveClientsDataToFile(_vClients);
	}

	void _AddNew() {
		
		_AddDataLineToFile(_ConvertClientObjectToLine(*this));

	}

	void _AddDataLineToFile(string stDataLine) {

		fstream MyFile;
		MyFile.open("Clients.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << stDataLine << endl;
			
			MyFile.close();
		}


	}

	struct stTransferLogRecord;

	string _PrepareTransferLog(double Amount, clsBankClient DestinationClient, string Username, string separator = "#//#") {

		string TransferRecord = "";

		TransferRecord += clsDate::GetCurrentTime() + separator;
		TransferRecord += AccountNumber() + separator;
		TransferRecord += DestinationClient.AccountNumber() + separator;
		TransferRecord += to_string(Amount) + separator;
		TransferRecord += to_string(_AccountBalance) + separator;
		TransferRecord += to_string(DestinationClient.AccountBalance) + separator;
		TransferRecord += Username;

		return TransferRecord;
	}

	void _RegisterTransferLog(double Amount, clsBankClient DestinationClient, string Username) {

		fstream MyFile;
		string sDataline = _PrepareTransferLog(Amount, DestinationClient, Username);

		MyFile.open("TransferLog.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << sDataline << endl;
			MyFile.close();
		}
	}

	static stTransferLogRecord _ConvertLinetoTransferRecord(string Line) {

		vector<string>_vTransferLog;
		_vTransferLog = clsString::Split(Line, "#//#");

		stTransferLogRecord TransferLogRecord;

		TransferLogRecord.DateTime = _vTransferLog[0];
		TransferLogRecord.SourceClientAccountNumber = _vTransferLog[1];
		TransferLogRecord.DestinationClientAccountNumber = _vTransferLog[2];
		TransferLogRecord.Amount = stod(_vTransferLog[3]);
		TransferLogRecord.SourceClientAccountBalanceAfter = stod(_vTransferLog[4]);
		TransferLogRecord.DestinationClientAccountBalanceAfter = stod(_vTransferLog[5]);
		TransferLogRecord.Implementer = _vTransferLog[6];

		return TransferLogRecord;
	}

public:

	clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone, string AccountNumber, string PinCode, float AccountBalance)
		         : clsPerson(FirstName, LastName, Email, Phone)
	{
		_AccountNumber = AccountNumber;
		_AccountBalance = AccountBalance;
		_PinCode = PinCode;
		_Mode = Mode;
	}

	struct stTransferLogRecord {
		string DateTime;
		string SourceClientAccountNumber;
		string DestinationClientAccountNumber;
		double Amount;
		double SourceClientAccountBalanceAfter;
		double DestinationClientAccountBalanceAfter;
		string Implementer;
	};

	bool IsEmpty() {
		return (_Mode == enMode::EmptyMode);
	}

	bool MarkedForDelete() {
		return _MarkedForDelete;
	}

	string AccountNumber() {
		return _AccountNumber;
	}

	void setPinCode(string PinCode) {
		_PinCode = PinCode;
	}
	string GetPinCode() {
		return _PinCode;
	}
	__declspec(property(get = GetPinCode, put = setPinCode)) string PinCode;

	void setAccountBalance(float AccountBalance) {
		_AccountBalance = AccountBalance;
	}
	float GetAccountBalance() {
		return _AccountBalance;
	}
	__declspec(property(get = GetAccountBalance, put = setAccountBalance)) float AccountBalance;

	static clsBankClient Find(string AccountNumber) {

		vector<clsBankClient>vClients;
		fstream MyFile;

		MyFile.open("Clients.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);
				if (Client.AccountNumber() == AccountNumber) 
				{
					MyFile.close();
					return Client;
				}

				vClients.push_back(Client);
			}
			MyFile.close();
		}
		return _GetEmptyClientObject();
	}

	static clsBankClient Find(string AccountNumber, string PinCode) {

		vector<clsBankClient>vClients;

		fstream MyFile;

		MyFile.open("Clients.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);

				if (Client.AccountNumber() == AccountNumber && Client.PinCode == PinCode)
				{
					MyFile.close();
					return Client;
				}
				vClients.push_back(Client);
			}
			MyFile.close();
		}
		return _GetEmptyClientObject();
	}

	enum enSaveResult { svFailedObject = 0, svSucceeded = 1, svFailedAccNumberExist = 2 };

	enSaveResult Save() {

		switch (_Mode)
		{
		case clsBankClient::EmptyMode:
			return svFailedObject;
			break;
		case clsBankClient::UpdateMode:
			_Update();
			return svSucceeded;
			break;
		case clsBankClient::AddNewMode:

			if (clsBankClient::IsClientExist(_AccountNumber))
			{
				return enSaveResult::svFailedAccNumberExist;
			}
			else
			{
				_AddNew();
				_Mode = enMode::UpdateMode;
				return svSucceeded;
			}
			break;
		}

	}

	static bool IsClientExist(string AccountNumber) {
		clsBankClient Client1 = clsBankClient::Find(AccountNumber);
		return (!Client1.IsEmpty());
	}

	static clsBankClient GetAddNewClientObject(string AccountNumber) {

		return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
	}

	bool Delete() {

		vector<clsBankClient>_vClients;
		_vClients = _LoadClientsDataFromFile();

		for (clsBankClient& C : _vClients)
		{
			if (C.AccountNumber() == _AccountNumber)
			{
				C._MarkedForDelete = true;
				break;
			}
		}

		_SaveClientsDataToFile(_vClients);
		*this = _GetEmptyClientObject();
		return true;
	}

	static vector<clsBankClient> GetClientList() {
		return _LoadClientsDataFromFile();

	}

	static double GetTotalBalances() {

		vector<clsBankClient>vClients = clsBankClient::GetClientList();
		double TotalBalances = 0;

		for (clsBankClient C: vClients)
		{
			TotalBalances += C.AccountBalance;
		}
		return TotalBalances;
	}

	void Deposite(double Amount) {

		_AccountBalance += Amount;
		Save();
	}

	bool Withdraw(double Amount) {

		if (Amount > _AccountBalance)
		{
			return false;
		}
		else
		{
			_AccountBalance -= Amount;
			Save();
			return true;
		}
		return false;
	}

	bool Transfer(double Amount, clsBankClient& DestinationClient, string Username)	 {

		if (Amount > AccountBalance)
		{
			return false;
		}

		Withdraw(Amount);
		DestinationClient.Deposite(Amount);
		_RegisterTransferLog(Amount, DestinationClient, Username);
		return true;
	}

	static vector<stTransferLogRecord> GetTransferLogList() {

		vector<stTransferLogRecord>vTtransferLogs;
		fstream MyFile;

		MyFile.open("TransferLog.txt", ios::in);

		if (MyFile.is_open())
		{

			string Line;
			stTransferLogRecord TransferLog;
			while (getline(MyFile, Line))
			{
				TransferLog = _ConvertLinetoTransferRecord(Line);
				vTtransferLogs.push_back(TransferLog);
			}
			MyFile.close();
		}

		return vTtransferLogs;
	}


};

