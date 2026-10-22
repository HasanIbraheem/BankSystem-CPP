#pragma once
#include<iostream>
#include<iomanip>
#include"clsScreen.h"
#include"clsCurrencies.h"
#include"clsInputValidate.h"

class clsCurrenciesExchangeScreen :protected clsScreen {
private:

	static float _ReadAmount() {
		cout << "\nEnter Amount To Exchange : ";
		float Amount = clsInputValidate::ReadFloatNumber();
		return Amount;
	}

	static clsCurrencies _GetCurrency(string Messege) {
		string CurrencyCode = "";
		cout << Messege << endl;
		CurrencyCode = clsInputValidate::ReadString();
		while (!clsCurrencies::IsCurrencyExist(CurrencyCode)) {
			cout << "\nCurrency is Not Found, Please Enter Another Code: ";
			CurrencyCode = clsInputValidate::ReadString();
		}
		clsCurrencies Currency = clsCurrencies::FindByCurrencyCode(CurrencyCode);
		return Currency;
	}



	static void _PrintCurrencyCard(clsCurrencies Currency,string Titel="Currency Card :") {
		cout << Titel<<endl;
		cout << "----------------------------";
		cout << "\nCountry Name: " << Currency.CountryName();
		cout << "\nCurrency Code: " << Currency.CurrencyCode();
		cout << "\nCurrency Name: " << Currency.CurrencyName();
		cout << "\nCurrency Rate: " << Currency.Rate();
		cout << "\n------------------------------\n";

	}
	static void _CalculateExchange(float Amount, clsCurrencies Currency1, clsCurrencies Currency2) {
		_PrintCurrencyCard(Currency1, "Convert From:");

		float AmountInUSD = Currency1.ConvertToUSD(Amount);

		cout << Amount << " " << Currency1.CurrencyCode()
			<< " = " << AmountInUSD << " USD\n";

		if (Currency2.CurrencyCode() == "USD")
		{
			return;
		}

		cout << "\nConverting from USD to:\n";

		_PrintCurrencyCard(Currency2, "To:");

		float AmountInCurrrency2 = Currency1.ConvertToOtherCurrency(Amount, Currency2);

		cout << Amount << " " << Currency1.CurrencyCode()
			<< " = " << AmountInCurrrency2 << " " << Currency2.CurrencyCode();


}

public:
	static void CurrencyExchangeScreen() {
		char Continue = 'y';

		while (Continue == 'y' || Continue == 'Y')
		{
			system("cls");

			_DrowScreenHeader("\tUpdate Currency Screen");

			clsCurrencies CurrencyFrom = _GetCurrency("\nPlease Enter Currency1 Code: ");
			clsCurrencies CurrencyTo = _GetCurrency("\nPlease Enter Currency2 Code: ");
			float Amount = _ReadAmount();

			_CalculateExchange(Amount, CurrencyFrom, CurrencyTo);

			cout << "\n\nDo you want to perform another calculation? y/n ? ";
			cin >> Continue;

		}
	}

};