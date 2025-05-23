#include<iostream>
#include "function/login.h"
#include "Routes/admin.h"
#include "Routes/cashier.h"
#include "Routes/customer.h"
#include "Routes/manager.h"
using namespace std;

enum ROLE{
    CUSTOMER = 1,
    CASHIER,
    MANAGER,
    ADMIN
};

int main(){
    while(true){
        switch(login()){
            case CUSTOMER:customer_introduction();break;
            case CASHIER:cashier_introduction();break;
            case MANAGER:manager_introduction();break;
            case ADMIN:admin_introduction();break;
        }       
    }
}