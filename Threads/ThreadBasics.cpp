/*
Multithreading: Concurrent execution of sub parts of the program for maximum maximum utilization of cpu. Each part of such program are called thread. So threads are lightweight processess within a process.

Thread synchronization primitives:
Mutexes: Mutexes ensure only single thread can access a shared resource in multithreaded environment at any given point of time.
Condition variables: Condition variables pauses threads from furthur processing until specified conditions becomes true.
Atomic operations: Allows access to shared resource without any explicit locking.

MultiThreading Issues:
Race conditions: When 2 or more threads try to access shared resources in multithreaded environment causes resource corruption such condition is called race condition. It can be avoided using mutexes, condition variables or atomic operations.
Deadlocks: When 2 or more threads blocked indefinitely waiting for other threads to release resource such condition is called deadlock. I can be avoided using mutexes, condition variables, atomic operations.
*/

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

std::mutex mtx;

void func(int thread_id){
    std::lock_guard<std::mutex> lck(mtx);//Locks shared resource and ensures only single thread is allowed at a time.
    std::cout<<"Thread "<<thread_id<<" Executing"<<std::endl;
    std::cout<<"sleep thread for 500 ms"<<std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout<<"Thread "<<thread_id<<" completed"<<std::endl;
}

void test(){
    std::lock_guard<std::mutex> lck(mtx);
    std::cout<<"Test execution"<<std::endl;
}


int main(){
    int thread_count{0};
    std::thread t1(func,++thread_count);//thread creation
    std::thread t2(func,++thread_count);
    t1.join();//execution blocks here until thread 1 joins
    t2.join();

    //array of threads
    std::thread threads_array[5];
    int i{0};
    for(i=0;i<5;i++)
        threads_array[i] = std::thread(func,++thread_count);
    for(i=0;i<5;i++)
        threads_array[i].join();

    std::thread t3(func,++thread_count);
    std::cout<<"Thread id: "<<t3.get_id()<<std::endl;// gets internal thread id
    if(t3.joinable()){// Checks thread is in parallel execution or not
        std::cout<<"Thread is joinable"<<std::endl;
        t3.join();
    }
    else{
        std::cout<<"Thread is not in running state"<<std::endl;
    }

    std::thread t4(func,++thread_count);
    t4.detach();//detaches the thread and executes independently from main thread

    std::thread t5(test);
    std::thread t6(test);
    std::cout<<"Thread ids before swap t5: "<<t5.get_id()<<", t6: "<<t6.get_id()<<std::endl;
    t5.swap(t6);//swaps threads we can verify by printing thread ids
    std::cout<<"Thread ids after swap t5: "<<t5.get_id()<<", t6: "<<t6.get_id()<<std::endl;
    t5.join();
    t6.join();
    std::thread t7(func,++thread_count);
    std::cout<<"t7 id before move: "<<t7.get_id()<<std::endl;
    std::thread t8 = std::move(t7);//moves t7 to t8 leaves t7 in default state
    std::cout<<"t7 id after move: "<<t7.get_id()<<std::endl;
    std::cout<<"t8 id: "<<t8.get_id()<<std::endl;
    t8.join();
    std::cout<<"No of concurrent threads supported: "<<std::thread::hardware_concurrency()<<std::endl;// returns how many no of concurrent threads supported
    return 0;
}
