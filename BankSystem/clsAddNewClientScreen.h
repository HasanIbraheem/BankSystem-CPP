#pragma once
#include<iostream>
#include<iomanip>
#include"clsScreen.h"
#include"clsBankClient.h"
#include"clsInputValidate.h"
#include"clsUser.h"
using namespace std;

class clsAddNewClientScreen :protected clsScreen {
private:
	static void _UpdateClientInfo(clsBankClient& Client) {
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
		cout << "\nLastName    : " <<Client. LastName;
		cout << "\nFull Name   : " << Client.FullName();
		cout << "\nEmail       : " << Client.Email;
		cout << "\nPhone       : " << Client.PhoneNumber;
		cout << "\nAccouNumber : " << Client.AccountNumber();
		cout << "\nPassword    : " << Client.PinCode;
		cout << "\nBalance     : " << Client.AccountBalance;
		cout << "\n___________________\n";

	}

public:
	static void AddNewClient() {
		
		if (!CheckAccessRights(clsUser::enPermessions::pAddNewClient)) {
			return;
		}

		_DrowScreenHeader("\tAdd New Client Menue");
		string AccountNumber = "";
		cout << "\n\nPlease Enter AccountNumber: ";
		AccountNumber = clsInputValidate::ReadString();
		while (clsBankClient::IsClientExist(AccountNumber)) {
			cout << "\nThe account already exist. Please enter another Account Number:";
			AccountNumber = clsInputValidate::ReadString();
		}
		clsBankClient AddClient = clsBankClient::GetAddNewClient(AccountNumber);


		_UpdateClientInfo(AddClient);


		clsBankClient::enSaveResults SaveResult = AddClient.Save();

		switch (SaveResult) {
		case clsBankClient::enSaveResults::svFaildEmptyObject: {
			cout << "\nThe Account is empty please chose another one \n ";
			break;
		}
		case clsBankClient::enSaveResults::svFailedAccountExist:
		{
			cout << "\nThe Account Number is Already Exist Please Chose Another One\n";
			break;
		}
		case clsBankClient::enSaveResults::svSucceeded:
			cout << "\n The client Added succefully \n";
			_PrintClient(AddClient);
		}
}

};