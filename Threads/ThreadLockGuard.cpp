/*
std::lock_guard class is a mutex wrapper that owns a mutex for a defined block of code, After the block lock_guard object will be destroyed and mutex is released. 
*/

#include<iostream>
#include<thread>
#include<mutex>

std::mutex mtx;
//Lockguard ensures resources are released only after the lockguard object is destroyed(moves out of scope).
void TestLockGuard(const int thread_id){
    {
        std::lock_guard<std::mutex> lck(mtx);
        std::cout<<"Thread "<<thread_id<<" Executing Block 1"<<std::endl;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    {
        std::lock_guard<std::mutex> lck(mtx);
        std::cout<<"Thread "<<thread_id<<" Executing Block 2"<<std::endl;
    }
}

int main(){
    std::thread t1(TestLockGuard,1);
    std::thread t2(TestLockGuard,2);
    std::thread t3(TestLockGuard,3);
    t1.join();
    t2.join();
    t3.join();
    return 0;
}