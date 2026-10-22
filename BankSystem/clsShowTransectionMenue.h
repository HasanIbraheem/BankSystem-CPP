#pragma once
#include<iostream>
#include<iomanip>
#include"clsScreen.h"
#include"clsInputValidate.h"
#include"clsDepositScreen.h"
#include"clsWithdrawScreen.h"
#include"clsTotalBalanceScreen.h"
#include"clsUser.h"
#include"clsTransferScreen.h";
#include"clsLogTransfer.h"

using namespace std;

class clsShowTransectionMenue:protected clsScreen {
private:
    enum enTransectionMenueOption {
        eDeposite = 1, eWithdraw = 2, eTotalBalance = 3,
        eTransfer=4,eTransferLog=5 ,eMainMenue = 6 
    };

    static short _ReadTransectionMenueOption() {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
        short Choice = clsInputValidate::ReadShortNumberBetween(1, 6, "Please Enter a Number from 1 To 6");
        return Choice;
    }

    static void _GoToTransectionMenue() {
        cout << setw(37) << left << "" << "\n\tPress any key to go back to Transaction Menue...\n";
        system("pause>0");
        ShowTransectionMenue();
    }

    static void _ShowDepositeScreen()
    {
      //  cout << "\nDeposit Screen Will be here...\n";
        
        clsDepositScreen::ShowDepositClientScreen();

    }

    static void _ShowWithdrawScreen()
    {
         //cout << "\nWithdraw Screen Will be here...\n";
        clsWithdrawScreen::ShowWithdrawClientScreen();

    }

    static void _ShowTotalBalanceScreen()
    {
       // cout << "\nTotal Balance Screen Will be here...\n";
        clsTotalBalanceScreen::ShowClientBalance();

    }

    static void _ShowTransferScreen() {
        clsTransferScreen::ShowTransferScreen();
    }


    static void _ShowTransferLog() {
        clsLogTransfer::ShowClientTransferList();
    }
  

    static void _PerformTransectionMenueOption(enTransectionMenueOption TransectionMenueInfo) {
        switch (TransectionMenueInfo) {
        case enTransectionMenueOption::eDeposite: {
            system("cls");
            _ShowDepositeScreen();
            _GoToTransectionMenue();
            break;
        }
        case enTransectionMenueOption::eWithdraw: {
            system("cls");
            _ShowWithdrawScreen();
            _GoToTransectionMenue();
            break;
        }
        case enTransectionMenueOption::eTotalBalance:  {
            system("cls");
            _ShowTotalBalanceScreen();
            _GoToTransectionMenue();
            break;
        }
        case enTransectionMenueOption::eTransfer: {
            system("cls");
            _ShowTransferScreen();
            _GoToTransectionMenue();
            break;
        }
        case enTransectionMenueOption::eTransferLog: {
            system("cls");
            _ShowTransferLog();
            _GoToTransectionMenue();
            break;
        }
        case enTransectionMenueOption::eMainMenue:  {
            
        }
     
        }


    }


public:
    static void ShowTransectionMenue() {
        system("cls");

        if (!CheckAccessRights(clsUser::enPermessions::pTransactions)) {
            return;
        }

        _DrowScreenHeader("\t\tTransection Screen");



        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t\tTransection Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Deposit.\n";
        cout << setw(37) << left << "" << "\t[2] Withdraw.\n";
        cout << setw(37) << left << "" << "\t[3] Total Balance.\n";
        cout << setw(37) << left << "" << "\t[4] Transfer.\n";
        cout << setw(37) << left << "" << "\t[5] Transfer Log.\n";
        cout << setw(37) << left << "" << "\t[6] Main Menue.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerformTransectionMenueOption((enTransectionMenueOption)_ReadTransectionMenueOption());
    }


};