#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include"clsPerson.h"
#include"clsString.h"
#include"clsDate.h"
#include"clsUtil.h"

using namespace std;

class clsUser :public clsPerson {
private:
	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
	enMode _Mode;
	string _UserName;
	string _Password;
	int _Permession;
	bool _MarkForDelete = false;
	string _EncryptionPassWord;
	struct stLogInRegisterRecord;

	static stLogInRegisterRecord _ConvertLogInRegisterLineToRecord(string Line, string Seperator = "#//#") {
		stLogInRegisterRecord LogInRegisterRecord;
		vector <string> LoginRegisterDataLine = clsString::Split(Line, Seperator);
		LogInRegisterRecord.DateTime = LoginRegisterDataLine[0];
		LogInRegisterRecord.UserName = LoginRegisterDataLine[1];
		LogInRegisterRecord.Password = clsUtil::DecryptText(LoginRegisterDataLine[2]);
 		LogInRegisterRecord.Permession = stoi(LoginRegisterDataLine[3]);
		return LogInRegisterRecord;
	}

	 string _PrepareLoginRecord(string Separater = "#//#") {
		string StRecord = "";
		StRecord += clsDate::GetSystemDateTimeString() + Separater;
		StRecord += UserName + Separater;
		StRecord +=clsUtil::EncryptText( Password) + Separater;
		StRecord += to_string(Permession);
		return StRecord;
	}

	static clsUser _ConvertLineToUserObject(string Line, string Seperater="#//#") {
		vector<string>vUser;
		vUser = clsString::Split(Line, Seperater);
		return clsUser(enMode::UpdateMode, vUser[0], vUser[1], vUser[2], vUser[3], vUser[4],clsUtil::DecryptText( vUser[5]), stoi(vUser[6]));
	}


	static string _ConvertUserObjectToLine(clsUser User, string Seperater = "#//#") {
		string setUser = "";
		setUser += User.FirstName + Seperater;
		setUser += User.LastName + Seperater;
		setUser += User.Email + Seperater;
		setUser += User.PhoneNumber + Seperater;
		setUser += User.UserName + Seperater;
		setUser += clsUtil::EncryptText( User.Password) + Seperater;
		setUser += to_string(User.Permession);
		return setUser;

	}



	static vector<clsUser>_LoadUserDataFromFile() {
		vector<clsUser>vUser;
		fstream MyFile;
		MyFile.open("Users.txt", ios::in);
		if (MyFile.is_open()) {
			string Line;
			while( getline(MyFile, Line)) {
				clsUser User=_ConvertLineToUserObject(Line);
				vUser.push_back(User);
			}
			MyFile.close();
		}
		return vUser;
	}

	static void _SaveUserObjectToFile(vector<clsUser>vUser) {
		
		
		fstream MyFile;
		MyFile.open("Users.txt", ios::out);
		string Line;
		if (MyFile.is_open()) {
			for (clsUser U : vUser) {
				if (U.MarkForDelete() == false) {
					Line = _ConvertUserObjectToLine(U, "#//#");
					MyFile << Line << endl;
				}
			}
			MyFile.close();
		}
	}

	static clsUser _GetEmptyUserObject() {
		return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	void _Update() {
		vector<clsUser>_vUser;
		_vUser = _LoadUserDataFromFile();
		for (clsUser &U : _vUser) {
			if (U.UserName == UserName) {
				U = *this;
				break;
			}
		}
		_SaveUserObjectToFile(_vUser);
	}

	void _AddDataLineToFile(string stDataLine) {
		fstream MyFile;


		MyFile.open("Users.txt", ios::out | ios::app);
		if (MyFile.is_open()) {
			MyFile << stDataLine << endl;
			MyFile.close();
		}
	}

	void _AddNew() {
		_AddDataLineToFile(_ConvertUserObjectToLine(*this));
	}

	static string EnctyptedPassword(string Password)
	{
		return clsUtil::EncryptText(Password);
	}

public:

	enum enPermessions{eAll=-1,pListClients=1,pAddNewClient=2,pDeleteClient=4,
		pUpdateClients=8,pFindClient=16,pTransactions=32,pManageUsers=64,pLogInRegister=128,pCurrencyExchange=256};

	struct stLogInRegisterRecord {
		string DateTime;
		string UserName;
		string Password;
		int Permession;
	};



	clsUser(enMode Mode,string FirstName,string LastName,string Email,string PhoneNumber, string UserName, string Password, int Permession) :
		clsPerson(FirstName, LastName, Email, PhoneNumber) {
		_Mode =Mode;
		_UserName = UserName;
		_Password = Password;
		_Permession = Permession;
	}

	bool IsEmpty() {
		return(_Mode==enMode::EmptyMode);
	}

	bool MarkForDelete() {
		return _MarkForDelete;
	}

	void SetUserName(string UserName) {
		_UserName = UserName;
	}

	string GetUserName() {
		return _UserName;
	}

	__declspec(property(get = GetUserName, put = SetUserName))string UserName;

	void SetPassword(string Password) {
		_Password = Password;
	}

	string GetPassword() {
		return _Password;
	}

	__declspec(property(get = GetPassword, put = SetPassword))string Password;

	void SetPermession(int Permession) {
		_Permession =Permession;
	}

	int GetPermession() {
		return _Permession;
	}

	__declspec(property(get = GetPermession, put = SetPermession))int Permession;

	static clsUser Find(string UserName) {
		fstream MyFile;
		MyFile.open("Users.txt", ios::in);
		if (MyFile.is_open()) {
			string Line;
			while (getline(MyFile, Line)) {
				clsUser User= _ConvertLineToUserObject(Line);
				if (User.UserName == UserName) {
					MyFile.close();
					return User;
				}
				
			}
			MyFile.close();
		}
		return _GetEmptyUserObject();
	}

	static clsUser Find(string UserName,string Password) {
		fstream MyFile;
		MyFile.open("Users.txt", ios::in);
		if (MyFile.is_open()) {
			string Line;
			while (getline(MyFile, Line)) {
				clsUser User = _ConvertLineToUserObject(Line);
				if (User.UserName == UserName && User.Password == Password) {
					MyFile.close();
					return User;
				}

			}
			MyFile.close();
		}
		return _GetEmptyUserObject();
	}

	bool Delete() {
		vector<clsUser>_vUser;
		_vUser = _LoadUserDataFromFile();
		for (clsUser &U : _vUser) {
			if (U.UserName == UserName) {
			    U._MarkForDelete = true;
				break;
			}
			
		}
		_SaveUserObjectToFile(_vUser);
		*this = _GetEmptyUserObject();
		return true;
	}

	static vector<clsUser>GetUserList() {
		return _LoadUserDataFromFile();
	}

	

	enum enSaveResult{svFailedEmptyObject=0,svSuccess=1,svFailedUserExist=2};

	enSaveResult Save() {
		switch (_Mode) {
		case enMode::EmptyMode: {
			if (IsEmpty()) {
				return enSaveResult::svFailedEmptyObject;

			}
		}
		case enMode::UpdateMode:
		{
			_Update();
			return enSaveResult::svSuccess;
			break;
		}
		case enMode::AddNewMode:
		{
			if (IsUserExist(_UserName))
				return enSaveResult::svFailedUserExist;
			else
			{
				_AddNew();
				_Mode = enMode::UpdateMode;
				return enSaveResult::svSuccess;
			} 
			break;
		}
		
		}
	}
	static bool IsUserExist(string UserName) {
		clsUser User = clsUser::Find(UserName);
		return (!User.IsEmpty());
	}

	static clsUser GetAddNewUser(string UserName) {
		return clsUser(enMode::AddNewMode, "", "", "", "", UserName, "", 0);
	}

	bool CheckAccessPermession(enPermessions Permession) {
		if (this->Permession == enPermessions::eAll)
			return true;
		if ((Permession & this->Permession) == Permession) {
			return true;
		}
		else
			return false;
		
	}

	void RegisterLogIn() {
		fstream MyFile;
		string Data = _PrepareLoginRecord();
		MyFile.open("LogInRegester.txt", ios::out | ios::app);
		if (MyFile.is_open()) {
			MyFile << Data << endl;

			MyFile.close();
		}
	}

	static vector<stLogInRegisterRecord>GetLogInUserRegisterList() {
		vector<stLogInRegisterRecord>vLogInRegisterRecord;
		fstream MyFile;
		MyFile.open("LogInRegester.txt", ios::in);
		if (MyFile.is_open()) {
			string Line;
			stLogInRegisterRecord LogInRegisterRecord;
			while (getline(MyFile, Line)) {
				LogInRegisterRecord = _ConvertLogInRegisterLineToRecord(Line);
				vLogInRegisterRecord.push_back(LogInRegisterRecord);
			}
			MyFile.close();
		}
		return vLogInRegisterRecord;
	}
};