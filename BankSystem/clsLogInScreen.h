#pragma once
#include<iostream>
#include"clsUser.h"
#include"clsScreen.h"
#include"Global.h"
#include"clsMainScreen.h"
#include"clsDate.h"

class clsLogInScreen :protected clsScreen {
private:
	static bool _Login() {
		bool LogInFaild = false;
		int LoginFaildCounter = 0;
		do {
			string UserName, Password;
			if (LogInFaild) {
				LoginFaildCounter++;
				cout << "\nUncorrect UserName/Password.\n";
				cout << "\n\nYou Have " << (3 - LoginFaildCounter) << " Trail(s) Left";
			}
			if (LoginFaildCounter == 3) {
				cout << "\n\nYou are Locked After 3 Faild Trails\n";
				return false;
			}
			cout << "\nPlease Enter User Name: ";
			cin >> UserName;
			cout << "\nPlease Enter Password: ";
			cin >> Password;
			CurrentUser = clsUser::Find(UserName, Password);
			LogInFaild = CurrentUser.IsEmpty();
		} while (LogInFaild);
		CurrentUser.RegisterLogIn();
		clsMainScreen::ShowMainMenue();
		return true;
	}
public:
	static bool ShowLogInScreen() {
		system("cls");
		_DrowScreenHeader("\tLogin Screen.");
		return _Login();
		
	}
};