#include<iostream>

struct Node{
    int data;
    Node* next;
};

struct Queue{
    Node* front;
    Node* rear;
};

Queue* createQueue(){
    Queue* q = new Queue;
    q->front = nullptr;
    q->rear = nullptr;
    return q;
}

void enqueue(Queue* q, int value){
    Node* newNode = new Node;
    newNode->data = value;
    newNode->next = nullptr;
    if(q->rear == nullptr){
        q->front = newNode;
        q->rear = newNode;
    }else{
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

void dequeue(Queue* q){
    if(q->front == nullptr){
        std::cout << "Queue is empty" << std::endl;
        return;
    }
    Node* temp = q->front;
    q->front = q->front->next;
    if(q->front == nullptr){
        q->rear = nullptr;
    }
    delete temp;
}