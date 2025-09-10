/*
SFINAE: Substitution failure is not an error, enable/disable code based on type.
Variadic templates allows to write functions or classes that accept any number of template parameters.
*/
#include <iostream>
#include <type_traits>
#include <string>
#include <concepts>

//SFINAE This function only invokes if arguments are either integers, or floating point values
template<typename T1, typename T2>
typename std::enable_if<std::is_arithmetic<T1>::value && std::is_arithmetic<T2>::value,double>::type
add(T1 a, T2 b){
    return a+b;
}

//This function template only accepts integers as arguments
template<typename T>
typename std::enable_if<std::is_integral<T>::value,std::string>::type
get(T value){
    std::string out = "value is : "+std::to_string(value);
    return out;
}

//variadic templates(... means zero or more arguments)
template <typename... Args>
void printAll(Args... args){
    (std::cout<<...<<args)<<"\n";//fold expression
}

//variadic templates
void printallargs() {}//base case

template <typename T, typename... Args>
void printallargs(T first,Args... rest){
    auto x = first;
    std::cout<<"data: "<<x<<", type: "<<typeid(x).name()<<std::endl;
    printallargs(rest...);
}

//Concepts C++20- cleaner constraints
template<std::integral T>
T sum(T a, T b)
{
    return a+b;
}

int main()
{
    std::cout<<add<int,int>(11,12)<<"\n";
    std::cout<<add<int,double>(10,12.35)<<"\n";
    std::cout<<add<float,int>(1.2,1)<<"\n";
    //std::cout<<add<std::string,int>(1,1)<<"\n";//compilation will fail because this type is deleted
    std::cout<<get(11)<<"\n";
    //std::cout<<get(99.999)<<"\n";//double as a argument is disabled
    printAll(11,"tests",7.81,'c',-1);
    printallargs('a','b',1,"ghs",12.456);
    std::cout<<sum(8,2)<<std::endl;
    //std::cout<<sum(8.5,2.5)<<std::endl;//fails supports only integer arguments
    return 0;
}