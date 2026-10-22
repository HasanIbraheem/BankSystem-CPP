#pragma once
#include<iostream>
#include"clsScreen.h"
#include"clsUser.h";
#include<iomanip>;
#include"clsDate.h"

using namespace std;

class clsLogInRegister:protected clsScreen {
private:
    static void PrintUserRegisterLine(clsUser::stLogInRegisterRecord LogInRegisterRecord) {
        cout << setw(8) << left << "" << "| " << setw(35) << left << LogInRegisterRecord.DateTime;
        cout << "| " << setw(20) << left << LogInRegisterRecord.UserName;
        cout << "| " << setw(20) << left << LogInRegisterRecord.Password;
        cout << "| " << setw(10) << left << LogInRegisterRecord.Permession;
    }

public:
    static void ShowUserRegisterList() {
        if (!CheckAccessRights(clsUser::enPermessions::pLogInRegister)) {
            return;
        }
        vector<clsUser::stLogInRegisterRecord>vLogInRegisterRecord = clsUser::GetLogInUserRegisterList();
        string Titel = "\tUser Registerd List Screen";
        string Subtitel = "\t (" + to_string(vLogInRegisterRecord.size()) + ") Record(s).";
        _DrowScreenHeader(Titel, Subtitel);
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(15) << "Date/Time";
        cout << "| " << left << setw(20) << "User Name";
        cout << "| " << left << setw(20) << "Password";
        cout << "| " << left << setw(10) << "Permession";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vLogInRegisterRecord.size() == 0) {
            cout << "\t\t\t\t No Users available in the system\n";
        }
        else
            for (clsUser::stLogInRegisterRecord Records : vLogInRegisterRecord) {
                PrintUserRegisterLine(Records);
                cout << endl;
            }
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
    }
};