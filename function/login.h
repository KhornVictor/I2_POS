#include<iostream> 
#include "sign_up.h"
#include "sign_in.h"
using namespace std;

#define YELLOW  "\033[33m"

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

void login(){
    system("cls");
    while (true){
        switch (Introduction()){
            case SIGNIN:check_user_sign_in();break;
            case SIGNUP:get_gmail_and_password_form_user();break;
            case EXIT:break;
            default:break;
        }
    }
}

