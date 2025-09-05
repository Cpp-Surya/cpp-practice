#include <iostream>
#include <string>

//overloading with templates
//Invokes when called with integer argument
void print(int x){
    std::cout<<"int: "<<x<<std::endl;
}

//Invoked when called with string argument
void print(std::string str){
    std::cout<<"string: "<<str<<std::endl;
}

template<typename Type>
void print (Type x){
    std::cout<<"template: "<<x<<std::endl;
}

//Multiple parameters
template<typename Type1, typename Type2>
auto multiply(Type1 x,Type2 y){
    return x*y;
}

//Non-Type template parameters
//Templates don't only take types, they can take values tool
template<int N>
int sum_of_array_elements(int arr[N]){
    int sum = 0;
    for(int i = 0;i < N;i++){
        sum = sum + arr[i];
    }
    return sum;
}

//Specialization
//Different behaviour for specific types.
template<typename Type>
class Printer{
    public:
        void print(Type value){
            std::cout<<value<<std::endl;
        }
};

template<>
class Printer<bool>{
    public:
        void print(bool value){
            std::cout<<(value ? "true" : "false")<<std::endl;
        }
};

int main()
{
    {
        //Overloading with templates
        print(11);//invokes void print(int x)
        print<int>(11);//This will specifically invoke template function
        print(std::string("Test string"));//invokes void print(std::string str)
        print('c');//invokes void print (Type x)
        print(98.2);//invokes void print (Type x)
    }
    
    {
        //Multiple parameters
        for(int i = 1; i<=10 ;i++){
            std::cout<<"10 x "<<i<<" = "<<multiply(10,i)<<std::endl;
        }
    }
    
    {
        //Non-type template parameters
        int arr[5] = {2,5,7,1,9};
        std::cout<<"Sum of array elements: "<<sum_of_array_elements<5>(arr)<<std::endl;
    }
    
    {
        //Specialization
        Printer<int> p1;
        p1.print(10);
        Printer<std::string> p2;
        p2.print("Test");
        Printer<double> p3;
        p3.print(123.456);
        Printer<bool> p4;
        p4.print(true);
    }
    
    return 0;
}