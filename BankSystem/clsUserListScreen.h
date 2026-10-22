#pragma once
#include<iostream>
#include"clsScreen.h"
#include"clsUser.h";
#include<iomanip>;

using namespace std;

class clsUserListScreen :protected clsScreen {
private:
    static void PrintUserRecordLine(clsUser User) {
        cout << setw(8) << left << "" << "| " << setw(15) << left << User.UserName;
        cout << "| " << setw(20) << left << User.FullName();
        cout << "| " << setw(12) << left << User.PhoneNumber;
        cout << "| " << setw(20) << left << User.Email;
        cout << "| " << setw(10) << left << User.Password;
        cout << "| " << setw(12) << left << User.Permession;
    }

public:
    static void ShowUserList() {
        vector<clsUser>vUser = clsUser::GetUserList();
        string Titel = "\tUser List Screen";
        string Subtitel = "\t (" + to_string(vUser.size()) + ") User(s).";
        _DrowScreenHeader(Titel, Subtitel);
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(15) << "User Name";
        cout << "| " << left << setw(20) << "Full Name";
        cout << "| " << left << setw(12) << "Phone";
        cout << "| " << left << setw(20) << "Email";
        cout << "| " << left << setw(10) << "Password";
        cout << "| " << left << setw(12) << "Permession";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vUser.size() == 0) {
            cout << "\t\t\t\t No Users available in the system\n";
        }
        else
            for (clsUser Clients : vUser) {
                PrintUserRecordLine(Clients);
                cout << endl;
            }
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
    }
};