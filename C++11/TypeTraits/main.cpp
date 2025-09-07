/*
TypeTraits: Typetraits checks about types at compile time and allows them to manipulate. This provides safest and fastest code path before runtime.
- Ensures templates are used only for valid types at compile time
- Allows conditional compilation
- Type transformation
Constexpression: constexpr tells compiler that a value, variable or functions will be evaluated at compile time if possible. If it cannot be evaluated at compile time it can still be evaluated at runtime.
*/

#include <iostream>
#include <type_traits>

//Template validation for specified types
template <typename T1,typename T2>
double average(T1 x,T2 y){
    static_assert(std::is_arithmetic<T1>::value && std::is_arithmetic<T2>::value,"average() requires numeric arguments");//ensures only numeric data is passed as args, avoids strings and other non-numeric values as args.
    return (x+y)/2;
}

//Conditional compilation
template <typename T>
void print_info(const T& x){
    if constexpr(std::is_pointer<T>::value){
        //This branch exists after compilation if T is a pointer.
        std::cout<<"Pointer to value: "<<*x<<std::endl;
    }else{
        //Otherwise this branch exists-no runtime overhead
        std::cout<<"value: "<<x<<std::endl;
    }
}

//enables only when a type meets a condition
template <typename T> 
typename std::enable_if<std::is_arithmetic<T>::value,T>::type
 add_one(T x){
    return x+1;
}

template <typename T, typename std::enable_if<std::is_arithmetic<T>::value,int>::type=0>
T subtract_one(T x){
    return x-1;
}

template <typename T, typename std::enable_if<std::is_arithmetic<T>::value,int>::type>
void divide_by_one(T x){
    std::cout<<"division: "<<x/1<<std::endl;
}

//Type transformations
void type_transform(){
    using T1 = std::remove_const<const int>::type;
    std::cout<<std::boolalpha<<std::is_same<T1,int>::value<<"\n";

    using T2 = std::remove_pointer<int*>::type;
    T2 x = 12;
    std::cout<<"x type: "<<typeid(x).name()<<"\n";
    using T3 = std::add_pointer<int>::type;
    T3 y = &x;
    std::cout<<"y type: "<<typeid(y).name()<<"\n";
}

int main()
{
    std::cout<<average(11,12)<<std::endl;
    //average("string",'c');//gives compilation error
    std::cout<<average(11.3,34.567)<<std::endl;

    int* ptr = new int(16);
    print_info(ptr);
    delete ptr;
    print_info(12);
    print_info("string");
    std::cout<<add_one(12)<<std::endl;
    std::cout<<add_one(12.5)<<std::endl;
    std::cout<<subtract_one(10)<<"\n";
    divide_by_one<int,0>(45);
    type_transform();
    return 0;
}