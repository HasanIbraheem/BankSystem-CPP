#pragma once
#include<iostream>
#include"clsScreen.h"
#include"clsCurrencies.h";
#include<iomanip>;

using namespace std;

class clsUserListCurrenciesScreen :protected clsScreen {
private:
    static void PrintCurrencyRecordLine(clsCurrencies Currency) {
        cout << setw(8) << left << "" << "| " << setw(30) << left << Currency.CountryName();
        cout << "| " << setw(8) << left << Currency.CurrencyCode();
        cout << "| " << setw(45) << left << Currency.CurrencyName();
        cout << "| " << setw(10) << left << Currency.Rate();
    }

public:
    static void ShowCurrenciesList() {
        vector<clsCurrencies>vCurrency = clsCurrencies::GetCurrenciesList();
        string Titel = "\tCurrencies List Screen";
        string Subtitel = "\t (" + to_string(vCurrency.size()) + ") Currency(ies).";
        _DrowScreenHeader(Titel, Subtitel);
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(30) << "Country Name";
        cout << "| " << left << setw(8) << "Currency Code";
        cout << "| " << left << setw(45) << "Currency Name";
        cout << "| " << left << setw(10) << "Rate";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vCurrency.size() == 0) {
            cout << "\t\t\t\t No Currencies available in the system\n";
        }
        else
            for (clsCurrencies Currency : vCurrency) {
                PrintCurrencyRecordLine(Currency);
                cout << endl;
            }
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
    }
};
