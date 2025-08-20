/*
Smart pointers are wrappers over a raw pointer that automatically manages memory, ensuring proper deallocation and preventing memory leaks.
Types of smart pointers
1. unique pointer: only one pointer can access object at a time.
2. shared pointer: multiple pointers can access and modify object, to track reference count is maintained.
3. weak pointer: this pointer takes reference to shared pointer except it doesnt maintain a reference count. It should be converted to shared pointer in order to access the referenced object.
*/

//A simple c++ program to demonstrate weak pointer usage.

#include <memory>
#include <iostream>

int main(){
    std::shared_ptr<int> shared_p1 = std::make_shared<int>(99);
    std::shared_ptr<int> shared_p2 = shared_p1;
    std::cout<<"ref count: "<<shared_p1.use_count()<<std::endl;
    std::weak_ptr<int> wk_ptr = shared_p1;

    //expired() checkes whether the referenced object is already destroyed or not
    if(!wk_ptr.expired())
        std::cout<<"object is still alive"<<std::endl;
    
    //lock() returns a copy of shared pointer the weak pointer is referring
    auto new_sh_p = wk_ptr.lock();
    std::cout<<"ref count: "<<shared_p1.use_count()<<std::endl;
    shared_p1.reset();
    shared_p2.reset();
    new_sh_p.reset();
    if(wk_ptr.expired())
        std::cout<<"object is destroyed"<<std::endl;
    
    return 0;
}