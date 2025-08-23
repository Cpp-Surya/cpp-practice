/*
std::thread::native_handle() Returns the OS specific implementation of thread handle. We can directly interact with platform-specific thread APIs.
ThreadNaming: Set thread names for easier debugging.
ThreadPriority: Set thread priorities to influence scheduling.
ThreadAffinity: Pin threads to specific CPU cores for performance optimization.
*/
#include<thread>
#include<iostream>
#include<chrono>
#include<pthread.h>
#include<string>
#include<sched.h>

void ThreadNamingTest(int id){
    std::cout<<"Executing func"<<std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout<<"Executed func"<<std::endl;
}

void ThreadPriorityTest(const std::string &name){
    for(int i=0;i<5;i++){
        std::cout<<"Thread Name: "<<name<<" - Iteration: "<<i<<std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

void ThreadAffinityTest(){
    std::cout<<"Thread Affinity Test"<<std::endl;
}

int main(){
    //Thread Naming
    std::thread t1(ThreadNamingTest,1);
    //Returns pthread_t on Linux/Posix
    //Returns HANDLE on Windows/MSVC
    std::thread::native_handle_type thread_handle = t1.native_handle();
    pthread_setname_np(thread_handle,"MyThread");//sets thread name on Linux/Posix
    //SetThreadDescription(thread_handle,L"MyThread");//sets thread name on Windows/MSVC
    t1.join();

    //Thread Priority
    std::thread t2(ThreadPriorityTest,"LowPriority");
    std::thread t3(ThreadPriorityTest,"HighPriority");
    auto thread2_handle = t2.native_handle();
    auto thread3_handle = t3.native_handle();
    sched_param sch;
    int policy;
    pthread_getschedparam(thread2_handle,&policy,&sch);//gets current thread priority on Linux
    std::cout<<"Current Thread 2 Priority Before: "<<sch.sched_priority<<std::endl;
    sch.sched_priority = sched_get_priority_max(SCHED_FIFO);
    pthread_setschedparam(thread2_handle,SCHED_FIFO,&sch);//sets thread priority on Linux
    std::cout<<"Current Thread 2 Priority After: "<<sch.sched_priority<<std::endl;

    pthread_getschedparam(thread3_handle,&policy,&sch);
    std::cout<<"Current Thread 3 Priority Before: "<<sch.sched_priority<<std::endl;
    sch.sched_priority = sched_get_priority_min(SCHED_FIFO);
    pthread_setschedparam(thread3_handle,SCHED_FIFO,&sch);
    std::cout<<"Current Thread 3 Priority After: "<<sch.sched_priority<<std::endl;

    t2.join();
    t3.join();

    //Thread Affinity(Pinning thread to specific core)
    std::thread t4(ThreadAffinityTest);
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(0,&cpuset);//pin thread to core 0
    auto thread4_handle = t4.native_handle();
    pthread_setaffinity_np(thread4_handle,sizeof(cpu_set_t),&cpuset);//sets thread affinity on Linux
    t4.join();

    return 0;
}