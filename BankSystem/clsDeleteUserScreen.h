#pragma once
#include<iostream>
#include<iomanip>
#include"clsScreen.h"
#include"clsUser.h"
#include"clsInputValidate.h"

using namespace std;

class clsDeleteUserScreen :protected clsScreen {
private:
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
	static void DeleteUserScreen() {
		_DrowScreenHeader("\tDelete User Menue");
		string UserName = "";
		cout << "\n\nPlease enter User Name You want to delete : ";
		UserName = clsInputValidate::ReadString();
		while (!clsUser::IsUserExist(UserName)) {
			cout << "User Is Not Exict Please Choose another one: ";
			UserName = clsInputValidate::ReadString();
		}
		clsUser User1 = clsUser::Find(UserName);
		_PrintUser(User1);
		cout << "\n\nAre You sure You want To Delete This User? y/n";
		char answer='n';
		cin >> answer;
		if (answer == 'y' || answer == 'Y') {
			if (User1.Delete()) {
				cout << "\nUser Deleted Successfuly\n";
			}
			else
				cout << "\nError Faild To Delet User.";
		}
	}
};