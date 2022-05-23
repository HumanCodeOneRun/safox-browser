//
// Created by Howell Young on 2022/5/12.
// Modified by Steven Wong on 2022/5/15
//


#ifndef safox_DATABASETASKSCHEDULER_H
#define safox_DATABASETASKSCHEDULER_H

#include <condition_variable>
#include <deque>
#include <functional>
#include <memory>
#include <mutex>
#include <thread>
#include <unordered_map>
#include <vector>
#include <QString>
#include <QThread>
#include <QDebug>
#include <unordered_map>
#include <future>


class DatabaseTaskScheduler : public QObject {
public:
    DatabaseTaskScheduler(int _num_threads = 4);

    ~DatabaseTaskScheduler();

    #if defined(__clang__) || defined(__GNUC__)
    template<class Fn>
    auto post(Fn &&f) -> std::future<decltype(f())>;

    #endif
    

    #if defined(_MSC_VER)
    template<class Fn, class ...Args>
    void post(Fn &&f, Args &&...args)
    {
        std::lock_guard<std::mutex> lock{m_mutex};
        task_queue.emplace_back(std::bind(std::forward<Fn>(f), std::forward<Args>(args)...));
        m_cv.notify_one();
    }

    /// Posts a task to the end of the work queue
    void post(std::function<void()> &&work);
    #endif


    /// Starts the worker thread
    void run();

    /// Stops the worker thread
    void stop();

private:
    /// Main loop of the worker thread
    void workerThread();

    /// Mutex
    mutable std::mutex m_mutex;

    /// Condition variable
    std::condition_variable m_cv;


    /// Pending tasks
    std::deque<std::packaged_task<void()> > task_queue;

    
    /// Worker flag - when set to false, the worker thread will halt
    volatile bool m_working;

    std::vector<std::thread> thread_pool;

    int num_threads;

};

#if defined(__clang__) || defined(__GNUC__)

template<class Fn>
auto DatabaseTaskScheduler::post(Fn &&f) -> std::future<decltype(f())> {
//decltype(auto) DatabaseTaskScheduler::post(Fn &&f, Args&&... args){

    using return_type = decltype(f());

    std::packaged_task<return_type()> task(
            //std::bind(std::forward<Fn>(f), std::forward<Args>(args)...)
            std::forward<Fn>(f)
    );

    
    std::future<return_type> ret = task.get_future();
    
    {
        std::unique_lock<std::mutex> lock{m_mutex};

        task_queue.emplace_back(std::move(task));
    }

    m_cv.notify_one();

    return ret;
}


#endif





#endif //safox_DATABASETASKSCHEDULER_H
