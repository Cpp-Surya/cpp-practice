/*
Linked list: Linked list is a linear data structure which has sequence of nodes each node stores data and address of next node{data,next node}.
Linked list are dynamic(no fixed size).
*/

#include <iostream>

struct Node{
    int data;
    Node* next;
    Node():data(0),next(nullptr){}
    Node(int value):data(value),next(nullptr){}
};

void printList(Node* head){
    Node* temp = head;
    while(temp != nullptr){
        std::cout<<temp->data<<" ";
        temp = temp->next;
    }
    std::cout<<std::endl;
}

void pushFront(Node*& head, int value){
    Node* new_node = new Node(value);
    new_node->next = head;
    head = new_node;
}

void pushBack(Node*& head, int value){
    Node* new_node = new Node(value);
    if(head == nullptr){
        head = new_node;
        return;
    }

    Node* temp = head;
    while(temp->next != nullptr){
        temp = temp->next;
    }
    temp->next = new_node;
}

int main() {
    //initialize head with null
    Node* head = nullptr;
    //create nodes individually
    Node* first = new Node(1);
    Node* second = new Node(2);
    Node* third = new Node(3);
    Node* fourth = new Node(4);
    //Link nodes
    first->next = second;
    second->next = third;
    third->next = fourth;
    //store first in head
    head = first;//head points to first node
    //Traverse list
    printList(head);
    //add element at start
    pushFront(head,78);
    pushFront(head,64);
    printList(head);
    pushBack(head,100);
    pushBack(head,43);
    printList(head);
    return 0;
}

