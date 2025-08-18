/*
RAII(Resource Acquisition Is Initialization)
The core principle of RAII is to tie lifetime of a resource to the lifetime of an object.
Acquisition in constuctor: when an object is created, its constructor is responsible for acquiring the necessary resource.
Release in Destructor: when object goes out of scope, its destructor will be automatically invoked and it is responsible for releasing the acquired resource, ensuring proper cleanup.
Examples of RAII in C++: smart pointers, std::lock_guard, std::unique_lock etc..,
*/

//A simple c++ program demonstrating custom file handling using RAII principles

#include <iostream>
#include <fstream>
#include <string>

class Logger{
    /*
        Logger interface opens a file and provides APIs to do file related operations, 
        once the file usage is done file will be closed. Here lifetime of file object is 
        bound to the lifetime of Logger instance.
    */
    public:
    explicit Logger(std::string path){
        log_file.open(path,std::ios::out | std::ios::app);
        if(!log_file.is_open()){
            std::cerr<<"Unable to open file"<<std::endl;
        }else{
            std::cout<<"File opened successfully"<<std::endl;
        }
    }

    ~Logger(){
        log_file.close();
        if(!log_file.is_open()){
            std::cout<<"File closed successfully"<<std::endl;
        }
    }

    void write(){
        log_file<<"written some data"<<std::endl;
        std::cout<<"data written in file"<<std::endl;
    }
    
    private:
    std::ofstream log_file;

};

int main(){
    Logger* log = new Logger("example.log");
    log->write();
    delete log;
    return 0;
}