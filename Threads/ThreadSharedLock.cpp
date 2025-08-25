/*
shared_lock allows multiple threads to read shared data concurrently, but only one thread can write to it at a time.
*/

#include<iostream>
#include<thread>
#include<shared_mutex>
#include<chrono>

std::shared_mutex mtx;
int shared_data{1};
bool exit_all_threads{false};

void reader(int id){
    while(!exit_all_threads){
        {
            std::shared_lock<std::shared_mutex> lck(mtx);
            std::cout<<"reader "<<id<<" shared data value: "<<shared_data<<std::endl;
        }//at this point shared_lock will be released and accesed by writer threads to modify values
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void writer(int id){
    int i{0};
    while(i<5){
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));//during this 1000ms reader threads can read values
        {
            std::unique_lock<std::shared_mutex> lck(mtx);//now no reader thread can read values because mutex is locked
            std::cout<<"Thread is locked"<<std::endl;
            ++shared_data;
            std::cout<<"writer "<<id<<" Updated shared value: "<<shared_data<<", Lets sleep for 500 ms no reader thread should run during this time"<<std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            std::cout<<"Thread is Unlocked"<<std::endl;
        }
        ++i;
    }
}

int main(){
    std::thread writers[2];
    std::thread readers[5];
    int id;
    for(id=0;id<2;id++)
        writers[id] = std::thread(writer,id);

    for(id=0;id<5;id++)
        readers[id] = std::thread(reader,id);

    for(id=0;id<2;id++)
        writers[id].join();

    exit_all_threads = true;
    for(id=0;id<5;id++)
        readers[id].join();

    return 0;

}