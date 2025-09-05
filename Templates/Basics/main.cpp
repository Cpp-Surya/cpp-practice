/*
Templates: Using Templates we can write generic programming, we dont need to define for each data type. 
We can create a template and use it for all datatypes.
*/

#include <iostream>

//Function template
//Compiler will generate a function for each type when needed. This process is called instantiation.
template <typename Type>
Type add(Type a, Type b){
    return a+b;
}

//Class template
//Compiler will generate a different class definition for each type used.
template<typename Type>
class Test{
    private:
        Type value;
    public:
        Test(Type v):value(v){
            
        }

        Type get() {
            return value;
        }
};

int main()
{
    {
        //Function template
        auto result1 = add(11,12);//instantiates add(int,int)
        std::cout<<"Type: "<<typeid(result1).name()<<", result1: "<<result1<<std::endl;
        
        auto result2 = add(2.3,4.3);//instantiates add(double,double)
        std::cout<<"Type: "<<typeid(result2).name()<<", result2: "<<result2<<std::endl;
    }
    
    {
        //Class template
        Test<int> t1(12);
        Test<double> t2(65.7);
        Test<char> t3('S');
        std::cout<<"Int: "<<t1.get()<<std::endl;
        std::cout<<"Double: "<<t2.get()<<std::endl;
        std::cout<<"Char: "<<t3.get()<<std::endl;
    }
    return 0;
}