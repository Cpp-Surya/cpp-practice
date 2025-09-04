/*
auto: auto keyword automatically deduces type of the variable, it should be initialized at the time of declaration.. It is useful for type deducing long and complex datatypes.
Range based for loop: Range based for loop iterate over a range, this range can be anything which can be iteratable such as arrays, vectors, maps and soon.
Nullptr: Using nullptr we can write safer code this is especially useful for overloaded functions.
*/

#include <iostream>
#include <vector>
#include <map>
#include <string>

struct Data{
    int v1;
    float v2;
    Data(int value1, float value2):v1(value1),v2(value2){}
};

//auto as parameter in a function allowed from C++20
void func(auto y){
    std::cout<<"argument_type: "<<typeid(y).name()<<std::endl; 
}

//auto as return Type allowed from C++14
auto get_int(){
    return 10;
}

auto get_double(){
    return 3.14;
}

auto get_struct(){
    return Data(11,76.8);
}

//Nullptr test function null_test()
void null_test(int value){
    std::cout<<"int is called"<<std::endl;
}

void null_test(const char* ptr){
    std::cout<<"pointer is called"<<std::endl;
}

int main()
{
    {
        //Auto keyword examples
        auto value = 20;//datatype deduction for a variable introduced from C++11
        std::cout<<"Type: "<<typeid(value).name()<<", value: "<<value<<std::endl;//should print i for type since 20 is a integer
        auto complex_data = Data(187,9.7);
        std::cout<<"Type: "<<typeid(complex_data).name()<<", v1: "<<complex_data.v1<<", v2: "<<complex_data.v2<<std::endl;//should print structure name
    
        std::vector<int> v{1,2,3,4,5};
        std::vector<int>::iterator it = v.begin();// instead of this we can simply use auto to deduce type
        auto it2 = v.begin();
        if(it == it2)
            std::cout<<"both have same values"<<std::endl;
        
        //parameter type deduction
        func(11);
        func(23.5);
        func('b');
        func("Monkey.D.Luffy");
        func(complex_data);
        
        //Return type deduction
        std::cout<<"return_type: "<<typeid(get_int()).name()<<std::endl;
        std::cout<<"return_type: "<<typeid(get_double()).name()<<std::endl;
        std::cout<<"return_type: "<<typeid(get_struct()).name()<<std::endl;
    }
    
    {
        //Range based for loop examples
        int arr[] = {7,2,11,45,10};
        for(auto& i : arr)//iterate over a array
            std::cout<<i<<"\n";
            
        std::vector<char> char_vec{'v','a','r'};
        for(auto& ch : char_vec)//iterate over vector
            std::cout<<ch<<std::endl;
            
        std::map<int,std::string> num_map{{1,"one"},{2,"two"},{3,"three"},{4,"four"},{5,"five"}};
        for(auto& n : num_map)
            std::cout<<"numerical value: "<<n.first<<", string value: "<<n.second<<std::endl;
    }
    
    {
        //Nullptr usage
        //null_test(NULL);//compiler will be confused which function to call
        null_test(nullptr);//This resolves the above issue
        
    }

    return 0;
}