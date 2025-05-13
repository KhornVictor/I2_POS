#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include <cctype>
#include <sstream>
#include "color.h"
#include "press_enter_to_continue.h"
using namespace std;

struct Node{
    string name;
    char gender;
    int age;
    string role;
    string email;
    string password;
    string phone;
    Node *next;
};

struct Stack{
    int size;
    Node *top;
};

Stack* create(){
    Stack* newlist = new Stack;
    newlist -> top = NULL;
    newlist -> size = 0;
    return newlist;
}

void push(Stack* s, string email){
    Node* newnode = new Node;
    newnode -> email = email;
    newnode -> next = s -> top;
    s -> top = newnode;
    s -> size++;
}

void display(Stack* s){
    Node* temporary = s -> top;
    while (temporary != NULL){
        cout << temporary -> email << endl;
        temporary = temporary -> next;
    }
}

void get_all_users_from_csv(Stack* s, string filename) {
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
            push(s, email);
        }
        file.close();
    }
}

bool isAllAlphabets(string str) {
    for (char ch : str) {if (!(isalpha(ch) || isspace(ch))) return false;}
    return true;
}

bool isAllDigits(string str) {
    for (char ch : str) {if (!isdigit(ch)) return false;}
    return true;
}

void add_to_user_csv(string name, int age, char gender, string phone, string role, string email, string password){
    system("cls");
    cout << GREEN << "Sign Up successfully" << RESET << endl;
    ofstream file;
    file.open("Database/user.csv", ios::app);
    if (file.is_open()) {
        file << name << "," << age << "," << gender << "," << phone << "," << role << "," << email << "," << password << endl;
        file.close();
    } else cout << RED << "Unable to open file." << RESET << endl;
}

string getPassword(){
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

string confirm_password(){
    string password;
    char ch ;
    cout << "Confirm password: " ;
    while((ch = _getch()) != '\r'){
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


void get_data_from_user(string email,string password){
    Node input;
    bool check = true;
    pressEnterToContinue();

    // check name
    do{  
        system("cls");
        cout << CYAN << "Informatiom" << RESET << endl;
        if (check) cout << BLUE << "Enter Your Information" << RESET << endl;
        else cout << RED << "Invalid name! Name shouldn't with symbol or number!" << RESET << endl;
        cout << "Full-name:\t" << YELLOW ; getline(cin >> ws, input.name); cout << RESET;
        (isAllAlphabets(input.name)) ? check = true : check = false; 
    } while (!check);

    // check Age ===============================================================================>
    do{
        system("cls");
        cout << CYAN << "Informatiom" << RESET << endl;
        if (check) cout << BLUE << "Enter Your Information" << RESET << endl;
        else cout << RED << "Invalid age! Please try to age (1-99)!" << RESET << endl;
        cout << "Full-name:\t" << YELLOW << input.name << RESET << endl;
        cout << "Age:\t\t" << YELLOW; cin >> input.age; cout << RESET;
        (input.age >= 0 && input.age <= 100) ? check = true : check = false; 
    } while (!check);

    // check gender ===============================================================================>
    do {
        system("cls");
        cout << CYAN << "Informatiom" << RESET << endl;
        if (check) cout << BLUE << "Enter Your Information" << RESET << endl;
        else cout << RED << "Invalid gender! Please try to enter (M/F)!" << RESET << endl;
        cout << "Full-name:\t" << YELLOW << input.name << RESET << endl;
        cout << "Age:\t\t" << YELLOW << input.age << RESET << endl;
        cout << "gender(M/F):\t" << YELLOW; cin >> input.gender; cout << RESET;
        (input.gender == 'M' || input.gender == 'm' || input.gender == 'F' || input.gender == 'f') ? check = true : check = false; 
    } while (!check);
    input.gender = toupper(input.gender);
    
    // check phone ===============================================================================>
    do {
        system("cls");
        cout << CYAN << "Informatiom" << RESET << endl;
        if (check) cout << BLUE << "Enter Your Information" << RESET << endl;
        else cout << RED << "Invalid phone number!" << RESET << endl;
        cout << "Full-name:\t" << YELLOW << input.name << RESET << endl;
        cout << "Age:\t\t" << YELLOW << input.age << RESET << endl;
        cout << "gender(M/F):\t" << YELLOW << input.gender << RESET << endl;
        cout << "Phone-number:\t" << YELLOW; cin >> input.phone; cout << RESET;
        (isAllDigits(input.phone) && input.phone[0] == '0' && (input.phone.size() == 9 || input.phone.size() == 10)) ? check = true : check = false; 
    } while (!check);
    add_to_user_csv(input.name, input.age, input.gender, input.phone, "customer", email, password);
}

bool check_validation_of_email(Stack *s, string email){
    Node* temporary = s -> top;
    bool check = false;
    while (temporary != NULL){
        if(temporary -> email == email) {
            system("cls");
            cout << RED << "This email has used by other user!" << RESET << endl;
            check = true;  
            break;
        }
        temporary = temporary -> next;
    }
    return check;
    
}

void get_gmail_and_password_form_user(){
    system("cls");
    Stack *s = create();
    get_all_users_from_csv(s, "Database/user.csv");
    Node input;
    int count = 0;
    cout << CYAN << "Sign up" << RESET << endl;
    while (true){
        cout << "Enter email: " << YELLOW; cin >> input.email; cout << RESET;
        if (check_validation_of_email(s, input.email)) continue;
        if (input.email.size() >= 10 && input.email.substr(input.email.size() - 10) == "@gmail.com") break;
        else {
            system("cls");
            cout << RED << "Invalid email" << RESET << endl;
        }
    }
    system("cls");
    cout << GREEN << "Email accepted!" << RESET << endl;
    cout << "Enter email: " << YELLOW << input.email << RESET << endl;
    input.password = getPassword();
    while (true){
        if (confirm_password() == input.password){
            system("cls");
            cout << GREEN << "Account accepted!" << RESET << endl;
            cout << "Enter email: " << YELLOW << input.email << RESET << endl;
            cout << "Enter password: "; for(int i : input.password){cout << "*";} cout << endl;
            cout << "Confirm password: "; for(int i : input.password){cout << "*";} cout << "\n" << endl;
            get_data_from_user(input.email, input.password);
            break;
        } else{
            system("cls");
            cout << RED << "Confirm password incorrect!" << RESET << endl;
            cout << "Enter email: " << YELLOW << input.email << RESET << endl;
            cout << "Enter password: ";
            for(int i : input.password){
                cout << "*";
            } cout << endl;
        }
    }
}
