#include <iostream> 
#include <windows.h>
#include "color.h"
#include "sign_up.h"
#include "sign_in.h"
using namespace std;


enum LOGIN{
    SIGNIN = 1,
    SIGNUP,
    EXIT
};

int Introduction(){
    int option;
    cout << CYAN << "<============ POS System ===========>" << RESET << endl;
    cout << RED  << "||" << RESET << " Welcome to POS(Point of Sale)   " << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << " 1. Sign in                      " << RED << "||" << RESET << endl; 
    cout << RED  << "||" << RESET << " 2. Sign up                      " << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << " 3. Exit                         " << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << "---------------------------------" << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << " Enter option: " << YELLOW; cin >> option; cout << RESET;
    return option;
}

void ExIT(int time){
    for (int i = time; i > 0; i--){
        system("cls");
        cout << "The system will shut down in " << MAGENTA << i << RESET << ((i <= 1) ? " second" : " seconds");
        Sleep(1000);
    }
    system("cls");
    cout << "Goodbye! Have a nice day!\n" << endl;
    cout << GRAY; system("pause"); cout << RESET;
    system("cls");
    exit(0);
}

void login(){
    system("cls");
    while (true){
        switch (Introduction()){
            case SIGNIN:check_user_sign_in();break;
            case SIGNUP:get_gmail_and_password_form_user();break;
            case EXIT:ExIT(3);break;
            default:break;
        }
    }
}

