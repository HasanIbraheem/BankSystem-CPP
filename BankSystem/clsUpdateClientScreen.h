#pragma once
#include<iostream>
#include<iomanip>
#include"clsBankClient.h"
#include"clsScreen.h"
#include"clsInputValidate.h"
#include"clsUser.h"

using namespace std;

class clsUpdateClientScreen :protected clsScreen {
private:
	static void ReadClientInfo(clsBankClient& Client) {
		cout << "\nClient Information:\n";
		cout << "-----------------------\n\n";
		cout << "\nEnter FirstName: ";
		Client.FirstName = clsInputValidate::ReadString();
		cout << "\nEnter LastName: ";
		Client.LastName = clsInputValidate::ReadString();
		cout << "\nEnter Email : ";
		Client.Email = clsInputValidate::ReadString();
		cout << "\nEnter PhoneNumber : ";
		Client.PhoneNumber = clsInputValidate::ReadString();
		cout << "\nEnter PinCode : ";
		Client.PinCode = clsInputValidate::ReadString();
		cout << "\nEnter AccountBalance : ";
		Client.AccountBalance = clsInputValidate::ReadFloatNumber();
	}
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
	static void ShowUpdateClientScreen() {

		if (!CheckAccessRights(clsUser::enPermessions::pUpdateClients)) {
			return;
		}

		_DrowScreenHeader("\tUpdate Client Screen");
		string AccountNumber = "";
		cout << "\n\nPlease Enter AccountNumber: ";
		AccountNumber = clsInputValidate::ReadString();
		while (!clsBankClient::IsClientExist(AccountNumber)) {
			cout << "\nThe account does not exist. Please enter another Account Number:";
			AccountNumber = clsInputValidate::ReadString();
		}
		clsBankClient Client = clsBankClient::Find(AccountNumber);
		_PrintClient(Client);

		cout << "\nAre you sure you want to update this client y/n? ";

		char Answer = 'n';
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{

			cout << "\n\nUpdate Client Info:";
			cout << "\n____________________\n";


			ReadClientInfo(Client);

			clsBankClient::enSaveResults SaveResult;

			SaveResult = Client.Save();

			switch (SaveResult)
			{
			case  clsBankClient::enSaveResults::svSucceeded:
			{
				cout << "\nAccount Updated Successfully :-)\n";

				_PrintClient(Client);
				break;
			}
			case clsBankClient::enSaveResults::svFaildEmptyObject:
			{
				cout << "\nError account was not saved because it's Empty";
				break;

			}
			}
		}
	}

};