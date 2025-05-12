#include <iostream>
#include <fstream>
#include <sstream>
#include <conio.h>
using namespace std;

#define RESET   "\033[0m"
#define BLACK   "\033[30m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m" 
#define WHITE   "\033[37m"
#define GRAY    "\033[90m"
#define BOLD    "\033[1m"

struct Sign_In_Element{
    string email;
    string password;
    Sign_In_Element *next;
};



struct Sign_in_Stack{
    int size;
    Sign_In_Element *top;
};

Sign_in_Stack* create_in_sign_in(){
    Sign_in_Stack* newlist = new Sign_in_Stack;
    newlist -> top = NULL;
    newlist -> size = 0;
    return newlist;
}

void push_in_sign_in(Sign_in_Stack* s, string email, string password){
    Sign_In_Element* newnode = new Sign_In_Element;
    newnode -> email = email;
    newnode -> password = password;
    newnode -> next = s -> top;
    s -> top = newnode;
    s -> size++;
}

string getPassword_in_sign_in(){
    string password;
    char ch ;
    cout << "Enter password: " ;
    while((ch = _getch())!= '\r'){
        if(ch == '\b'){
            if(!password.empty()){
                password.pop_back();
                cout << "\b \b";        
            }
        }else{
            password += ch;
            cout << "*";            
        }
    }
    cout << endl;
    return password;
}

void get_all_users_from_csv_in_sign_in(Sign_in_Stack* s, string filename) {
    ifstream file;
    file.open(filename, ios::in);
    string line;
    if (!file.is_open()) cout << RED << "Cannot open the file!" << RESET << endl;
    else {
        while (getline(file, line)) { // Correct way to read each line
            stringstream ss(line);
            string name, ageStr, genderStr, phone, roleStr, email, password;
            getline(ss, name, ',');
            getline(ss, ageStr, ',');
            getline(ss, genderStr, ',');
            getline(ss, phone, ',');
            getline(ss, roleStr, ',');
            getline(ss, email, ',');
            getline(ss, password);
            push_in_sign_in(s, email, password);
        }
        file.close();
    }
}

bool check_email_in_sign_in(Sign_in_Stack* s, string email){
    Sign_In_Element *temporary = s -> top;
    while (temporary != NULL){
        if (temporary -> email == email) return true;
        temporary = temporary -> next;
    } 
    return false;
}

bool check_email_and_password_in_sign_in(Sign_in_Stack *s, string email, string password){
    Sign_In_Element *temporary = s -> top;
    while (temporary != NULL){
        if (temporary -> email == email && temporary -> password == password) return true;
        temporary = temporary -> next;
    } 
    return false;
}


void check_user_sign_in(){
    system("cls");
    Sign_in_Stack *s = create_in_sign_in();
    get_all_users_from_csv_in_sign_in(s, "Database/user.csv");
    Sign_In_Element input;
    int count = 0;
    do{
        cout << CYAN << "Sign up" << RESET << endl;
        while (true){
            cout << "Enter email: " << YELLOW; cin >> input.email; cout << RESET;
            if (check_email_in_sign_in(s, input.email)) break;
            else {
                system("cls");
                cout << RED << "Invalid email" << RESET << endl;
            }
        }
        system("cls");
        cout << GREEN << "Email accepted!" << RESET << endl;
        cout << "Enter email: " << YELLOW << input.email << RESET << endl;
        input.password = getPassword_in_sign_in();
        if (check_email_and_password_in_sign_in(s, input.email, input.password)){
            system("cls");
            cout << GREEN << "Sign in sucess!" << RESET << endl;
            break;
        }
        else {
            system("cls");
            cout << RED << "Email and password incorrect!" << RESET << endl;
            continue;
        }
    } while (true);
    


}