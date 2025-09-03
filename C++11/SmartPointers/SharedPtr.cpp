/*
Smart pointers are wrappers over a raw pointer that automatically manages memory, ensuring proper deallocation and preventing memory leaks.
Types of smart pointers
1. unique pointer: only one pointer can access object at a time.
2. shared pointer: multiple pointers can access and modify object, to track reference count is maintained.
3. weak pointer: this pointer takes reference to shared pointer except it doesnt maintain a reference count. It should be converted to shared pointer in order to access the referenced object.
*/

//A simple c++ program to demonstrate shared pointer usage.

#include <memory>
#include <iostream>

void test_func(std::shared_ptr<int>& p){
    *p = 87;
}

void test_func2(std::shared_ptr<int> p){
    *p = 99;
}

int main(){
    std::shared_ptr<int> i_ptr1 = std::make_shared<int>(12);
    std::cout<<"accessing using *: "<<*i_ptr1<<std::endl;
    std::cout<<"ptr1 ref count: "<<i_ptr1.use_count()<<" should be 1"<<std::endl;
    std::shared_ptr<int> i_ptr2 = i_ptr1;
    std::cout<<"ptr1 ref count: "<<i_ptr1.use_count()<<" should be 2"<<std::endl;
    std::cout<<"addr i_ptr: "<<i_ptr1<<std::endl;
    std::cout<<"addr i_ptr2: "<<i_ptr2<<std::endl;
    std::cout<<"i_ptr1 value: "<<*i_ptr1<<"\ni_ptr2 value: "<<*i_ptr2<<std::endl;
    int new_val = 86;
    *i_ptr2 = new_val;
    //ptr1 value will also modify.
    std::cout<<"i_ptr2 updated\ni_ptr1 value: "<<*i_ptr1<<"\ni_ptr2 value: "<<*i_ptr2<<std::endl;
    
    //reset(raw pointer) removes current object and replaces with new object.
    i_ptr1.reset(new int(54));
    std::cout<<"i_ptr1 resetted\ni_ptr1 addr: "<<i_ptr1<<", i_ptr1 value: "<<*i_ptr1<<", i_ptr1 ref count: "<<i_ptr1.use_count()
    <<"\ni_ptr2 addr: "<<i_ptr2<<", i_ptr2 value: "<<*i_ptr2<<", i_ptr2 ref count: "<<i_ptr2.use_count()<<std::endl;
    //reset() deletes current managing object
    i_ptr1.reset();
    if(i_ptr1 == nullptr)
        std::cout<<"i_ptr1 is resetted so it should be null"<<std::endl;
    
    //unique() checks object is managed by only single shared_ptr.
    if(i_ptr2.unique())
        std::cout<<"i_ptr2 is managed by only one pointer"<<std::endl;
    std::shared_ptr<int> i_ptr3 = i_ptr2;//new pointer pointing to same object
    if(!i_ptr2.unique())
        std::cout<<"i_ptr2 is managed by multiple pointers"<<std::endl;
    
    //get() returns the stored pointer
    auto raw_ptr = i_ptr3.get();
    std::cout<<"raw_ptr: "<<*raw_ptr<<", ref count i_ptr3: "<<i_ptr3.use_count()<<std::endl;
    
    //swap() swaps two pointers
    std::shared_ptr<int> new_ptr = std::make_shared<int>(102);
    std::cout<<"Before swap\ni_ptr3: "<<*i_ptr3<<"\nnew_ptr: "<<*new_ptr<<std::endl;
    i_ptr3.swap(new_ptr);
    std::cout<<"After swap\ni_ptr3: "<<*i_ptr3<<"\nnew_ptr: "<<*new_ptr<<std::endl;

    //pass by reference
    test_func(i_ptr3);
    std::cout<<"After test_func call i_ptr3: "<<*i_ptr3<<", ref count: "<<i_ptr3.use_count()<<std::endl;
    
    //pass by value
    test_func2(i_ptr3);
    std::cout<<"After test_func2 call i_ptr3: "<<*i_ptr3<<", ref count: "<<i_ptr3.use_count()<<std::endl;
    return 0;
}