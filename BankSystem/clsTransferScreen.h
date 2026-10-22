#pragma once
#include<iostream>
#include"clsBankClient.h"
#include"clsScreen.h"
#include"clsInputValidate.h"
#include"clsFindClientScreen.h"

using namespace std;

class clsTransferScreen :protected clsScreen {
private:
	static void _PrintClient(clsBankClient Client) {
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFull Name   : " << Client.FullName();
		cout << "\nAccouNumber : " << Client.AccountNumber();
		cout << "\nBalance     : " << Client.AccountBalance;
		cout << "\n___________________\n";

	}
	static string _ReadAccountNumber() {
		string AccountNumber = "";
		cout << "\n\nPlease Enter AccountNumber You Want To transfer Money From: ";
		AccountNumber = clsInputValidate::ReadString();
		while (!clsBankClient::IsClientExist(AccountNumber)) {
			cout << "\n Account Number [" << AccountNumber << "] does not exist. Please enter another Account Number:";
			AccountNumber = clsInputValidate::ReadString();
		}
		return AccountNumber;
	}

	static double _ReadAmount(clsBankClient SourceClient) {
		double Amount ;
		cout << "\nEnter Transfer Amount? ";
		Amount = clsInputValidate::ReadDblNumber();
		while (Amount > SourceClient.AccountBalance) {
			cout << "\nAmount Exceeds the available Balance, Enter another Amount ? ";
			Amount = clsInputValidate::ReadDblNumber();
		}
		return Amount;

	}

public:
	static void ShowTransferScreen() {
		_DrowScreenHeader("\tTransfer Screen");

		
		string AccountNumber = _ReadAccountNumber();
		
		clsBankClient SourceClient = clsBankClient::Find(AccountNumber);
		_PrintClient(SourceClient);

		cout << "\n\nPlease Enter AccountNumber You Want To transfer Money To: ";
		AccountNumber = clsInputValidate::ReadString();
		
		clsBankClient DestenationClient = clsBankClient::Find(AccountNumber);
		_PrintClient(DestenationClient);

		double Amount;
		
		Amount = _ReadAmount(SourceClient);
		cout << "\nAre you sure you want to perform this operation? y/n? ";
		char Answer = 'n';
		cin >> Answer;
		if (Answer == 'Y' || Answer == 'y') {
			if (SourceClient.Transfer(Amount, DestenationClient,CurrentUser.UserName)) {
				cout << "\nTransfer done successfully\n";
			}
			else
			{
				cout << "\nTransfer Faild \n";
			}

		}
		_PrintClient(SourceClient);
		_PrintClient(DestenationClient);
	}

};