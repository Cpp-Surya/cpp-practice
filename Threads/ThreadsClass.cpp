/*
Accessing member functions using threads
*/

#include<thread>
#include<iostream>
#include<condition_variable>
#include<mutex>
#include<chrono>

class TestThreads{
    public:
        TestThreads(const std::string& name):object_name(name){
        }

        void func1(const int& x){
            std::lock_guard<std::mutex> lck(mtx);
            //std::lock_guard<std::mutex> lck(TestThreads::static_mtx);
            for(int i=0;i<x;i++){
                std::cout<<object_name<<" func1 count: "<<i<<std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
            }
        }

        void func2(const int& y){
            std::lock_guard<std::mutex> lck(mtx);
            //std::lock_guard<std::mutex> lck(TestThreads::static_mtx);
            for(int i=0;i<y;i++){
                std::cout<<object_name<<" func2 count: "<<i<<std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
            }
        }

        static std::mutex static_mtx;
    private:
        std::string object_name;
        std::mutex mtx;
        std::condition_variable cv;
};

std::mutex TestThreads::static_mtx;// static member variables must be defined outside class

int main(){
    //create two objects obj1,obj2. start threads for func1 and func2.
    TestThreads obj1("obj1");
    TestThreads obj2("obj2");
    
    std::thread t1(&TestThreads::func1,&obj1,5);
    std::thread t2(&TestThreads::func2,&obj1,5);
    std::thread t3(&TestThreads::func1,&obj2,5);
    std::thread t4(&TestThreads::func2,&obj2,5);
    //for object1 either func1 or func2 will start, if func 1 is started first func2 
    //will be blocked until func1 completes vice-versa if func2 is started. 
    //This is because of object1 is sharing same mutex.
    //for object2 same thing will happen but object2 functions and obj1 functions execute
    //parallely since object1 and object 2 have different mutexs. Here object1 mutex
    //is restricted to itself not linked with object2 since they are both seperate entities.
    //If we try to use static mutex variable, it will restrict all functions to execute 
    //one after other because static variables are belongs to whole class not to any specific object,
    //This will block all other threads

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    return 0;
}