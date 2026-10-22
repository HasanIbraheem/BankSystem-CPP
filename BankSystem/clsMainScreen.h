#pragma once
#include<iostream>
#include<iomanip>
#include"clsScreen.h"
#include"clsInputValidate.h";
#include"clsClientListScreen.h"
#include"clsAddNewClientScreen.h"
#include"clsDeleteClientScreen.h"
#include"clsUpdateClientScreen.h"
#include"clsFindClientScreen.h"
#include"clsShowTransectionMenue.h"
#include"clsManageUserScreen.h"
#include"Global.h"
#include"clsUser.h"
#include"clsLogInRegister.h"
#include"clsCurrencyExchangeMenue.h"

using namespace std;

class clsMainScreen :protected clsScreen {
private:
    enum enMainMenueOption{
        eListClients = 1, eAddNewClient = 2, eDeleteClient = 3,
        eUpdateClient = 4, eFindClient = 5, eShowTransactionsMenue = 6,
        eManageUsers = 7,eRegistredUser=8,eCurrencyExchange=9,eExit = 10};

    static short _ReadMainMenueOption() {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 10]? ";
        short Choice = clsInputValidate::ReadShortNumberBetween(1, 10, "Please Enter a Number from 1 To 10");
        return Choice;
    }

    static void _GoToMainMenue() {
        cout << setw(37) << left << "" << "\n\tPress any key to go back to Main Menue...\n";
        system("pause>0");
        ShowMainMenue();
    }

    static void _ShowAllClientsScreen()
    {
       // cout << "\nClient List Screen Will be here...\n";
        clsClientListScreen::ShowClientList();


    }

    static void _ShowAddNewClientsScreen()
    {
       // cout << "\nAdd New Client Screen Will be here...\n";
        clsAddNewClientScreen::AddNewClient();

    }

    static void _ShowDeleteClientScreen()
    {
        //cout << "\nDelete Client Screen Will be here...\n";
        clsDeleteClientScreen::ShowDeletClientScreen();

    }

    static void _ShowUpdateClientScreen()
    {
      //  cout << "\nUpdate Client Screen Will be here...\n";
        clsUpdateClientScreen::ShowUpdateClientScreen();

    }

    static void _ShowFindClientScreen()
    {
       // cout << "\nFind Client Screen Will be here...\n";
        clsFindClientScreen::ShowFindClientScreen();
    }

    static void _ShowTransactionsMenue()
    {
       // cout << "\nTransactions Menue Will be here...\n";
        clsShowTransectionMenue::ShowTransectionMenue();

    }

    static void _ShowManageUsersMenue()
    {
        //cout << "\nUsers Menue Will be here...\n";
        clsManageUserScreenMenue::ShowManageUserMenue();
    }

    //static void _ShowEndScreen()
    //{
    //    cout << "\nEnd Screen Will be here...\n";

    //}

    static void _ShowRegisterUserScreen() {
        clsLogInRegister::ShowUserRegisterList();
    }

    static void _ShowCurrencyExchangeScreen() {
        clsCurrencyExchangeMenue::ShowCurrencyExchangeMenue();
    }

    static void _LogOut() {
        CurrentUser = clsUser::Find("", "");
    }

    static void _PerformMainMenueOption(enMainMenueOption NainMenueInfo) {
        switch (NainMenueInfo) {
        case enMainMenueOption::eListClients: {
            system("cls");
            _ShowAllClientsScreen();
            _GoToMainMenue();
            break;
        }
        case enMainMenueOption::eAddNewClient: {
            system("cls");
            _ShowAddNewClientsScreen();
            _GoToMainMenue();
            break;
        }
        case enMainMenueOption::eDeleteClient: {
            system("cls");
            _ShowDeleteClientScreen();
            _GoToMainMenue();
            break;
        }
        case enMainMenueOption::eUpdateClient: {
            system("cls");
            _ShowUpdateClientScreen();
            _GoToMainMenue();
            break;
        }
        case enMainMenueOption::eFindClient: {
            system("cls");
            _ShowFindClientScreen();
            _GoToMainMenue();
            break;
        }

        case enMainMenueOption::eShowTransactionsMenue: {
            system("cls");
            _ShowTransactionsMenue();
            _GoToMainMenue();
            break;
        }
        case enMainMenueOption::eManageUsers: {
            system("cls");
            _ShowManageUsersMenue();
            _GoToMainMenue();
            break;
        }
     

        case enMainMenueOption::eRegistredUser: {
            system("cls");
            _ShowRegisterUserScreen();
            _GoToMainMenue();
            break;
        }
        case enMainMenueOption::eCurrencyExchange: {
            system("cls");
            _ShowCurrencyExchangeScreen();
            _GoToMainMenue();
            break;
        }
        case enMainMenueOption::eExit: {
            system("cls");
            //_ShowEndScreen();
            _LogOut();

            break;
        }
        }
        

    }


public:
	static void ShowMainMenue() {
        system("cls");

		_DrowScreenHeader("\t\tMain Screen");
       
       

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t\tMain Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Show Client List.\n";
        cout << setw(37) << left << "" << "\t[2] Add New Client.\n";
        cout << setw(37) << left << "" << "\t[3] Delete Client.\n";
        cout << setw(37) << left << "" << "\t[4] Update Client Info.\n";
        cout << setw(37) << left << "" << "\t[5] Find Client.\n";
        cout << setw(37) << left << "" << "\t[6] Transactions.\n";
        cout << setw(37) << left << "" << "\t[7] Manage Users.\n";
        cout << setw(37) << left << "" << "\t[8] Login Register.\n";
        cout << setw(37) << left << "" << "\t[9] Currency Exchange.\n";
        cout << setw(37) << left << "" << "\t[10] Logout.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerformMainMenueOption((enMainMenueOption)_ReadMainMenueOption());
	}

  
};