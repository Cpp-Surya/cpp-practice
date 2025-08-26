/*
Thread Pool maintains a set of pre-created threads and those threads can be reused again to do many tasks concurrently. This reduces overhead that costs us due to the creation and destruction of threads.
*/

#include<thread>
#include<vector>
#include<mutex>
#include<condition_variable>
#include<functional>
#include<queue>
#include<iostream>


class ThreadPool{
    public:
        ThreadPool(const int no_of_threads)
        {
            for(int i=0;i<no_of_threads;i++)
            {
                threads.emplace_back([this]{
                    auto thread_id = std::this_thread::get_id();
                    while (true)
                    {
                        std::function<void()> task;
                        {
                            std::unique_lock<std::mutex> lck(mtx);
                            //Block this thread until task is available
                            std::cout<<thread_id<<" Thread is blocked, since no task is available"<<std::endl;
                            cv.wait(lck,[this]{return !task_queue.empty() || stop;});
                            
                            if(task_queue.empty() && stop){
                                //stop requested
                                return;
                            }
                            std::cout<<thread_id<<" Thread unblocked, task is available"<<std::endl;
                            task = std::move(task_queue.front());
                            task_queue.pop();

                        } 
                        std::cout<<thread_id<<" executing task"<<std::endl;
                        task();//Executes task
                    }
                    
                });
            }
        }

        ~ThreadPool()
        {
            {
                std::unique_lock<std::mutex> lck(mtx);
                stop = true;//stop all threads
            }
            cv.notify_all();
            for(auto& t : threads)
            {
                std::cout<<"Stopping thread: "<<t.get_id()<<std::endl;
                t.join();
            }
        }

        void enqueue(std::function<void()> task)
        {
            {
                std::unique_lock<std::mutex> lck(mtx);
                task_queue.emplace(std::move(task));
            }
            cv.notify_one();
        }
    
    private:
        std::vector<std::thread> threads;
        std::mutex mtx;
        std::condition_variable cv;
        std::queue<std::function<void()>> task_queue;
        bool stop{false};
};

int main()
{
    int n = std::thread::hardware_concurrency();
    std::cout<<"Max allowed threads: "<<n<<std::endl;
    ThreadPool* pool = new ThreadPool(n);
    for(int i=0;i<5;i++)
    {
        pool->enqueue([i]{
            std::cout<<"Task "<<i<<" is running"<<std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        });
    }
    delete pool;
    
    return 0;
}