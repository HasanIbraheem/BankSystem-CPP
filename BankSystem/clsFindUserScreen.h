#pragma once
#include<iostream>
#include"clsUser.h"
#include"clsScreen.h"
#include"clsInputValidate.h"

using namespace std;

class clsFindUserScreen :protected clsScreen {
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
	static void FindUserScren() {
	
		_DrowScreenHeader("\tFind  user Menue.");
		string UserName = "";
		cout << "Please Enter User Name: ";
		UserName = clsInputValidate::ReadString();
		while (!clsUser::IsUserExist(UserName)) {
			cout << "\nUser Name Doesn't Exict Please Enter Another One : ";
			UserName = clsInputValidate::ReadString();
		}
		clsUser User = clsUser::Find(UserName);
		if (!User.IsEmpty()) {
			cout << "\nUser Found Successfully :)\n";
		}
		else {
			cout << "\nUser Was Not Found :(\n";
		}
		_PrintUser(User);
	}
};