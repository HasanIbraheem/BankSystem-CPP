#pragma once
#include<iostream>
#include<iomanip>
#include"clsScreen.h"
#include"clsCurrencies.h"
#include"clsInputValidate.h"
using namespace std;

class clsFindCurrencyScreen :protected clsScreen {
private:
	static void PrintCurrency(clsCurrencies Currency) {
		cout << "\nCurrency Card:\n";
		cout << "----------------------------";
		cout << "\nCountry Name: " << Currency.CountryName();
		cout << "\nCurrency Code: " << Currency.CurrencyCode();
		cout << "\nCurrency Name: " << Currency.CurrencyName();
		cout << "\nCurrency Rate: " << Currency.Rate();
		cout << "\n------------------------------\n";

	}

	static void _ShowResult(clsCurrencies Currency) {
		if (!Currency.IsEmpty()) {
			cout << "\nCurrency Found :)";
			PrintCurrency(Currency);
		}
		else {
			cout << "\nCurrency not Found :(";
		}
	}

public:
	static void FindCurrencyScreen() {
		_DrowScreenHeader("\tCurrency Find Screen");
		cout << "\nFind By: [1] Code [2] Country ?  ";
		short Answer = 1;
		cin >> Answer;
		if (Answer == 1) {
			string CurrencyCode = "";
			cout << "\nPlease Enter Currency Code:";
			CurrencyCode = clsInputValidate::ReadString();
			clsCurrencies Currency = clsCurrencies::FindByCurrencyCode(CurrencyCode);
			_ShowResult(Currency);
		}
		else
		{
			string CountryName;
			cout << "\nPlease Enter Country Name: ";
			CountryName = clsInputValidate::ReadString();
			clsCurrencies Currency = clsCurrencies::FindByCountryName(CountryName);
			_ShowResult(Currency);
		}
	}
};