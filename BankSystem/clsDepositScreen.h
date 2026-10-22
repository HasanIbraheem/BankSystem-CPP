#pragma once
#include<iostream>
#include"clsBankClient.h"
#include"clsScreen.h"
#include"clsInputValidate.h"
#include"clsFindClientScreen.h"

using namespace std;

class clsDepositScreen :protected clsScreen {
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
	static void ShowDepositClientScreen() {
		_DrowScreenHeader("\tDeposit Screen");
		
		cout << "\n\nPlease Enter AccountNumber: ";
		string AccountNumber = _ReadAccountNumber();
		while (!clsBankClient::IsClientExist(AccountNumber)) {
			cout << "\n Account Number ["<<AccountNumber<<"] does not exist. Please enter another Account Number:";
			AccountNumber = _ReadAccountNumber();
		}
		clsBankClient Client = clsBankClient::Find(AccountNumber);
		_PrintClient(Client);

		float Amount;
		cout << "\nPlease enter the deposit amount ? ";
		Amount = clsInputValidate::ReadFloatNumber();

		cout << "\nAre you sure you want to preform this transection? y/n? ";

		char Answer = 'n';
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{

			Client.Deposit(Amount);
			cout << "\n\nAmount Deposit Succesfully ";
			cout << "\nNew balance is: " << Client.AccountBalance << endl;

		}
		else
			cout << "\nOperation was cancelled\n";
	}
};