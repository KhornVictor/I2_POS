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

void Admin_insert_user_end(Admin_List *list, char gender, string name, int age, string phone, string role, string email, string password){
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

            Admin_insert_user_end(s, gender, name, age, phone, role, email, password);
        }
        file.close();
    }
}

void admin_option(){
    cout << CYAN << "<===== " << GREEN << "Admin" << CYAN << " =======================>" << RESET << endl;
    cout << RED  << "||" << RESET << " Admin welcome                   " << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << " 1. Check User                   " << RED << "||" << RESET << endl; 
    cout << RED  << "||" << RESET << " 2. Check Product                " << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << " 3. Check Login                  " << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << " 4. Logout                       " << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << " 5. Exit                         " << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << "=================================" << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << " Enter option: ";
    
}


void admin_display_user_table(Admin_List* list) {
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
    cout << GRAY; system("pause"); cout << RESET << endl;
    system("cls");
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
        cout << RED  << "||" << RESET << " Admin welcome                   " << RED << "||" << RESET << endl;
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
            case 1:system("cls");admin_display_user_table(list);break;
            case 2:system("cls");admin_check_user_display_age_menu(list);break;
            case 3:system("cls");admin_check_user_display_gender_menu(list);break;
            case 4:system("cls");admin_check_user_display_role_menu(list, "admin");break;
            case 5:system("cls");admin_check_user_display_role_menu(list, "manager");break;
            case 6:system("cls");admin_check_user_display_role_menu(list, "customer");break;
            case 7:system("cls");admin_check_user_display_role_menu(list, "cashier");break;
            case 8:system("cls");admin_display_user_email_password(list);break;
            case 9:system("cls");break;
            default:break;
        }
    }
}

void admin_check_user_menu(Admin_List* list){
    system("cls");
    int option = 0;
    while(option != 4){
        cout << CYAN << "<===== " << GREEN << "Admin" << CYAN << " =======================>" << RESET << endl;
        cout << RED  << "||" << RESET << " Admin welcome                   " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 1. Display                      " << RED << "||" << RESET << endl; 
        cout << RED  << "||" << RESET << " 2. Modify                       " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 3. Search                       " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 4. Back                         " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << "=================================" << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " Enter option: " << YELLOW; cin >> option; cout << RESET;
        switch (option){
            case 1:system("cls");admin_check_user_display_menu(list);break;
            case 4:system("cls");break;
            default:break;
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

