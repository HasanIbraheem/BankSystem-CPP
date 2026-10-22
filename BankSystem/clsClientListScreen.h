#pragma once
#include<iostream>
#include"clsScreen.h"
#include"clsBankClient.h";
#include<iomanip>;
#include"clsUser.h"

using namespace std;

class clsClientListScreen :protected clsScreen {
private:
	static void PrintClientRecordLine(clsBankClient Client) {
        cout << setw(8) << left << "" << "| " << setw(15) << left << Client.AccountNumber();
        cout << "| " << setw(20) << left << Client.FullName();
        cout << "| " << setw(12) << left << Client.PhoneNumber;
        cout << "| " << setw(20) << left << Client.Email;
        cout << "| " << setw(10) << left << Client.PinCode;
        cout << "| " << setw(12) << left << Client.AccountBalance;
	}

public:
    static void ShowClientList() {

        if (!CheckAccessRights(clsUser::enPermessions::pListClients)) {
            return;
        }

        vector<clsBankClient>vClient = clsBankClient::GetClientList();
        string Titel = "\tClient List Screen";
        string Subtitel = "\t (" + to_string(vClient.size()) + ") Client(s).";
        _DrowScreenHeader(Titel, Subtitel);
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(15) << "Accout Number";
        cout << "| " << left << setw(20) << "Client Name";
        cout << "| " << left << setw(12) << "Phone";
        cout << "| " << left << setw(20) << "Email";
        cout << "| " << left << setw(10) << "Pin Code";
        cout << "| " << left << setw(12) << "Balance";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vClient.size() == 0) {
            cout << "\t\t\t\t No client available in the system\n";
        }
        else
            for (clsBankClient Clients : vClient) {
                PrintClientRecordLine(Clients);
                cout << endl;
            }
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
    }
};