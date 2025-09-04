/*
Generic lambdas: Allows parameters can be declared with auto keyword, enabling it to work with different datatypes
*/

#include <iostream>
#include <vector>
#include <algorithm>

class Test{
    public:
        int value;
        Test(int x):value(x){}
        
        ~Test(){}
        
        Test operator+(const Test& other){
            return Test(this->value+other.value);
        }
};


int main()
{
    {
        //Lambda functions with auto parameters
        auto func1 = [](auto x, auto y){
            std::cout<<"arg1_type: "<<typeid(x).name()<<", arg2_type: "<<typeid(y).name()<<std::endl;
            return x+y; 
        };
        auto result1 = func1(11,12);
        std::cout<<"return_type: "<<typeid(result1).name()<<", Value: "<<result1<<std::endl;
        auto result2 = func1(99.12,8);
        std::cout<<"return_type: "<<typeid(result2).name()<<", Value: "<<result2<<std::endl;
        Test t1(80),t2(10);
        auto result3 = func1(t1,t2);
        std::cout<<"return_type: "<<typeid(result3).name()<<", Value: "<<result3.value<<std::endl;
    }
    {
        //Lambda functions in algorithms
        Test t1(11),t2(54),t3(78),t4(99),t5(176);
        std::vector<Test> test_vec{t1,t2,t3,t4,t5};
        //find test object which has value 78
        int target_value = 78;
        auto find_itr = std::find_if(test_vec.begin(),test_vec.end(),[&](auto& t)/*(Test& t)*/{//automatically deduce datatype and passes as parameter to lambda function
            return t.value == target_value;
        });
        
        if(find_itr != test_vec.end())
            std::cout<<"Target found"<<std::endl;
    }
    
    return 0;
}