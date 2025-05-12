#include<iostream>
using namespace std;

struct Node{
    int data;
    Node *next;
};

struct SingleLinkedList{
    Node *head;
    Node *tail;
};

SingleLinkedList* createSingleLinkedList(){
    SingleLinkedList *list = new SingleLinkedList;
    list->head = nullptr;
    list->tail = nullptr;
    return list;
}

void insertAtHead(SingleLinkedList *list, int value){
    Node *newNode = new Node;
    newNode->data = value;
    newNode->next = list->head;
    list->head = newNode;
    if(list->tail == nullptr){
        list->tail = newNode;
    }
}

void insertAtTail(SingleLinkedList *list, int value){
    Node *newNode = new Node;
    newNode->data = value;
    newNode->next = nullptr;
    if(list->tail == nullptr){
        list->head = newNode;
        list->tail = newNode;
    }else{
        list->tail->next = newNode;
        list->tail = newNode;
    }
}

void deleteNode(SingleLinkedList *list, int value){
    Node *current = list->head;
    Node *previous = nullptr;
    while(current != nullptr && current->data != value){
        previous = current;
        current = current->next;
    }
    if(current == nullptr){
        cout << "Value not found in the list." << endl;
        return;
    }
    if(previous == nullptr){
        list->head = current->next;
    }else{
        previous->next = current->next;
    }
    if(current == list->tail){
        list->tail = previous;
    }
    delete current;
}

void displayList(SingleLinkedList *list){
    Node *current = list->head;
    while(current != nullptr){
        cout << current->data << " -> ";
        current = current->next;
    }
    cout << "nullptr" << endl;
}

