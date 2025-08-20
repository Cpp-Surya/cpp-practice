/*
Move Semantics: move semantics transfers ownership of resources from a temporary or expiring object to a new object.
This transfer avoids expensive copies, especially beneficial for objects managing large amounts of data.
Key components:
Rvalue references(&&): These are new type of reference that binds to temporary objects(rvalues) or objects explicitly cast to rvalues using std::move. They are crucial for distinguishing between objects that can be moved from and those that must be copied.
Move constructor: A constructor that takes an rvalue reference to an object and transfers its resources to the newly constructed object.
Move assignment operator: An overloaded assignment operator that takes an rvalue reference and transfers resources from the source object to the target object. It reassigns pointers and nullifies the sources pointers.
std::move: A utility function that explicitly casts an lvalue to an rvalue reference, enabling the use of move constructors and move assignment operators in situations where the objects lifetime is ending or its resources are no longer needed.
*/

#include <iostream>
#include <utility>

void test_(int& i) {
    //std::cout << "pass by lvalue reference triggered" << std::endl;
}

void test_(int&& i) {
    //std::cout << "rvalue triggered" << std::endl;
}

class Test{
    public:
        Test(){

        }

        Test(int x):value(x){
            std::cout<<"Param ctr called"<<std::endl;
        }

        ~Test(){
            //std::cout<<"Destructor called"<<std::endl;
        }

        Test(const Test& other){
            std::cout<<"Copy ctr called"<<std::endl;
            this->value = other.value;
        }

        Test& operator=(const Test& other){
            std::cout<<"Copy assign called"<<std::endl;
            if(this != &other){
                this->value = other.value;
            }
            return *this;
        }

        Test(Test&& other) noexcept{
            std::cout<<"Move ctr called"<<std::endl;
            this->value = other.value;
            other.value = -1;//setting default value
        }

        Test& operator=(Test&& other) noexcept{
            std::cout<<"move assign called"<<std::endl;
            if(this != &other){
                this->value = other.value;
                other.value = -1;
            }
            return *this;
        }
    
    private:
        int value{-1};
};

int main() {
    int x = 5;

    test_(x);//should trigger test_(int& i)
    test_(11);//should trigger test_(int&& i)
    test_(std::move(x));//should trigger test_(int&& i)

    Test t1(12);//should trigger param ctr
    Test t2(t1);//should trigger copy ctr
    Test t3(std::move(t2));//should trigger move ctr
    Test t4;
    t4 = t3;//should trigger copy assign
    Test t5;
    t5 = std::move(t4);//should trigger move assign
    return 0;
}

