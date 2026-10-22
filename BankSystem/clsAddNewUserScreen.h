#pragma once
#include<iostream>
#include<iomanip>
#include"clsUser.h"
#include"clsScreen.h"
#include"clsInputValidate.h"

using namespace std;

class clsAddNewUserScreen :protected clsScreen {
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
	static void ShowAddNewUser() {
		_DrowScreenHeader("\tAdd New User Menue ");
		string UserName = "";
		cout << "\n\nPlease Enter User Name: ";
		UserName = clsInputValidate::ReadString();
		while (clsUser::IsUserExist(UserName)) {
			cout << "\nUser Is Alreadey Exict Please Enter Another User Name : \n";
			UserName = clsInputValidate::ReadString();
		}
		clsUser AddNewUser = clsUser::GetAddNewUser(UserName);
		_ReadUserInfo(AddNewUser);
		
		clsUser::enSaveResult SaveResult = AddNewUser.Save();
		switch (SaveResult) {
		case clsUser::enSaveResult::svFailedEmptyObject: {
			cout << "\nThe User Is Empty Please Choose Another One\n";
			break;
		}
		case clsUser::enSaveResult::svFailedUserExist: {
			cout << "\nThe User Is Already Exict Please Choose Another One?\n";
			break;
		}
		case clsUser::enSaveResult::svSuccess: {
			cout << "\nUser Added Succefully\n";
			_PrintUser(AddNewUser);
		}
		}
	}
};

