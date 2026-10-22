#pragma once
#include<iostream>
#include<iomanip>
#include"clsScreen.h"
#include"clsInputValidate.h"
#include"clsUserListScreen.h"
#include"clsAddNewUserScreen.h"
#include"clsDeleteUserScreen.h"
#include"clsUpdateUserScreen.h"
#include"clsFindUserScreen.h"
#include"clsUser.h"
#include"clsTransferScreen.h"
using namespace std;

class clsManageUserScreenMenue :protected clsScreen {
private:
    enum enManageUserMenueOption {
        eListUsers = 1, eAddNewUser = 2, eDeleteUser = 3,eUpdateUser=4,eFindUser=5,
        eMainMenue = 6,
    };

    static short _ReadManageUserMenueOption() {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
        short Choice = clsInputValidate::ReadShortNumberBetween(1, 6, "Please Enter a Number from 1 To 6");
        return Choice;
    }

    static void _GoToManageUserMenue() {
        cout << setw(37) << left << "" << "\n\tPress any key to go back to Manage User Menue...\n";
        system("pause>0");
        ShowManageUserMenue();
    }

    static void _ShowListUsersScreen()
    {
       //  cout << "\nList Users Screen Will be here...\n";
        clsUserListScreen::ShowUserList();
        

    }

    static void _ShowAddNewScreen()
    {
       // cout << "\nAdd New User Screen Will be here...\n";
        clsAddNewUserScreen::ShowAddNewUser();
        

    }

    static void _ShowDeleteUserScreen()
    {
        //cout << "\nDelete User Screen Will be here...\n";
        clsDeleteUserScreen::DeleteUserScreen();

    }

    static void _ShowUpdateUserScreen()
    {
        //cout << "\nUpdate User Screen Will be here...\n";
        clsUpdateUserScreen::UpdateUserInfo();

    }

    static void _ShowFindUserScreen()
    {
       // cout << "\nFind User Screen Will be here...\n";
        clsFindUserScreen::FindUserScren();

    }



    static void _PerformManageUserMenueOption(enManageUserMenueOption ManageUserMenueInfo) {
        switch (ManageUserMenueInfo) {
        case enManageUserMenueOption::eListUsers: {
            system("cls");
            _ShowListUsersScreen();
            _GoToManageUserMenue();
            break;
        }
        case enManageUserMenueOption::eAddNewUser:{
            system("cls");
            _ShowAddNewScreen();
            _GoToManageUserMenue();
            break;
        }
        case enManageUserMenueOption::eDeleteUser: {
            system("cls");
            _ShowDeleteUserScreen();
            _GoToManageUserMenue();
            break;
        }
        case enManageUserMenueOption::eUpdateUser: {
            system("cls");
            _ShowUpdateUserScreen();
            _GoToManageUserMenue();
            break;
        }
        case enManageUserMenueOption::eFindUser: {
            system("cls");
            _ShowFindUserScreen();
            _GoToManageUserMenue();
            break;
        }
        case enManageUserMenueOption::eMainMenue: {

        }

        }


    }


public:
    static void ShowManageUserMenue() {
        system("cls");

        if (!CheckAccessRights(clsUser::enPermessions::pManageUsers)) {
            return;
        }

        _DrowScreenHeader("\t\tManage User Screen");



        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t\tManage User Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] List Users.\n";
        cout << setw(37) << left << "" << "\t[2] Add New User.\n";
        cout << setw(37) << left << "" << "\t[3] Delete User.\n";
        cout << setw(37) << left << "" << "\t[4] Update User.\n";
        cout << setw(37) << left << "" << "\t[5] Find User.\n";
        cout << setw(37) << left << "" << "\t[6] Main Menue.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerformManageUserMenueOption((enManageUserMenueOption)_ReadManageUserMenueOption());
    }


};