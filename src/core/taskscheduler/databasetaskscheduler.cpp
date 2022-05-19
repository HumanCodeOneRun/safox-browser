//
// Created by Howell Young on 2022/5/12.
// Modified by Steven Wong on 2022/5/15.
//
#include "databasetaskscheduler.h"
#include <iostream>
DatabaseTaskScheduler::DatabaseTaskScheduler(int _num_threads) :
    m_mutex(),
    m_cv(),
    m_working(false),
    num_threads(_num_threads)
{
}

DatabaseTaskScheduler::~DatabaseTaskScheduler()
{
    stop();
}



void DatabaseTaskScheduler::run()
{
    if (m_working)
        return;

    m_working = true;

    for(int i = 0; i < this->num_threads; i++){
        thread_pool.emplace_back(
            std::thread(&DatabaseTaskScheduler::workerThread, this
        ));
    }
}

void DatabaseTaskScheduler::stop()
{   
    {
        std::unique_lock<std::mutex> lock{m_mutex};
        m_working = false;
    }
    m_cv.notify_all();

    for(auto &thread : thread_pool){
        if(thread.joinable()){
            std::cout << "[thead exit] thread: " << thread.get_id() << " join\n";
            thread.join();
        }
    }

}

void DatabaseTaskScheduler::workerThread()
{
    for (;;)
    {
        std::unique_lock<std::mutex> lock{m_mutex};
        m_cv.wait(lock, [this](){
            return !task_queue.empty() || !m_working;
        });

        if (!m_working && task_queue.empty())
            break;

        auto task = std::move(task_queue.front());
        task_queue.pop_front();

        lock.unlock();

        task();


        if (!m_working && task_queue.empty())
            break;
    }
}

#if defined(_MSC_VER)
void DatabaseTaskScheduler::post(std::function<void()> &&work)
{
    std::lock_guard<std::mutex> lock{m_mutex};
    task_queue.emplace_back(std::move(work));
    m_cv.notify_one();
}
#endif