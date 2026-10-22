#pragma once
#include<iostream>
#include<iomanip>
#include"clsScreen.h"
#include"clsInputValidate.h"
#include"clsUser.h"
#include"clsListCurrenciesScreen.h"
#include"clsFindCurrencyScreen.h"
#include"clsUpdateCurrencyRateScreen.h"
#include"clsCurrenciesCalculaterScreen.h"

using namespace std;

class clsCurrencyExchangeMenue :protected clsScreen {
private:
    enum enCurrencyExchangeMenueOption {
        eListCurrencies = 1, eFindCurrency = 2, eUpdateRate = 3,
        eCalculateCurrency = 4, eMainMenue = 5
    };

    static short _ReadCurrencyExchangeMenueOption() {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 5]? ";
        short Choice = clsInputValidate::ReadShortNumberBetween(1, 5, "Please Enter a Number from 1 To 5");
        return Choice;
    }

    static void _GoToCurrencyExchangeMenue() {
        cout << setw(37) << left << "" << "\n\tPress any key to go back to Currency Exchange Menue...\n";
        system("pause>0");
        ShowCurrencyExchangeMenue();
    }

    static void _ShowListCurrencyScreen()
    {
         //cout << "\List Currency Screen Will be here...\n";
        clsUserListCurrenciesScreen::ShowCurrenciesList();

    }

    static void _ShowFindCurrencyScreen()
    {
       // cout << "\nFind Currency Screen Will be here...\n";
        clsFindCurrencyScreen::FindCurrencyScreen();
    }

    static void _ShowUpdateRateScreen()
    {
        //cout << "\Update Currency Screen Will be here...\n";
        clsUpdateCurrencyRateScreen::UpdateCurrency();

    }

    static void _ShowCalculateCurrencyScreen() {
        clsCurrenciesExchangeScreen::CurrencyExchangeScreen();
    }


    static void _PerformCurrencyExchangeMenueOption(enCurrencyExchangeMenueOption CurrencyExchangeMenueInfo) {
        switch (CurrencyExchangeMenueInfo) {
        case enCurrencyExchangeMenueOption::eListCurrencies: {
            system("cls");
            _ShowListCurrencyScreen();
            _GoToCurrencyExchangeMenue();
            break;
        }
        case enCurrencyExchangeMenueOption::eFindCurrency: {
            system("cls");
            _ShowFindCurrencyScreen();
            _GoToCurrencyExchangeMenue();
            break;
        }
        case enCurrencyExchangeMenueOption::eUpdateRate: {
            system("cls");
            _ShowUpdateRateScreen();
            _GoToCurrencyExchangeMenue();
            break;
        }
        case enCurrencyExchangeMenueOption::eCalculateCurrency: {
            system("cls");
            _ShowCalculateCurrencyScreen();
            _GoToCurrencyExchangeMenue();
            break;
        }
        case enCurrencyExchangeMenueOption::eMainMenue: {

        }

        }


    }


public:
    static void ShowCurrencyExchangeMenue() {
        if (!CheckAccessRights(clsUser::enPermessions::pCurrencyExchange)) {
            return;
        }
        system("cls");

        if (!CheckAccessRights(clsUser::enPermessions::pTransactions)) {
            return;
        }

        _DrowScreenHeader("\t\tCurrency Exchange Screen");



        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t\tCurrency Exchange Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] List Currencies.\n";
        cout << setw(37) << left << "" << "\t[2] Find Currency.\n";
        cout << setw(37) << left << "" << "\t[3] Update Rate.\n";
        cout << setw(37) << left << "" << "\t[4] Calculate Currency.\n";
        cout << setw(37) << left << "" << "\t[5] Main Menue.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerformCurrencyExchangeMenueOption((enCurrencyExchangeMenueOption)_ReadCurrencyExchangeMenueOption());
    }


};