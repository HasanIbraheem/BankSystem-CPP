#pragma once
#include<iostream>
#include<iomanip>
#include"clsScreen.h"
#include"clsBankClient.h"
#include"clsInputValidate.h"
#include"clsUser.h"

using namespace std;

class clsDeleteClientScreen :protected clsScreen {
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

public:
	static void ShowDeletClientScreen() {

		if (!CheckAccessRights(clsUser::enPermessions::pDeleteClient)) {
			return;
		}

		_DrowScreenHeader("\tDelet client menue ");
		string AccountNumber = "";
		cout << "\n\nPlease Enter AccountNumber: ";
		AccountNumber = clsInputValidate::ReadString();
		while (!clsBankClient::IsClientExist(AccountNumber)) {
			cout << "\nThe account does not exist. Please enter another Account Number:";
			AccountNumber = clsInputValidate::ReadString();
		}
		clsBankClient Client = clsBankClient::Find(AccountNumber);
		_PrintClient(Client);

		cout << "Are you sure you want to delete this account number :y/n\n";
		char answer = 'n';
		cin >> answer;
		if (answer == 'y' || answer == 'Y') {
			if (Client.Delete()) {
				cout << "\nClient Deleted Successfuly\n";
				_PrintClient(Client);
			}
			else
				cout << "\nError Faild to Delete Client\n";
		}

}
	
};