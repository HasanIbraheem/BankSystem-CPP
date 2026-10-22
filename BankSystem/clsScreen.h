#pragma once
#include<iostream>
#include"clsUser.h"
#include"Global.h"
#include"clsDate.h"

using namespace std;

class clsScreen {
protected:
	static void _DrowScreenHeader(string Titel, string subtitel="") {
		cout << "\t\t\t\t\t___________________________________________";
		cout << "\n\n\t\t\t\t\t" << Titel ;
		if (subtitel != "") {
			cout << "\n\n\t\t\t\t\t" << subtitel << "";
		}
		cout << "\n\t\t\t\t\t___________________________________________\n\n";
        cout << "\t\t\t\t\tUser: " << CurrentUser.UserName <<"\n";
        cout << "\t\t\t\t\tDate: " << clsDate::DateToString(clsDate())<<"\n";
	}

    

    

    static bool CheckAccessRights(clsUser::enPermessions Permission)
    {

        if (!CurrentUser.CheckAccessPermession(Permission))
        {
            cout << "\t\t\t\t\t______________________________________";
            cout << "\n\n\t\t\t\t\t  Access Denied! Contact your Admin.";
            cout << "\n\t\t\t\t\t______________________________________\n\n";
            return false;
        }
        else
        {
            return true;
        }

    }

};
	
