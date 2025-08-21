/*
Lambda functions are anonymous functions they can be defined inline, they are useful for short and concise operations. They do not require a name, they are mostly used in STL algorithms as callback functions.
Its syntax contains capture list, arguments, return type and function body, we can capture by either value or reference.
syntax:
[capture-list](parameters)->return-type{
    //definition
}
return-type is evaluated by the compiler itself, no need to specify it explicitly. However, in some complex cases the compiler cannot determine the return type and explicit specification is required.
capture-list captures external variables from the enclosing scope.
[&]: capture all external variables by reference.
[=]: capture all external variables by value.
[a,&b]: capture 'a' by value and 'b' by reference. 
*/

#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>
#include <functional>

class Test{
    public:
        Test(int value):x(value){

        } 
        
        int get() const{
            return x;
        }

        void set(int value){
            x = value;
        }
    private:
        int x{-1};
};

void test_func(std::function<void(int)> f){
    //function accepting argument as another function
    //with return type void and a single integer argument
    f(10);
}

int main(){
    //Example 1: lambda expression takes one integer as argument and return sum of the integer itself and prints the result.
    auto func = [](int x){
        return x+x;
    };
    std::cout<<func(5)<<std::endl;

    //Example 2: lambda expression captures variables by reference.
    int x=32,y=56;
    auto func_by_ref = [&](int z){
        x=x+z;//add z to x
        y=y-z;//subtract z from y
    };
    std::cout<<"values before[&] lambda function call x: "<<x<<",y: "<<y<<std::endl;
    func_by_ref(5);
    std::cout<<"values after[&] lambda function call x: "<<x<<",y: "<<y<<std::endl;

    //Example 3: lambda expression captures variables by values.
    auto func_by_val = [=](int z) mutable{
        //added mutable to allow modification of local copies of x,y, 
        //this is required because we are capturing variables by values 
        //not by reference so these are usaully read-only copies.
        //Eventhough we modify here it wont effecy outer values.
        x=x+z;//add z to x
        y=y-z;//subtract z from y
        std::cout<<"Inside[=] lambda func x: "<<x<<", y: "<<y<<std::endl;
    };
    func_by_val(10);
    std::cout<<"Outside[=] lambda func x: "<<x<<", y: "<<y<<std::endl;

    //Example 4: lambda expression with mixed capture list
    auto func_by_mixed = [x,&y](int z) mutable{
        x=x+z;//add z to x
        y=y-z;//subtract z from y
        std::cout<<"Inside mixed lambda func values x: "<<x<<", y: "<<y<<std::endl;
    };
    func_by_mixed(2);
    std::cout<<"Outer mixed lambda func values x: "<<x<<", y: "<<y<<std::endl;
    
    //Example 5: passing lambda function in threads
    auto thread_func = [&](int a, int b){
        std::cout<<"thread func executing a: "<<a<<", b: "<<b<<", x: "<<x<<", y: "<<y<<std::endl;
    };
    std::thread t1(thread_func,12,13);
    t1.join();
    //another approach
    std::thread t2([&](int a, int b){
        std::cout<<"thread executing a: "<<a<<", b: "<<b<<", x: "<<x<<", y: "<<y<<std::endl;
    },99,23);
    t2.join();

    //Example 6: lambdas with objects
    Test obj{56};
    std::cout<<"before value: "<<obj.get()<<std::endl;
    auto modify_object_val = [&obj](int new_val){
        obj.set(new_val);
    };
    modify_object_val(92);
    std::cout<<"after value: "<<obj.get()<<std::endl;

    //Example 7: lambdas with STL
    std::vector<int> values{43,13,82,98};
    int target = 82;
    auto find_itr = std::find_if(values.begin(),values.end(),[target](const int& v){
        return v == target;
    });
    if(find_itr != values.end())
        std::cout<<"target found"<<std::endl;
    else
        std::cout<<"target not found"<<std::endl;

    //Example 8: Passing lambda as callback function
    int m{20};
    test_func([m](int x){
        std::cout<<"x: "<<x+m<<std::endl;
    });
    return 0;
}