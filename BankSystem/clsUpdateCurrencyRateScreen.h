#pragma once
#include<iostream>
#include<iomanip>
#include"clsScreen.h"
#include"clsInputValidate.h"
#include"clsCurrencies.h"

class clsUpdateCurrencyRateScreen :protected clsScreen {
private:

	static float _ReadRate() {
		cout << "\nEnter New Rate: ";
		float NewRate = clsInputValidate::ReadFloatNumber();
		return NewRate;
	}

	static void _PrintCurrency(clsCurrencies Currency) {
		cout << "\nCurrency Card:\n";
		cout << "----------------------------";
		cout << "\nCountry Name: " << Currency.CountryName();
		cout << "\nCurrency Code: " << Currency.CurrencyCode();
		cout << "\nCurrency Name: " << Currency.CurrencyName();
		cout << "\nCurrency Rate: " << Currency.Rate();
		cout << "\n------------------------------\n";

	}


public:
	static void UpdateCurrency() {
		_DrowScreenHeader("\tUpdate Currencies Screen");
		string CurrencyCode = "";
		cout << "\nPlease Enter Currency Code:";
		CurrencyCode = clsInputValidate::ReadString();
		while (!clsCurrencies::IsCurrencyExist(CurrencyCode)) {
			cout << "\nCurrency is Not Found, Please Enter Another Code: ";
			CurrencyCode = clsInputValidate::ReadString();
		}
		clsCurrencies Currency = clsCurrencies::FindByCurrencyCode(CurrencyCode);
		_PrintCurrency(Currency);
		cout << "\nAre You Sure You Want To Update The Rate Of This Currency ? y/n";
		char Answer = 'n';
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y') {
			cout << "\nUpdate Currency Rate:";
			cout << "\n----------------------------";
			
			Currency.UpdateRate(_ReadRate());
			_PrintCurrency(Currency);
		}
	}
};
