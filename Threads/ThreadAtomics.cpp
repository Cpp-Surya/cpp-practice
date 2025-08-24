#include<atomic>
#include<iostream>
#include<chrono>
#include<thread>

std::atomic<int> val{0};

void f1(){
    val.store(0);
    val.wait(0);
    std::cout<<"f1 atomic value: "<<val.load()<<std::endl;
}

void f2(){
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout<<"Unblocking .."<<std::endl;
    val.store(32);
    val.notify_one();
}

int main(){
    auto v = val.load();
    std::cout<<"atomic value: "<<v<<std::endl;
    val.store(5);
    v = val.load();
    std::cout<<"atomic value: "<<v<<std::endl;
    val.store(8);
    v = val.load();
    std::cout<<"atomic value: "<<v<<std::endl;
    auto current_v = val.exchange(98);
    std::cout<<"current_v: "<<current_v<<std::endl;
    v = val.load();
    std::cout<<"atomic value: "<<v<<std::endl;
    current_v = val.fetch_add(1);
    std::cout<<"current_v: "<<current_v<<std::endl;
    v = val.load();
    std::cout<<"atomic value: "<<v<<std::endl;
    std::thread t1(f1);
    std::thread t2(f2);
    t1.join();
    t2.join();
    return 0;
}