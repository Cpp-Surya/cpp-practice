#include <iostream>

struct Node{
    int data;
    Node* next;
    Node(int val):data(val),next(nullptr){}
};

void push_back(Node*& head, int value){
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

void print_list(Node*& head){
    if(head == nullptr){
        std::cout<<"List is empty"<<std::endl;
        return;
    }
    
    Node* temp = head;
    while(temp != nullptr){
        std::cout<<temp->data<<" ";
        temp = temp->next;
    }
    std::cout<<"\n";
}

//operations on linked list
//Delete a value in list
void delete_by_value(Node*& head,int target){
    std::cout<<"target to delete: "<<target<<std::endl;
    if(head == nullptr){
        return;
    }
    
    if(head->data == target){
        Node* temp = head;
        head = head->next;
        delete temp;
        return;
    }
    
    Node* temp = head;
    while(temp->next != nullptr && temp->next->data != target){
        temp = temp->next;
    }
    
    if(temp->next != nullptr){
        Node* delete_node = temp->next;
        temp->next = temp->next->next;
        delete delete_node;
    }
}

//Delete all values
void delete_all(Node*& head){
    while(head != nullptr){
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

//find element in list
bool find_element(Node*& head, int element){
    Node* temp = head;
    bool found{false};
    while(temp != nullptr){
        if(temp->data == element){
            found = true;
            break;
        }
        temp=temp->next;
    }
    
    return found;
}

int main()
{
    Node* head = nullptr;
    push_back(head,20);
    print_list(head);
    delete_by_value(head,40);
    print_list(head);
    push_back(head,30);
    push_back(head,40);
    push_back(head,50);
    push_back(head,60);
    print_list(head);
    delete_by_value(head,20);
    print_list(head);
    delete_by_value(head,40);
    print_list(head);
    //delete_all(head);
    print_list(head);
    for(int t = 10;t<80;t=t+10){
        find_element(head,t) ? (std::cout<<"Found: "<<t<<"\n") : (std::cout<<"Not Found: "<<t<<"\n");
    }
    return 0;
}