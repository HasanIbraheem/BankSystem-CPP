#pragma once
#include<iostream>
#include"clsScreen.h"
#include"clsBankClient.h"
#include<iomanip>
#include"clsUtil.h"

using namespace std;

class clsTotalBalanceScreen :protected clsScreen {
private:
    static void PrintClientRecordLine(clsBankClient Client) {
        cout << setw(8) << left << "" << "| " << setw(15) << left << Client.AccountNumber();
        cout << "| " << setw(20) << left << Client.FullName();
        cout << "| " << setw(12) << left << Client.AccountBalance;
    }

public:
    static void ShowClientBalance() {

        vector<clsBankClient>vClient = clsBankClient::GetClientList();
        string Titel = "\tClient Balance Screen";
        string Subtitel = "\t (" + to_string(vClient.size()) + ") Client(s).";
        _DrowScreenHeader(Titel, Subtitel);
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(15) << "Accout Number";
        cout << "| " << left << setw(20) << "Client Name";
        cout << "| " << left << setw(12) << "Balance";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
        double TotalBalance = 0;
        TotalBalance = clsBankClient::GetTotalBalance();
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
       
        cout << setw(8) << left << "" << "\n\t\t\t\t\tTotal AcountBalance = " << TotalBalance;
        cout << setw(8) << left << "" << "\n\t\t\t\t\t("<< clsUtil::NumberToText(TotalBalance)<<")";

    }
};