#pragma once
#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include"clsString.h"

using namespace std;

class clsCurrencies {
private:
	enum enMode{EmptyMode=0, UpdateMode =1};
	enMode _Mode;
	string _CountryName;
	string _CurrencyCode;
	string _CurrencyName;
	float _Rate;

	static clsCurrencies _ConvertLineToCurrencyObject(string Line, string Seperator = "#//#") {
		vector<string>vCurrency;
		vCurrency = clsString::Split(Line,Seperator);
		return clsCurrencies(enMode::UpdateMode, vCurrency[0], vCurrency[1], vCurrency[2], stof(vCurrency[3]));
		
	}

	static string _ConvertCurrencyObjectToLine(clsCurrencies Currency,string Seperator="#//#") {
		string stData = "";
		stData += Currency.CountryName() + Seperator;
		stData += Currency.CurrencyCode() + Seperator;
		stData += Currency.CurrencyName() + Seperator;
		stData += to_string(Currency.Rate());
		return stData;
	}

	static vector<clsCurrencies>_LoadCurrencyDataFromFile() {
		vector<clsCurrencies>vCurrency;
		string Line;
		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);
		if (MyFile.is_open()) {
			while (getline(MyFile, Line)) {
				clsCurrencies Currency = _ConvertLineToCurrencyObject(Line);
				vCurrency.push_back(Currency);
			}
			MyFile.close();
		}
		return vCurrency;
	}

	static void _SaveCurencyObjectToFile(vector<clsCurrencies>_vCurrency) {	
		fstream MyFile;
		MyFile.open("Currencies.txt", ios::out);
		if (MyFile.is_open()) {
			for (clsCurrencies C : _vCurrency) {
				MyFile << _ConvertCurrencyObjectToLine(C,"#//#")<<endl;
			}
			MyFile.close();
		}
	}

	void _Update() {
		vector<clsCurrencies>vCurrency;
		vCurrency = _LoadCurrencyDataFromFile();
		for (clsCurrencies &Currency : vCurrency) {
			if (Currency.CountryName() == CountryName()) {
				Currency = *this;
				break;
			}
		}
		_SaveCurencyObjectToFile(vCurrency);
	}

	static clsCurrencies _GetEmptyCurrencyObject() {
		return clsCurrencies(enMode::EmptyMode, "", "", "", 0);
	}


public:

	clsCurrencies(enMode Mode, string CountryName, string CurrencyCode, string CurrencyName, float Rate) {
		_Mode = Mode;
		_CountryName = CountryName;
		_CurrencyCode = CurrencyCode;
		_CurrencyName = CurrencyName;
		_Rate = Rate;

	}

	bool IsEmpty() {
		return (_Mode==enMode::EmptyMode);
	}


	string CountryName() {
		return _CountryName;
	}
	



	string CurrencyCode() {
		return _CurrencyCode;
	}
	

	
	string CurrencyName() {
		return _CurrencyName;
	}
	

	void UpdateRate(float Rate) {
		_Rate = Rate;
		_Update();
	}
	float Rate() {
		return _Rate;
	}
	

	static clsCurrencies FindByCountryName(string CountryName) {
		CountryName=clsString::UpperFirstLetterOfEachWord(CountryName);
		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);
		if (MyFile.is_open()) {
			string Line;
			while (getline(MyFile, Line)) {
				clsCurrencies Currency = _ConvertLineToCurrencyObject(Line);
				if (Currency.CountryName() == CountryName) {
					MyFile.close();
					return Currency;
				}

			}
			MyFile.close();
		}
		return _GetEmptyCurrencyObject();
	}

	static clsCurrencies FindByCurrencyCode(string CurrencyCode) {
		CurrencyCode=clsString::UpperAllString(CurrencyCode);
		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);
		if (MyFile.is_open()) {
			string Line;
			while (getline(MyFile, Line)) {
				clsCurrencies Currency = _ConvertLineToCurrencyObject(Line);
				if (Currency.CurrencyCode() == CurrencyCode) {
					MyFile.close();
					return Currency;
				}

			}
			MyFile.close();
		}
		return _GetEmptyCurrencyObject();
	}

	static bool IsCurrencyExist(string CurrencyCode) {
		clsCurrencies Currency1 = clsCurrencies::FindByCurrencyCode(CurrencyCode);
		return (!Currency1.IsEmpty());
	}

	static vector<clsCurrencies>GetCurrenciesList() {
		return _LoadCurrencyDataFromFile();
	}

	float ConvertToUSD(float Amount) {
		return (float)(Amount / Rate());
	}

	float ConvertToOtherCurrency(float Amount, clsCurrencies Currency2) {
		float AmountInUSD = ConvertToUSD(Amount);
		if (Currency2.CurrencyCode() == "USD") {
			return AmountInUSD;
		}
		return (float)(AmountInUSD * Currency2.Rate());
	}

};