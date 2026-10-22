#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include"clsPerson.h"
#include"clsString.h"
#include"Global.h"
#include"clsUser.h"

using namespace std;

class clsBankClient : public clsPerson {
private:
	enum enMode{EmptyMode=0,UpdateMode=1,AddNew=2};
	enMode _Mode;
	string _AccountNumber;
	string _PinCode;
	float _AccountBalance;
	bool _MarkForDelete = false;
	struct stLogTransferRecord;

	static stLogTransferRecord _ConvertTransferLineToRecord(string Line, string Seperator="#//#") {
		stLogTransferRecord LogTransferRecord;
		vector<string>LogTransferDataLine = clsString::Split(Line, Seperator);
		LogTransferRecord.DateTime = LogTransferDataLine[0];
		LogTransferRecord.AccountNumber1 = LogTransferDataLine[1];
		LogTransferRecord.AccountNumber2 = LogTransferDataLine[2];
		LogTransferRecord.Amount =stod( LogTransferDataLine[3]);
		LogTransferRecord.AccountBalance1 = stod(LogTransferDataLine[4]);
		LogTransferRecord.AccountBalance2 = stod(LogTransferDataLine[5]);
		LogTransferRecord.UserName = LogTransferDataLine[6];
		return LogTransferRecord;

	}

	string _PrepareLoginTransfer(double Amount,clsBankClient DestenationClient, string UserName ,string Separater = "#//#") {
		string StRecord = "";
		StRecord += clsDate::GetSystemDateTimeString() + Separater;
		StRecord += AccountNumber() + Separater;
		StRecord += DestenationClient.AccountNumber() + Separater;
		StRecord += to_string(Amount) + Separater;
		StRecord += to_string(AccountBalance)+Separater;
		StRecord += to_string(DestenationClient.AccountBalance) + Separater;
		StRecord += UserName ;
		return StRecord;
	}



	void _RegisterLogInTransfer(double Amount, clsBankClient DestenationClient,string UserName) {
		fstream MyFile;
		string Line;
		Line = _PrepareLoginTransfer(Amount,  DestenationClient,UserName);
		MyFile.open("LogTransfer.txt", ios::out | ios::app);
		if (MyFile.is_open()) {
			MyFile << Line << endl;
		}
		MyFile.close();
	}


	static clsBankClient _ConvertLineToClientObject(string Line, string Separator = "#//#") {
		vector<string>vClient;

		vClient = clsString::Split(Line, Separator);

		return clsBankClient(enMode::UpdateMode, vClient[0], vClient[1], vClient[2], vClient[3], vClient[4], vClient[5],
			stod(vClient[6]));

	}
	static clsBankClient _GetEmptyClientObject() {
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	static string _ConvertClientObjectToLine(clsBankClient Client ,string Separator="#//#") {
		string stData = "";
		stData += Client.FirstName + Separator;
		stData += Client.LastName + Separator;
		stData += Client.Email + Separator;
		stData += Client.PhoneNumber + Separator;
		stData += Client.AccountNumber () + Separator;
		stData += Client.PinCode + Separator;
		stData += to_string(Client.AccountBalance);
		return stData;
	}

	static vector<clsBankClient>_LoadClientDataFromFile() {
		vector<clsBankClient>vClint;
		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);
		if (MyFile.is_open()) {
			string Line;
			while (getline(MyFile, Line)) {
				clsBankClient Client = _ConvertLineToClientObject(Line);
				vClint.push_back(Client);
				
			}
			MyFile.close();
			
		}
		return vClint;
	}

	static void _SaveClientsDataToFile(vector<clsBankClient>VClients) {
		
		
		fstream MyFile;
		
		MyFile.open("Clients.txt", ios::out);
		if (MyFile.is_open()) {
			for (clsBankClient Client : VClients) {
				if(Client.MarkForDelet()==false)
				MyFile << _ConvertClientObjectToLine(Client, "#//#")<<endl;
			
			}
			MyFile.close();
		}
	}

	void _Update() {
		vector<clsBankClient>_VClient;
		_VClient = _LoadClientDataFromFile();
		for (clsBankClient& C : _VClient) {
			if (C.AccountNumber() == AccountNumber()) {
				C = *this;
				break;
			}
		}
		_SaveClientsDataToFile(_VClient);
	}

	static void _AddDataLineToFile(string stDataLine) {
		fstream MyFile;
		
	
		MyFile.open("Clients.txt", ios::out | ios::app);
		if (MyFile.is_open()) {
			MyFile << stDataLine << endl;
			MyFile.close();
		}
	}

	void _AddNew() {
		_AddDataLineToFile(_ConvertClientObjectToLine(*this));
	}


	


public:


	struct stLogTransferRecord {
		string DateTime;
		string AccountNumber1;
		string AccountNumber2;
		double Amount;
		double AccountBalance1;
		double AccountBalance2;
		string UserName;
	};



	clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string PhoneNumber,
		string AccountNumber, string PinCode, float AccountBalance) :clsPerson(FirstName, LastName, Email, PhoneNumber) {
		_Mode = Mode;
		_AccountNumber = AccountNumber;
		_PinCode = PinCode;
		_AccountBalance = AccountBalance;

	}

	bool MarkForDelet() {
		return _MarkForDelete;
	}

	bool IsEmpty() {
		return (_Mode == enMode::EmptyMode);
	}

	string AccountNumber() {
		return _AccountNumber;
	}

	void SetPinCode(string PinCode) {
		_PinCode = PinCode;
	}

	string GetPinCode() {
		return _PinCode;
	}
	__declspec(property(get = GetPinCode, put = SetPinCode))string PinCode;

	void setAccountBalance(float AccountBalance) {
		_AccountBalance = AccountBalance;
	}

	float GetAccountBalance() {
		return _AccountBalance;
	}

	__declspec(property(get = GetAccountBalance, put = setAccountBalance)) float AccountBalance;


	/*void Print()
	{
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << FirstName;
		cout << "\nLastName    : " << LastName;
		cout << "\nFull Name   : " << FullName();
		cout << "\nEmail       : " << Email;
		cout << "\nPhone       : " << PhoneNumber;
		cout << "\nAccouNumber : " << _AccountNumber;
		cout << "\nPassword    : " << _PinCode;
		cout << "\nBalance     : " << _AccountBalance;
		cout << "\n___________________\n";

	}*/

	static clsBankClient Find(string AccountNumber) {
		vector<clsBankClient>vClients;
		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);
		if (MyFile.is_open()) {
			string Line;
			
			while (getline(MyFile, Line)) {
				clsBankClient client = _ConvertLineToClientObject(Line);
				if (client.AccountNumber() == AccountNumber) {
					MyFile.close();
					return client;
				}
				
			}
			MyFile.close();
		}
		return _GetEmptyClientObject();
	}

	static clsBankClient Find(string AccountNumber, string PinCode) {
		vector<clsBankClient>vClient;
		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);
		if (MyFile.is_open()) {
			string Line;
			while (getline(MyFile, Line)) {
				clsBankClient Client = _ConvertLineToClientObject(Line);
				if (Client.AccountNumber() == AccountNumber && Client.PinCode == PinCode) {
					MyFile.close();
					return Client;
				}
			}
			MyFile.close();
		}
		return _GetEmptyClientObject();
	}

	static bool IsClientExist(string AccountNumber) {
		clsBankClient Client1 = clsBankClient::Find(AccountNumber);
		return (!Client1.IsEmpty());
	}

	enum enSaveResults{svFaildEmptyObject=0,svSucceeded=1, svFailedAccountExist =2};

	enSaveResults Save() {
		switch (_Mode) {
		case enMode::EmptyMode:
			return enSaveResults::svFaildEmptyObject;
		case enMode::UpdateMode:
			_Update();
			return enSaveResults::svSucceeded;
		case enMode::AddNew:
			if (IsClientExist(AccountNumber()))
				return enSaveResults::svFailedAccountExist;
			else {
				_AddNew();
				return enSaveResults::svSucceeded;
			}
			
		}
	}

	bool Delete() {
		vector<clsBankClient>_VClients;
		_VClients = _LoadClientDataFromFile();
		for (clsBankClient &client : _VClients) {
			if (client.AccountNumber() == AccountNumber()) {
				client._MarkForDelete = true;
				break;
			}
		}
		_SaveClientsDataToFile(_VClients);
		*this = _GetEmptyClientObject();
		return true;
	}

	static vector<clsBankClient> GetClientList() {
		return _LoadClientDataFromFile();
		
	}

	static double GetTotalBalance() {
		double TotaleBalance = 0;
		vector<clsBankClient>vClients;
		vClients = clsBankClient::GetClientList();
		for (clsBankClient Client : vClients) {
			TotaleBalance += Client.AccountBalance;
		}
		return TotaleBalance;
	}

	void Deposit(double Amount) {
		_AccountBalance += Amount;
		Save();
	}
	void Withdraw (double Amount) {
		while (Amount > _AccountBalance) {

			cout << "\n\nWithdrw Amount is not available.";
			cout << "\n Your balance is: " << _AccountBalance << endl;
			cout << "\nPlease Choose Another Amount:";
			Amount = clsInputValidate::ReadFloatNumber();
		}
		_AccountBalance -= Amount;
		Save();
	}

	bool Transfer(double Amount,clsBankClient&DestenationClient,string UserName) {
		if (Amount > AccountBalance) {
			return false;
		}
		else
		{
			Withdraw(Amount);
			DestenationClient.Deposit(Amount);
			_RegisterLogInTransfer(Amount, DestenationClient,UserName);
			return true;
		}
	}

	static clsBankClient GetAddNewClient(string AccountNumber) {
		return clsBankClient(enMode::AddNew, "", "", "", "", AccountNumber, "", 0);
	}


	static vector<stLogTransferRecord>GetLogTransferList() {
		vector<stLogTransferRecord>vLogTransferRecord;
		fstream MyFile;
		MyFile.open("LogTransfer.txt", ios::in);
		if (MyFile.is_open()) {
			string Line;
			stLogTransferRecord LogTransferRecord;
			while (getline(MyFile, Line)) {
				LogTransferRecord = _ConvertTransferLineToRecord(Line);
				vLogTransferRecord.push_back(LogTransferRecord);
			}
			MyFile.close();
		}
		return vLogTransferRecord;
	}

	
};
