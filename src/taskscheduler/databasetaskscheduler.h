//
// Created by Howell Young on 2022/5/12.
//

#ifndef FOLKTELL_DATABASETASKSCHEDULER_H
#define FOLKTELL_DATABASETASKSCHEDULER_H
#include <condition_variable>
#include <deque>
#include <functional>
#include <memory>
#include <mutex>
#include <thread>
#include <unordered_map>
#include <vector>
#include <QString>

class DatabaseTaskScheduler {
public:
    DatabaseTaskScheduler();

    ~DatabaseTaskScheduler();
    /**
     * @brief Posts a task to the end of the work queue
     * @param f Member function to be invoked
     * @param args Function arguments
     */
    template<class Fn, class ...Args>
    void post(Fn &&f, Args &&...args)
    {
        std::lock_guard<std::mutex> lock{m_mutex};
        m_tasks.push_back(std::bind(std::forward<Fn>(f), std::forward<Args>(args)...));
        m_cv.notify_one();
    }

    /// Posts a task to the end of the work queue
    void post(std::function<void()> &&work);

    /// Starts the worker thread
    void run();

    /// Stops the worker thread
    void stop();

private:
    /// Main loop of the worker thread
    void workerThread();

private:

    /// Mutex
    mutable std::mutex m_mutex;

    /// Condition variable
    std::condition_variable m_cv;

    /// Worker thread
    std::thread *m_thread;

    /// Pending tasks
    std::deque<std::function<void()>> m_tasks;

    /// Worker flag - when set to false, the worker thread will halt
    bool m_working;
};

#endif //FOLKTELL_DATABASETASKSCHEDULER_H
