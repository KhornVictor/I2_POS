#include<iostream>
#include "color.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <windows.h>
#include <cctype>
using namespace std;


struct Admin_User_Element{
    string name;
    char gender;
    int age;
    string role;
    string email;
    string password;
    string phone;
    Admin_User_Element *next;
    Admin_User_Element *previous;
};

struct Admin_List{
    int size;
    Admin_User_Element* head;
    Admin_User_Element* tail;
};

Admin_List *create_new_admin_user_list(){
    Admin_List *New_Admin_User = new Admin_List;
    New_Admin_User -> size = 0;
    New_Admin_User -> head = NULL;
    New_Admin_User -> tail = NULL;
    return New_Admin_User;
}

void Admin_insert_user_begin(Admin_List *list, string name, char gender, int age, string phone, string role, string email, string password){
    Admin_User_Element *newnode = new Admin_User_Element;
    newnode -> name = name;
    newnode -> gender = gender;
    newnode -> age = age;
    newnode -> phone = phone;
    newnode -> role = role;
    newnode -> email = email;
    newnode -> password = password;                                                                     
    newnode -> previous = NULL;                                                                   
    newnode -> next = list -> head;                                                            
    if(list -> size == 0) list -> tail = newnode;                                                  
    else list -> head -> previous = newnode;                                                        
    list -> head = newnode;                                                                      
    list -> size++;                                                                             
}

void Admin_insert_user_end(Admin_List *list, string name, char gender, int age, string phone, string role, string email, string password){
    Admin_User_Element *newnode = new Admin_User_Element; 
    newnode -> name = name;
    newnode -> gender = gender;
    newnode -> age = age;
    newnode -> phone = phone;
    newnode -> role = role;
    newnode -> email = email;
    newnode -> password = password;                                                                    
    newnode -> next = NULL;                                                                   
    newnode -> previous = list -> tail;                                                          
    if(list -> size == 0) list -> head = newnode;                                                  
    else list -> tail -> next = newnode;                                                        
    list -> tail = newnode;                                                                      
    list -> size++;                                                                             
}

void admin_delete_end (Admin_List* list) {
    if (list -> size == 0) return;                                                         
    Admin_User_Element *temporary = list -> tail;                                                      
    list -> tail = list -> tail -> previous;                                              
    if (list -> tail != NULL) list -> tail -> next = NULL;                                 
    else list -> head = NULL;                                                                     
    delete temporary;                                                                        
    list -> size--;                                                                                  
}

void admin_delete_begin (Admin_List* list) {
    if (list -> size == 0) return;                                                            
    Admin_User_Element *temporary = list -> head;                                                       
    list -> head = list -> head -> next;                                                     
    if (list->head != NULL) list -> head -> previous = NULL;                                   
    else list->tail = NULL;                                                                        
    delete temporary;                                                                   
    list->size--;                                                           
}

void admin_delete_random_variablesx_by_index(Admin_List* list, int index_that_have_to_delete){
    if (list -> size == 0 || index_that_have_to_delete < 0) return;
    if (index_that_have_to_delete == list -> size) admin_delete_end(list);
    else if (index_that_have_to_delete == 1) admin_delete_begin(list);
    else {
        Admin_User_Element *temporary = list->head;                                                
        for (int i = 0; i < index_that_have_to_delete - 1; i++) temporary = temporary->next;           
        if (temporary->previous != NULL) temporary->previous->next = temporary->next;       
        else list->head = temporary->next;                                                    
        if (temporary->next != NULL) temporary->next->previous = temporary->previous;             
        else list->tail = temporary->previous;                                              
        delete temporary;                                                            
        list->size--;                                                                  
    }
}

void admin_add_specific(Admin_List *list, int position, string name, char gender, int age, string phone, string role, string email, string password){
    Admin_User_Element* newnode = new Admin_User_Element;
    newnode -> name = name;
    newnode -> gender = gender;
    newnode -> age = age;
    newnode -> phone = phone;
    newnode -> role = role;
    newnode -> email = email;
    newnode -> password = password;
    if (position == 1 || list -> size == 0) Admin_insert_user_begin(list, name, gender, age, phone, role, email, password);
    else if (position == list -> size + 1) Admin_insert_user_end(list, name, gender, age, phone, role, email, password); 
    else if(position < 0 || position > list -> size) cout << "Invalid Position" << endl;
    else {
        Admin_User_Element* temporary = list->head;
        for (int i = 1; i < position - 1; i++){temporary = temporary -> next;}
        newnode -> previous = temporary;
        newnode -> next = temporary -> next; 
        if (temporary -> next != NULL) temporary -> next -> previous = newnode;
        temporary -> next = newnode;
        list -> size++;
    }
}

void admin_get_all_users_from_csv(Admin_List* s, string filename) {
    ifstream file;
    file.open(filename, ios::in);
    string line;
    if (!file.is_open()) cout << RED << "Cannot open the file!" << RESET << endl;
    else {
        while (getline(file, line)) {
            stringstream ss(line);
            string name, ageStr, genderStr, phone, role, email, password;
            getline(ss, name, ',');
            getline(ss, ageStr, ',');
            getline(ss, genderStr, ',');
            getline(ss, phone, ',');
            getline(ss, role, ',');
            getline(ss, email, ',');
            getline(ss, password);

            int age = stoi(ageStr);
            char gender = genderStr[0];

            Admin_insert_user_end(s, name, gender, age, phone, role, email, password);
        }
        file.close();
    }
}

void admin_option(){
    cout << CYAN << "<===== " << GREEN << "Admin" << CYAN << " =======================>" << RESET << endl;
    cout << RED  << "||" << GRAY  << " Admin welcome                   " << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << "---------------------------------" << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << " 1. Check User                   " << RED << "||" << RESET << endl; 
    cout << RED  << "||" << RESET << " 2. Check Product                " << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << " 3. Check Login                  " << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << " 4. Logout                       " << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << " 5. Exit                         " << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << "=================================" << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << " Enter option: ";
}


void admin_display_user_table(Admin_List* list, bool clear) {
    Admin_User_Element* temporary = list->head;
    int number = 1;
    cout << GREEN << "Here are all user in this system ..." << endl << RESET << endl;
    cout << left
         << setw(8)  << "No"
         << setw(20) << "Name"
         << setw(6)  << "Age"
         << setw(8)  << "Gender"
         << setw(15) << "Phone"
         << setw(12) << "Role"
         << endl;
    cout << string(69, '-') << endl;

    while (temporary != NULL) {
        if (temporary -> role == "admin") cout << GREEN;
        else if (temporary -> role == "customer") cout << YELLOW;
        else if (temporary -> role == "manager") cout << RED;
        else cout << BLUE;
        cout << left
             << setw(8)  << number
             << setw(20) << temporary -> name
             << setw(6)  << temporary -> age
             << setw(8)  << temporary -> gender
             << setw(15) << temporary -> phone
             << setw(12) << temporary -> role
             << endl;
        temporary = temporary -> next;
        number++;
        cout << RESET;
    }
    cout << endl
         << GREEN  << "GREEN"  << RESET << " : admin\t"
         << RED    << "RED"    << RESET << " : manager\t"
         << BLUE   << "BLUE"   << RESET << " : cashier\t"
         << YELLOW << "YELLOW" << RESET << " : customer\t"
         << endl;
    if (clear) {cout << GRAY; system("pause"); cout << RESET << endl;system("cls");}
}

void admin_check_user_display_role_menu (Admin_List* list,string role){
    Admin_User_Element* temporary = list->head;
    int number = 1;
    int count = 0;
    cout << GREEN << "Here are " << role << endl << RESET << endl;
    cout << left
         << setw(8)  << "No"
         << setw(20) << "Name"
         << setw(6)  << "Age"
         << setw(8)  << "Gender"
         << setw(15) << "Phone"
         << setw(12) << "Role"
         << endl;
    cout << string(69, '-') << endl;
    while (temporary != NULL) {
        if (temporary -> role == role){
            cout << left
                 << setw(8)  << number
                 << setw(20) << temporary->name
                 << setw(6)  << temporary->age
                 << setw(8)  << temporary->gender
                 << setw(15) << temporary->phone
                 << setw(12) << temporary->role
                 << endl;
            temporary = temporary -> next;
            number++;
            count++;
        }
        else temporary = temporary -> next;
    }
    if (count == 0) {system("cls"); cout << YELLOW << "List Empty! :)" RESET;}
    cout << endl << GRAY; system("pause"); cout << RESET << endl;
    system("cls");
}

void admin_check_user_display_age_menu (Admin_List* list){
    Admin_User_Element* temporary = list->head;
    int number = 1;
    int count = 0, maximum, minimum;
    cout << "Enter age to display" << endl;
    cout << "Min : "; cin >> minimum;
    cout << "Max : "; cin >> maximum;
    system("cls");
    cout << GREEN << "Here are user of ages between ... " << minimum << " and " << maximum << endl << RESET << endl;
    cout << left
         << setw(8)  << "No"
         << setw(20) << "Name"
         << setw(6)  << "Age"
         << setw(8)  << "Gender"
         << setw(15) << "Phone"
         << setw(12) << "Role"
         << endl;
    cout << string(69, '-') << endl;

    while (temporary != NULL) {
        if (temporary -> age >= minimum && temporary -> age <= maximum){
            cout << left
                 << setw(8)  << number
                 << setw(20) << temporary->name
                 << setw(6)  << temporary->age
                 << setw(8)  << temporary->gender
                 << setw(15) << temporary->phone
                 << setw(12) << temporary->role
                 << endl;
            temporary = temporary -> next;
            number++;
            count++;
        }
        else temporary = temporary -> next;
    }
    if (count == 0) {system("cls"); cout << YELLOW << "List Empty! :)" RESET;}
    cout << endl << GRAY; system("pause"); cout << RESET << endl;
    system("cls");
}

void admin_check_user_display_gender_menu (Admin_List *list){
    Admin_User_Element* temporary = list -> head;
    int number = 1;
    int count = 0;
    char gender;
    cout << "Enter the gender (M/F) : " << YELLOW; cin >> gender; cout << RESET;
    gender = toupper(gender);
    system("cls");
    if (gender == 'M' || gender == 'F'){
        cout << GREEN << "Here are " << ((gender == 'M') ? "male" : "female") << " user ..." << endl << RESET << endl;
        cout << left
             << setw(8)  << "No"
             << setw(20) << "Name"
             << setw(6)  << "Age"
             << setw(8)  << "Gender"
             << setw(15) << "Phone"
             << setw(12) << "Role"
             << endl;
        cout << string(69, '-') << endl;
    
        while (temporary != NULL) {
            if (temporary -> gender == gender){
                cout << left
                     << setw(8)  << number
                     << setw(20) << temporary->name
                     << setw(6)  << temporary->age
                     << setw(8)  << temporary->gender
                     << setw(15) << temporary->phone
                     << setw(12) << temporary->role
                     << endl;
                temporary = temporary -> next;
                number++;
                count++;
            }
            else temporary = temporary -> next;
        }
        if (count == 0) {system("cls"); cout << YELLOW << "List Empty! :)" RESET;}
        cout << endl << GRAY; system("pause"); cout << RESET << endl;
        system("cls");
    }
    else cout << RED << "Invalid Input!" << RESET << endl;
}

void admin_display_user_email_password(Admin_List* list) {
    Admin_User_Element* temp = list -> head;
    int number = 1;
    cout << GREEN << "Here are email and password of all user ... " << endl << RESET << endl;
    cout << left
         << setw(8)  << "No"
         << setw(20) << "Name"
         << setw(30) << "Email"
         << setw(20) << "Password"
         << endl;
    cout << string(78, '-') << endl;

    while (temp != NULL) {
        cout << left
             << setw(8)  << number
             << setw(20) << temp->name
             << setw(30) << temp->email
             << setw(20) << temp->password
             << endl;
        temp = temp->next;
        number++;
    }
    cout << endl << GRAY; system("pause"); cout << RESET << endl;
    system("cls");
}

void admin_check_user_display_menu(Admin_List* list){
    system("cls");
    int option = 0;
    while(option != 9){
        cout << CYAN << "<===== " << GREEN << "Admin" << CYAN << " =======================>" << RESET << endl;
        cout << RED  << "||" << GRAY  << " Admin/Check User/Display        " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << "---------------------------------" << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 1. All                          " << RED << "||" << RESET << endl; 
        cout << RED  << "||" << RESET << " 2. Age                          " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 3. Gender                       " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 4. Admin                        " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 5. Manager                      " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 6. Customer                     " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 7. Cashier                      " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 8. Email & Password             " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 9. Back                         " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << "=================================" << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " Enter option: " << YELLOW; cin >> option; cout << RESET;
        switch (option){
            case 1:system("cls");admin_display_user_table(list, true);break;
            case 2:system("cls");admin_check_user_display_age_menu(list);break;
            case 3:system("cls");admin_check_user_display_gender_menu(list);break;
            case 4:system("cls");admin_check_user_display_role_menu(list, "admin");break;
            case 5:system("cls");admin_check_user_display_role_menu(list, "manager");break;
            case 6:system("cls");admin_check_user_display_role_menu(list, "customer");break;
            case 7:system("cls");admin_check_user_display_role_menu(list, "cashier");break;
            case 8:system("cls");admin_display_user_email_password(list);break;
            case 9:system("cls");break;
            default:system("cls");cout << RED << "Invalid Input" << RESET << endl;break;
        }
    }
}

void admin_write_all_users_to_csv(Admin_List* list, const string& filename) {
    ofstream file(filename, ios::out);
    if (!file.is_open()) {cout << RED << "Cannot open the file for writing!" << RESET << endl; return;}
    Admin_User_Element* temporary = list -> head;
    while (temporary != NULL) {
        file << temporary -> name << ","
             << temporary -> age << ","
             << temporary -> gender << ","
             << temporary -> phone << ","
             << temporary -> role << ","
             << temporary -> email << ","
             << temporary -> password << endl;
        temporary = temporary ->next;
    }
    file.close();
}

bool admin_isAllAlphabets(string str) {
    for (char ch : str) {if (!(isalpha(ch) || isspace(ch))) return false;}
    return true;
}

bool admin_isAllDigits(string str) {
    for (char ch : str) {if (!isdigit(ch)) return false;}
    return true;
}

string admin_change_string_to_lower(string str) {
    string x;
    for (char ch : str) {
        ch = tolower(ch);
        x += ch;
    }
    return x;
}

void admin_check_user_modify_change_information_add_to_list(Admin_List *list, int select, string name, char gender, int age, string phone, string role, string email, string password){
    admin_delete_random_variablesx_by_index(list, select);
    admin_add_specific(list, select, name, gender, age, phone, role, email, password);
}

bool check_validation_of_email(Admin_List *s, string email){
    Admin_User_Element* temporary = s -> head;
    bool check = false;
    while (temporary != NULL){
        if(temporary -> email == email) {
            system("cls");
            cout << RED << "This email has used by other user!" << RESET << endl;
            check = true;  
            break;
        }temporary = temporary -> next;
    }return check;
}

string admin_check_user_modify_change_information_name(int header_condition){
    string x;
    while (true){
        if (header_condition == 1) cout << CYAN << "Name modification ... " << RESET << endl;
        else if (header_condition == 2) cout << CYAN << "Adding User ... " << RESET << endl;
        cout << "Enter new name: " << YELLOW; getline(cin >> ws, x); cout << RESET;
        system("cls");
        if (header_condition == 1) cout << GREEN << "Name's changed !" << RESET << endl;
        else if (header_condition == 2) cout << GREEN << "Name's added !\n" << RESET << endl;
        if (admin_isAllAlphabets(x)) return x;
        else {system("cls");cout << RED << "Invlid name!" << RESET << endl;continue;}
    }
}

char admin_check_user_modify_change_information_gender(int header_condition){
    char x;
    while (true){
        if (header_condition == 1) cout << CYAN << "Gender modification ... " << RESET << endl;
        else if (header_condition == 2) cout << CYAN << "Adding User ... " << RESET << endl;
        cout << "Enter new Gender: " << YELLOW; cin >> x; cout << RESET;
        system("cls");
        if (header_condition == 1) cout << GREEN << "Gender's changed !" << RESET << endl;
        else if (header_condition == 2) cout << GREEN << "Gender's added !\n" << RESET << endl;
        x = toupper(x);
        if (x == 'M' || x == 'F') return x;
        else {system("cls");cout << RED << "Invlid gender!" << RESET << endl; continue;}
    }
}

int admin_check_user_modify_change_information_age(int header_condition){
    int x;
    while (true){
        if (header_condition == 1) cout << CYAN << "Age modification ... " << RESET << endl;
        else if (header_condition == 2) cout << CYAN << "Adding User ... " << RESET << endl;
        cout << "Enter new Age: " << YELLOW; cin >> x; cout << RESET;
        system("cls");
        if (header_condition == 1) cout << GREEN << "Age's changed !" << RESET << endl;
        else if (header_condition == 2) cout << GREEN << "Age's added !\n" << RESET << endl;
        if (x >= 0 && x <= 100) return x;
        else {system("cls");cout << RED << "Invlid age!" << RESET << endl; continue;}
    }
}

string admin_check_user_modify_change_information_phone(int header_condition){
    while (true){
        string x;
        if (header_condition == 1) cout << CYAN << "Phone modification ... " << RESET << endl;
        else if (header_condition == 2) cout << CYAN << "Adding User ... " << RESET << endl;
        cout << "Enter new Phone: " << YELLOW; cin >> x; cout << RESET;
        system("cls");
        if (header_condition == 1) cout << GREEN << "Phone's changed !" << RESET << endl;
        else if (header_condition == 2) cout << GREEN << "Phone's added !\n" << RESET << endl;
        if (admin_isAllDigits(x) && x[0] == '0' && (x.size() == 9 || x.size() == 10)) return x;
        else {system("cls");cout << RED << "Invlid Phone!" << RESET << endl; continue;}
    }
}

string admin_check_user_modify_change_information_role(int header_condition){
    string x;
    while (true){
        if (header_condition == 1) cout << CYAN << "Role modification ... " << RESET << endl;
        else if (header_condition == 2) cout << CYAN << "Adding User ... " << RESET << endl;
        cout << "Enter new Role: " << YELLOW; cin >> x; cout << RESET;
        x = admin_change_string_to_lower(x);
        system("cls");
        if (header_condition == 1) cout << GREEN << "Role's changed !" << RESET << endl;
        else if (header_condition == 2) cout << GREEN << "Role's added !\n" << RESET << endl;
        if (x == "admin"   || 
            x == "manager" || 
            x == "cashier" ||
            x == "customer"
        ) return x;
        else {system("cls");cout << RED << "Invlid Role!" << RESET << endl; continue;}
    }
}

string admin_check_user_modify_change_information_email(Admin_List *list ,int header_condition){
    string x;
    while (true){
        if (header_condition == 1) cout << CYAN << "Email modification ... " << RESET << endl;
        else if (header_condition == 2) cout << CYAN << "Adding User ... " << RESET << endl;
        cout << "Enter new Email: " << YELLOW; cin >> x; cout << RESET;
        system("cls");
        if (header_condition == 1) cout << GREEN << "Email's changed !" << RESET << endl;
        else if (header_condition == 2) cout << GREEN << "Email's added !\n" << RESET << endl;
        if (check_validation_of_email(list, x)) continue;
        if (x.size() >= 10 && x.substr(x.size() - 10) == "@gmail.com") return x;
        else {system("cls");cout << RED << "Invlid Email!" << RESET << endl; continue;}
    }
}

string admin_check_user_modify_change_information_password(int header_condition){
    string x;
    if (header_condition == 1) cout << CYAN << "Password modification ... " << RESET << endl;
    else if (header_condition == 2) cout << CYAN << "Adding User ... " << RESET << endl;
    cout << "Enter new Password: " << YELLOW; cin >> x; cout << RESET;
    system("cls");
    if (header_condition == 1) cout << GREEN << "Password's changed !" << RESET << endl;
    else if (header_condition == 2) cout << GREEN << "Passowrd's added !\n" << RESET << endl;
    return x;
}

void admin_check_user_modify_add_user(Admin_List *list){
    string email = admin_check_user_modify_change_information_email(list, 2);
    string password = admin_check_user_modify_change_information_password(2);
    string name = admin_check_user_modify_change_information_name(2);
    int age = admin_check_user_modify_change_information_age(2);
    char gender = admin_check_user_modify_change_information_gender(2);
    string role = admin_check_user_modify_change_information_role(2);
    string phone = admin_check_user_modify_change_information_phone(2);
    system("cls");
    cout << CYAN << "New User ... " << RESET << endl
         << "Name :   " << YELLOW << name << RESET << endl
         << "Gender : " << YELLOW << gender << RESET << endl
         << "Age :    " << YELLOW << age << RESET << endl
         << "Role :   " << YELLOW << role << RESET << endl
         << "Phone :  " << YELLOW << phone << RESET << endl
         << "Email :  " << YELLOW << email << RESET << endl << endl;
    cout << GRAY; system("pause"); system("cls"); cout << RESET;
    cout << GREEN << "New User added ... " << RESET << endl;
    Admin_insert_user_end(list, name, gender, age, phone, role, email, password);
    admin_write_all_users_to_csv(list, "Database/user.csv");

}


void admin_check_user_modify_change_information(Admin_List *list){
    Admin_User_Element* temporary = new Admin_User_Element;
    int option = 0;
    int select;
    while(option != 8){
        int number = 1;
        temporary = list -> head; 
        cout << GREEN << "Modification Menu ..." << endl << RESET << endl;
        cout << left
            << setw(8)  << "No"
            << setw(20) << "Name"
            << setw(6)  << "Age"
            << setw(8)  << "Gender"
            << setw(15) << "Phone"
            << setw(12) << "Role"
            << endl;
        cout << string(69, '-') << endl;

        while (temporary != NULL) {
            if (temporary -> role == "admin") cout << GREEN;
            else if (temporary -> role == "customer") cout << YELLOW;
            else if (temporary -> role == "manager") cout << RED;
            else cout << BLUE;
            cout << left
                << setw(8)  << number
                << setw(20) << temporary -> name
                << setw(6)  << temporary -> age
                << setw(8)  << temporary -> gender
                << setw(15) << temporary -> phone
                << setw(12) << temporary -> role
                << endl;
            temporary = temporary -> next;
            number++;
            cout << RESET;
        }
        cout << endl
            << GREEN  << "GREEN"  << RESET << " : admin\t"
            << RED    << "RED"    << RESET << " : manager\t"
            << BLUE   << "BLUE"   << RESET << " : cashier\t"
            << YELLOW << "YELLOW" << RESET << " : customer\t"
            << endl << endl;

        cout << CYAN << "<===== " << GREEN << "Admin" << CYAN << " =================================>" << RESET << endl;
        cout << RED  << "||" << GRAY  << " Admin/Check User/Modify/Change Information " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << "--------------------------------------------" << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " Enter No of user to modify                 " << RED << "||" << RESET << endl; 
        cout << RED  << "||" << RESET << "============================================" << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " Number: " << YELLOW; cin >> select; cout << RESET;

        if (select <= 0 || select > list -> size ) {
            system("cls");
            cout << RED << "Invalid Input" << RESET << endl;        
            continue;
        }
        
        temporary = list -> head;
        for (int i = 0; i < select - 1; i++){temporary = temporary -> next;}
        system("cls");
        cout << GREEN;
        for (char i : temporary -> name){
            if (i == ' ') break;
            else cout << i;
        }
        cout << "'s Information" << RESET << endl;
        cout << GRAY << string(50, '-') << RESET << endl;
        cout << "Name: " << YELLOW << temporary -> name << RESET << endl;
        cout << "Gender: " << YELLOW << temporary -> gender << RESET << endl;
        cout << "Age: " << YELLOW << temporary -> age << RESET << endl;
        cout << "Role: " << YELLOW << temporary -> role << RESET << endl;
        cout << "Email: " << YELLOW << temporary -> email << RESET << endl;
        cout << "Phone: " << YELLOW << temporary -> phone << RESET << endl;
        cout << GRAY << string(50, '-') << RESET << endl;

        cout << CYAN << "<===== " << GREEN << "Admin" << CYAN << " =================================>" << RESET << endl;
        cout << RED  << "||" << GRAY  << " Admin/Check User/Modify/Change Information " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << "--------------------------------------------" << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " Enter the option to modify                 " << RED << "||" << RESET << endl; 
        cout << RED  << "||" << RESET << " 1. Name                                    " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 2. Gender                                  " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 3. Age                                     " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 4. Role                                    " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 5. Email                                   " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 6. Phone                                   " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 7. Password                                " << RED << "||" << RESET << endl;  
        cout << RED  << "||" << RESET << " 8. Back                                    " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << "============================================" << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " Modification option: " << YELLOW; cin >> option; cout << RESET;
        switch (option){
            case 1:system("cls");temporary -> name = admin_check_user_modify_change_information_name(1);break;
            case 2:system("cls");temporary -> gender = admin_check_user_modify_change_information_gender(1);break;
            case 3:system("cls");temporary -> age = admin_check_user_modify_change_information_age(1);break;
            case 4:system("cls");temporary -> role = admin_check_user_modify_change_information_role(1);break;
            case 5:system("cls");temporary -> email = admin_check_user_modify_change_information_email(list, 1);break;
            case 6:system("cls");temporary -> phone = admin_check_user_modify_change_information_phone(1);break;
            case 7:system("cls");temporary -> password = admin_check_user_modify_change_information_password(1);break;
            case 8:system("cls");break;
        }
        admin_check_user_modify_change_information_add_to_list(list, select, temporary -> name, temporary -> gender, temporary -> age, temporary -> phone, temporary -> role, temporary -> email, temporary -> password);
        char admin_check_if_want_to_write = 'A';
        while (admin_check_if_want_to_write != 'N' && admin_check_if_want_to_write != 'Y') {
            cout << "Do you want to modify something else? [Y(es)/N(o)] => "; cin >> admin_check_if_want_to_write;
            admin_check_if_want_to_write = toupper(admin_check_if_want_to_write);
            switch (admin_check_if_want_to_write){
                case 'Y':system("cls");cout << GREEN << "Information changed!!!" << RESET << endl << YELLOW << "Note: " << RESET << "It hasn't pushed to database yet." << endl;break;
                case 'N':system("cls");admin_write_all_users_to_csv(list, "Database/user.csv");break;
                default :system("cls");cout << RED << "Invalid input" << RESET << endl;
            }
        }  
    }
}

void admin_check_user_modify_menu(Admin_List *list){
    Admin_User_Element* temporary = list->head;
    int number = 1;
    int option = 0;
    while(option != 3){
        cout << CYAN << "Modification Menu ..." << endl << RESET << endl;
        cout << left
            << setw(8)  << "No"
            << setw(20) << "Name"
            << setw(6)  << "Age"
            << setw(8)  << "Gender"
            << setw(15) << "Phone"
            << setw(12) << "Role"
            << endl;
        cout << string(69, '-') << endl;

        while (temporary != NULL) {
            if (temporary -> role == "admin") cout << GREEN;
            else if (temporary -> role == "customer") cout << YELLOW;
            else if (temporary -> role == "manager") cout << RED;
            else cout << BLUE;
            cout << left
                << setw(8)  << number
                << setw(20) << temporary -> name
                << setw(6)  << temporary -> age
                << setw(8)  << temporary -> gender
                << setw(15) << temporary -> phone
                << setw(12) << temporary -> role
                << endl;
            temporary = temporary -> next;
            number++;
            cout << RESET;
        }
        cout << endl
            << GREEN  << "GREEN"  << RESET << " : admin\t"
            << RED    << "RED"    << RESET << " : manager\t"
            << BLUE   << "BLUE"   << RESET << " : cashier\t"
            << YELLOW << "YELLOW" << RESET << " : customer\t"
            << endl << endl;

        cout << CYAN << "<===== " << GREEN << "Admin" << CYAN << " =======================>" << RESET << endl;
        cout << RED  << "||" << GRAY  << " Admin/Check User/Modify         " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << "---------------------------------" << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 1. Add User                     " << RED << "||" << RESET << endl; 
        cout << RED  << "||" << RESET << " 2. Change information           " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 3. Back                         " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << "=================================" << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " Enter option: " << YELLOW; cin >> option; cout << RESET;
        switch (option){
            case 1:system("cls");admin_check_user_modify_add_user(list);break;
            case 2:system("cls");admin_check_user_modify_change_information(list);break;
            case 3:system("cls");break;
            default:system("cls");cout << RED << "Invalid Input" << RESET << endl;break;
        }
    }
}

void admin_check_user_search_display_email_only(Admin_List* list) {
    Admin_User_Element* temp = list->head;
    int number = 1;
    cout << left << setw(8) << "No" << setw(30) << "Email" << endl;
    cout << GRAY << string(38, '-') << RESET << endl;
    while (temp != NULL) {
        cout << left << setw(8) << number << YELLOW << setw(30)  << temp->email << RESET << endl;
        temp = temp->next;
        number++;
    } cout << GRAY << string(38, '-') << RESET << endl;
}

void admin_check_user_search_menu(Admin_List *list){
    string email;
    bool check = false;
    Admin_User_Element *temporary = list -> head;
    admin_check_user_search_display_email_only(list);
    cout << endl;
    cout << CYAN << "<===== " << GREEN << "Admin" << CYAN << " =======================>" << RESET << endl;
    cout << RED  << "||" << GRAY  << " Admin/Check User/Search         " << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << " Enter Email for Search          " << RED << "||" << RESET << endl; 
    cout << RED  << "||" << RESET << "=================================" << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << " Email: " << YELLOW; getline(cin >> ws, email); cout << RESET; system("cls");
    while(temporary != NULL){
        if (temporary -> email == email){
            cout << GREEN;
            for (char i : temporary -> name){
                if (i == ' ') break;
                else cout << i;
            }
            cout << "'s Information" << RESET << endl;
            cout << GRAY << string(50, '-') << RESET << endl;
            cout << "Name: " << YELLOW << temporary -> name << RESET << endl;
            cout << "Gender: " << YELLOW << temporary -> gender << RESET << endl;
            cout << "Age: " << YELLOW << temporary -> age << RESET << endl;
            cout << "Role: " << YELLOW << temporary -> role << RESET << endl;
            cout << "Email: " << YELLOW << temporary -> email << RESET << endl;
            cout << "Phone: " << YELLOW << temporary -> phone << RESET << endl;
            cout << GRAY << string(50, '-') << RESET << endl;
            check = true;
            break;
        }
        temporary = temporary -> next;
    }
    if (!check) cout << RED << "Email not found!" << RESET << endl;
    cout << endl << GRAY; system("pause"); system("cls"); cout << RESET;
}

void admin_check_user_menu(Admin_List* list){
    system("cls");
    int option = 0;
    while(option != 4){
        cout << CYAN << "<===== " << GREEN << "Admin" << CYAN << " =======================>" << RESET << endl;
        cout << RED  << "||" << GRAY  << " Admin/Check User                " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << "---------------------------------" << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 1. Display                      " << RED << "||" << RESET << endl; 
        cout << RED  << "||" << RESET << " 2. Modify                       " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 3. Search                       " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 4. Back                         " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << "=================================" << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " Enter option: " << YELLOW; cin >> option; cout << RESET;
        switch (option){
            case 1:system("cls");admin_check_user_display_menu(list);break;
            case 2:system("cls");admin_check_user_modify_menu(list);break;
            case 3:system("cls");admin_check_user_search_menu(list);break;
            case 4:system("cls");break;
            default:system("cls");cout << RED << "Invalid Input" << RESET << endl;break;
        }
    }
}

void admin_exit(int time){
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

void admin_introduction(){
    cout << "Hello! Admin" << endl;
    cout << "Admin" << endl;
    int option = 0;
    Admin_List *Admin_List_User = create_new_admin_user_list();
    admin_get_all_users_from_csv(Admin_List_User, "Database/user.csv");
    system("cls");
    while (option != 4){
        admin_option(); cout << YELLOW; cin >> option; cout << RESET;
        switch (option){
            case 1: system("cls");admin_check_user_menu(Admin_List_User);break;
            case 4: system("cls"); break;
            case 5: system("cls"); admin_exit(3); break;
            default: system("cls"); cout << RED << "Invalid option" << RESET << endl; break;
        }
    }
}

