/*
std::unique_lock is a mutex wrapper which supports deferred locking, time-constrained attempts at locking, recursive locking, transfer of lock ownership, and use with conditional variables. 
*/
#include<iostream>
#include<thread>
#include<mutex>
#include<condition_variable>
#include<string>
#include<exception>

std::mutex mtx;
std::condition_variable cv;
int shared_data{0};
std::timed_mutex time_mtx;
bool value_set{false};
bool ready{false};

void TestLockUnlock(const std::string& thread_name){
    std::unique_lock<std::mutex> lck(mtx);
    std::cout<<thread_name<<" Locked mutex first time"<<std::endl;
    for(int i=0;i<10;i++);
    std::cout<<thread_name<<" Releasing Lock first time"<<std::endl;
    lck.unlock();
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    lck.lock();
    std::cout<<thread_name<<" Locked mutex second time"<<std::endl;
    for(int i=0;i<10;i++);
    std::cout<<thread_name<<" Releasing Lock second time"<<std::endl;
    lck.unlock();
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
}

void TestTryLock(const std::string& thread_name){
    std::unique_lock<std::mutex> lck(mtx);
    //mutex is already locked, so try_lock should fail.
    try{
        lck.try_lock();
    }catch(const std::exception& e){
        std::cerr<<"expected lock failure -> "<<e.what()<<std::endl;
    }

    lck.unlock();
    //mutex is unlocked, so try_lock should succeed.
    if(lck.try_lock()){
        std::cout<<"Expected: Locking Succees"<<std::endl;
    }
}

void TestTryLockForWaiter(){
    /*Tries to lock mutex before timeout*/
    std::unique_lock<std::timed_mutex> lck(time_mtx,std::defer_lock);
    if(lck.try_lock_for(std::chrono::milliseconds(100))){
        std::cout<<"Waiter able to lock mutex in time"<<std::endl;
    }else{
        std::cout<<"Waiter failed to get lock in time"<<std::endl;
    }
}

void TestTryLockForProvider(){
    /*Locks mutex for sometime*/
    std::unique_lock<std::timed_mutex> lck(time_mtx,std::defer_lock);
    if(lck.try_lock_for(std::chrono::milliseconds(50))){
        std::cout<<"mutex locked by provider"<<std::endl;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

}

// condition variables allow threads to synchronize by using wait and notify functions
void TestConditionVariableProducer(){
    std::unique_lock<std::mutex> lck(mtx);
    for(int i=0;i<10;i++){
        cv.wait(lck,[]{return !value_set;});
        std::cout<<"Provider sending: "<<++shared_data<<std::endl;
        value_set = true;
        cv.notify_one();
    }

}

void TestConditionVariableConsumer(){
    std::unique_lock<std::mutex> lck(mtx);
    for(int i=0;i<10;i++){
        cv.wait(lck,[]{return value_set;});
        std::cout<<"Consumer receiving: "<<shared_data<<std::endl;
        value_set = false;
        cv.notify_one();
    }
}

void TestCVWaitFor(){
    std::unique_lock<std::mutex> lck(mtx);
    if(!cv.wait_for(lck,std::chrono::milliseconds(100),[]{return ready;})){
        std::cout<<"Timeout occured before lock"<<std::endl;
    }
}

int main(){
    std::thread thread_arr[6];
    for(int i=0;i<6;i++)
        thread_arr[i] = std::thread(TestLockUnlock,"Thread "+std::to_string(i));
    
    for(int i=0;i<6;i++)
        thread_arr[i].join();

    std::thread t1(TestTryLock,"Thread 1");
    t1.join();

    std::thread ProviderThread(TestTryLockForProvider);
    std::thread WaiterThread(TestTryLockForWaiter);
    ProviderThread.join();
    WaiterThread.join();

    shared_data = 0;
    std::thread prod(TestConditionVariableProducer);
    std::thread cons(TestConditionVariableConsumer);
    prod.join();
    cons.join();

    std::thread t2(TestCVWaitFor);
    t2.join();
    return 0;
}