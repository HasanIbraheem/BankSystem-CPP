#pragma once
#include<iostream>
#include"clsBankClient.h"
#include"clsScreen.h"
#include"clsInputValidate.h"
#include"clsFindClientScreen.h"

using namespace std;

class clsWithdrawScreen :protected clsScreen {
private:
	static void _PrintClient(clsBankClient Client) {
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << Client.FirstName;
		cout << "\nLastName    : " << Client.LastName;
		cout << "\nFull Name   : " << Client.FullName();
		cout << "\nEmail       : " << Client.Email;
		cout << "\nPhone       : " << Client.PhoneNumber;
		cout << "\nAccouNumber : " << Client.AccountNumber();
		cout << "\nPassword    : " << Client.PinCode;
		cout << "\nBalance     : " << Client.AccountBalance;
		cout << "\n___________________\n";

	}
	static string _ReadAccountNumber() {
		string AccountNumber = "";
		AccountNumber = clsInputValidate::ReadString();
		return AccountNumber;
	}
public:
	static void ShowWithdrawClientScreen() {
		_DrowScreenHeader("\tWithdraw Screen");

		cout << "\n\nPlease Enter AccountNumber: ";
		string AccountNumber = _ReadAccountNumber();
		while (!clsBankClient::IsClientExist(AccountNumber)) {
			cout << "\n Account Number [" << AccountNumber << "] does not exist. Please enter another Account Number:";
			AccountNumber = _ReadAccountNumber();
		}
		clsBankClient Client = clsBankClient::Find(AccountNumber);
		_PrintClient(Client);

		float Amount;
		cout << "\nPlease enter the withdrwa amount ? ";
		Amount = clsInputValidate::ReadFloatNumber();
		
		cout << "\nAre you sure you want to preform this transection? y/n? ";

		char Answer = 'n';
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{
			Client.Withdraw(Amount);
			cout << "\nThe Amount was deducted succefully .\n";
			cout << "Your New Balance is: " << Client.AccountBalance;
		}
		else
			cout << "\nOperation was cancelled\n";
	}
};