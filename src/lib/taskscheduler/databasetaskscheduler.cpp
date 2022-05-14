//
// Created by Howell Young on 2022/5/12.
//
#include "databasetaskscheduler.h"

DatabaseTaskScheduler::DatabaseTaskScheduler() :
    m_mutex(),
    m_cv(),
    m_thread(nullptr),
    m_tasks(),
    m_working(false)
{}

DatabaseTaskScheduler::~DatabaseTaskScheduler()
{
    stop();
}

void DatabaseTaskScheduler::post(std::function<void()> &&work)
{
    std::lock_guard<std::mutex> lock{m_mutex};
    m_tasks.push_back(std::move(work));
    m_cv.notify_one();
}

void DatabaseTaskScheduler::run()
{
    if (m_thread != nullptr || m_working)
        return;

    m_working = true;
    m_thread = new std::thread(&DatabaseTaskScheduler::workerThread, this);
}

void DatabaseTaskScheduler::stop()
{
    if (m_thread != nullptr)
    {
        m_working = false;
        m_cv.notify_all();

        if (m_thread->joinable())
            m_thread->join();

        delete m_thread;
        m_thread = nullptr;
    }
}

void DatabaseTaskScheduler::workerThread()
{
    for (;;)
    {
        std::unique_lock<std::mutex> lock{m_mutex};
        m_cv.wait(lock, [this](){
            return !m_tasks.empty() || !m_working;
        });

        if (!m_working && m_tasks.empty())
            break;

        std::function<void()> task = std::move(m_tasks.front());
        m_tasks.pop_front();
        lock.unlock();

        task();

        if (!m_working && m_tasks.empty())
            break;
    }
}
