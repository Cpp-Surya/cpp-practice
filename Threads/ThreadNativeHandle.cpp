/*
std::thread::native_handle() Returns the OS specific implementation of thread handle. We can directly interact with platform-specific thread APIs.

*/
#include<thread>
#include<iostream>
#include<chrono>
#include<pthread.h>

void test_func(int id){
    pthread_setname_np("MyThread");
    std::cout<<"Executing func"<<std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout<<"Executed func"<<std::endl;
}

int main(){
    std::thread t1(test_func,1);
    //Returns pthread_t on Linux/Posix
    //Returns HANDLE on Windows/MSVC
    std::thread::native_handle_type thread_handle = t1.native_handle();
    t1.join();

    return 0;
}