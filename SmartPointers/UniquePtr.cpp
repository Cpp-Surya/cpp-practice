/*
Smart pointers are wrappers over a raw pointer that automatically manages memory, ensuring proper deallocation and preventing memory leaks.
Types of smart pointers
1. unique pointer: only one pointer can access object at a time.
2. shared pointer: multiple pointers can access and modify object, to track reference count is maintained.
3. weak pointer: 
*/

//A simple c++ program to demonstrate unique pointers usage.

#include <memory>
#include <iostream>

class Test{
    public:
        Test(int value):x(value){
            std::cout<<"Initialized test"<<std::endl;
        }

        ~Test(){
            std::cout<<"DeInitialized test"<<std::endl;
        }

        void set_value(int value){
            std::cout<<"updating value: "<<value<<std::endl;
            x = value;
        }

        int get_value(){
            return x;
        }

    private:
        int x;
};

void modifyvalue(std::unique_ptr<Test>& t){
    t->set_value(97);
}

int main(){
    std::unique_ptr<int> test_val = std::make_unique<int>(12);//pointer to an integer
    std::cout<<"access using * : "<<*test_val<<std::endl;
    std::unique_ptr<int[]> test_array = std::make_unique<int[]>(3);//pointer to an array of size 3 elements
    for(int i = 0; i<3; i++)
        test_array[i] = i;
    
    for(int i = 0; i<3; i++)
        std::cout<<test_array[i]<<" ";
    std::cout<<std::endl;
    std::unique_ptr<Test> t1 = std::make_unique<Test>(12);
    std::cout<<"Address of t1: "<<t1<<std::endl;
    std::cout<<"X: "<<t1->get_value()<<std::endl;
    t1->set_value(54);
    std::cout<<"X: "<<t1->get_value()<<std::endl;
    //Below declaration not allowed only single unique pointer can access a object at any given point of time
    //std::unique_ptr<Test> t2 = t1;
    //Below declaration is allowed 
    std::unique_ptr<Test> t2 = std::move(t1);

    //get() returns a raw pointer to the managed object.
    auto raw_ptr_obj_mngd_by_t2 = t2.get();
    std::cout<<"addr of object managed by t2: "<<raw_ptr_obj_mngd_by_t2<<std::endl;
    std::cout<<"address of t2: "<<t2.get()<<std::endl;//now t2 has Test object
    if(t1 == nullptr){
        std::cout<<"address of t1: "<<t1.get()<<std::endl;//t1 no longer points to Test object so address will be '0'
    }
    std::cout<<"access x using t2: "<<t2->get_value()<<std::endl;

    //release() returns a raw pointer to the managed object and releases the ownership.
    auto tmp = t2.release();// releases ownership and returns a raw pointer must be deleted
    if(t2 == nullptr)
        std::cout<<"t2 is null"<<std::endl;
    delete tmp;
    
    //reset() deletes the currently managed object.
    std::unique_ptr<Test> reset_test_ptr = std::make_unique<Test>(75);
    if(reset_test_ptr != nullptr)
        std::cout<<"before reset: pointer is not null"<<std::endl;
    reset_test_ptr.reset();
    if(reset_test_ptr == nullptr)
        std::cout<<"After reset: pointer is null"<<std::endl;
    
    //swap() swaps pointers
    std::unique_ptr<Test> ptr1 = std::make_unique<Test>(13);
    std::unique_ptr<Test> ptr2 = std::make_unique<Test>(66);
    std::cout<<"Before swap\nptr1 value: "<<ptr1->get_value();
    std::cout<<"\nptr2 value: "<<ptr2->get_value()<<std::endl;
    ptr1.swap(ptr2);
    std::cout<<"After swap\nptr1 value: "<<ptr1->get_value();
    std::cout<<"\nptr2 value: "<<ptr2->get_value()<<std::endl;

    //passing unique pointers as arguments to function, pass by reference
    std::unique_ptr<Test> t = std::make_unique<Test>(7);
    modifyvalue(t);
    std::cout<<t->get_value()<<std::endl;
    return 0;
}