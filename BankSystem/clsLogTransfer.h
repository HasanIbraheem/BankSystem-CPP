#pragma once
#include<iostream>
#include"clsScreen.h"
#include"clsBankClient.h";
#include<iomanip>;
#include"clsDate.h"

using namespace std;

class clsLogTransfer :protected clsScreen {
private:
    static void PrintClientTransferLine(clsBankClient::stLogTransferRecord LogTransferRecord) {
        cout << setw(8) << left << "" << "| " << setw(20) << left << LogTransferRecord.DateTime;
        cout << "| " << setw(15) << left << LogTransferRecord.AccountNumber1;
        cout << "| " << setw(20) << left << LogTransferRecord.AccountNumber2;
        cout << "| " << setw(10) << left << LogTransferRecord.Amount;
        cout << "| " << setw(15) << left << LogTransferRecord.AccountBalance1;
        cout << "| " << setw(20) << left << LogTransferRecord.AccountBalance2;
        cout << "| " << setw(10) << left << LogTransferRecord.UserName;
    }

public:
    static void ShowClientTransferList() {
        if (!CheckAccessRights(clsUser::enPermessions::pTransactions)) {
            return;
        }
        vector<clsBankClient::stLogTransferRecord>vLogTransferRecord = clsBankClient::GetLogTransferList();
        string Titel = "\tClient Transfer List Screen";
        string Subtitel = "\t (" + to_string(vLogTransferRecord.size()) + ") Record(s).";
        _DrowScreenHeader(Titel, Subtitel);
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(20) << "Date/Time";
        cout << "| " << left << setw(15) << "Source Account";
        cout << "| " << left << setw(20) << "Destenation Account";
        cout << "| " << setw(10) << left << "Amount";
        cout << "| " << left << setw(15) << "Source Balance";
        cout << "| " << left << setw(20) << "Destenation Balance";
        cout << "| " << left << setw(10) << "User Name";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vLogTransferRecord.size() == 0) {
            cout << "\t\t\t\t No Client available in the system\n";
        }
        else
            for (clsBankClient::stLogTransferRecord Records : vLogTransferRecord) {
                PrintClientTransferLine(Records);
                cout << endl;
            }
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
    }
};