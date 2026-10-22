#pragma once
#include<iostream>
#include<iomanip>
#include"clsScreen.h"
#include"clsUser.h"
#include"clsInputValidate.h"

using namespace std;

class clsUpdateUserScreen :protected clsScreen {
private:
	static int _ReadPermessionToSet() {
		int Permession = 0;
		char Answer = 'n';
		cout << "Do You Want To Give User Full Access ? (Y/N) ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y') {
			return -1;
		}
		cout << "\nDo You Want To Give Permessin TO : \n";
		cout << "\nShow Client List? (y/n) ";
		cin >> Answer;
		if (Answer == 'Y' || Answer == 'y') {
			Permession += clsUser::enPermessions::pListClients;
		}
		cout << "\nAdd A New Client ? (y/n) ";
		cin >> Answer;
		if (Answer == 'Y' || Answer == 'y') {
			Permession += clsUser::enPermessions::pAddNewClient;
		}
		cout << "\nDelete Client? (Y/N) ";
		cin >> Answer;
		if (Answer == 'Y' || Answer == 'y') {
			Permession += clsUser::enPermessions::pDeleteClient;
		}
		cout << "\nUpdate Client ? (Y/N) ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y') {
			Permession += clsUser::enPermessions::pUpdateClients;
		}
		cout << "\nFind Client? (Y/N)";
		cin >> Answer;
		if (Answer == 'Y' || Answer == 'y') {
			Permession += clsUser::enPermessions::pFindClient;
		}
		cout << "\nTransaction? (Y/N)";
		cin >> Answer;
		if (Answer == 'Y' || Answer == 'y') {
			Permession += clsUser::enPermessions::pTransactions;
		}
		cout << "\nManage Users ? (Y/N)";
		cin >> Answer;
		if (Answer == 'Y' || Answer == 'y') {
			Permession += clsUser::enPermessions::pManageUsers;
		}
		cout << "\nShow LogIn Register ? (Y/N)";
		cin >> Answer;
		if (Answer == 'Y' || Answer == 'y') {
			Permession += clsUser::enPermessions::pLogInRegister;
		}
		return Permession;

	}

	static void _ReadUserInfo(clsUser& User) {
		cout << "\nUser Information: ";
		cout << "\n----------------------\n";
		cout << "\nFirstName: ";
		User.FirstName = clsInputValidate::ReadString();
		cout << "\nLastName: ";
		User.LastName = clsInputValidate::ReadString();
		cout << "\nEmail: ";
		User.Email = clsInputValidate::ReadString();
		cout << "\nPhoneNumber: ";
		User.PhoneNumber = clsInputValidate::ReadString();
		cout << "\nPassword: ";
		User.Password = clsInputValidate::ReadString();
		cout << "\nPermession: ";
		User.Permession = _ReadPermessionToSet();

	}
	static void _PrintUser(clsUser User) {
		cout << "\nUser Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << User.FirstName;
		cout << "\nLastName    : " << User.LastName;
		cout << "\nFull Name   : " << User.FullName();
		cout << "\nEmail       : " << User.Email;
		cout << "\nPhone       : " << User.PhoneNumber;
		cout << "\nUserName    : " << User.UserName;
		cout << "\nPassword    : " << User.Password;
		cout << "\nPermession  : " << User.Permession;
		cout << "\n___________________\n";

	}
public:
	static void UpdateUserInfo() {
		_DrowScreenHeader("\tUpdate User Menue.");
		string UserName = "";
		cout << "Please Enter UsernName : ";
		UserName = clsInputValidate::ReadString();
		while (!clsUser::IsUserExist(UserName)) {
			cout << "\nUser Is Not Exict Please Enter A Deferent User Name: ";
			UserName = clsInputValidate::ReadString();
		}
		clsUser User = clsUser::Find(UserName);
		_PrintUser(User);
		cout << "\nDo You Want To Update User Info? y/n";
		char Answer = 'n';
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y') {
			cout << "\n\nUpdate User Info:\n";
			cout << "--------------------------\n";
			_ReadUserInfo(User);
			clsUser::enSaveResult SaveResults = User.Save();
			switch (SaveResults) {
			case clsUser::enSaveResult::svSuccess: {
				cout << "\nUser Updated Successfully\n";
				_PrintUser(User);
				break;
			}
			case clsUser::enSaveResult::svFailedEmptyObject:
				cout << "\nFaild Empty User\n";
				break;
			}
		}
	}
};