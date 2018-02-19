//
// Created by loic lopez on 23/01/2018.
//

#include <Thread/ThreadPool.hpp>
#include <iostream>
#include <Core/ServerCore.hpp>
#include <Exception/ZiaException.hpp>

ThreadPool::ThreadPool(int threads) : shutdown_(false)
{
    this->threads_.reserve(threads);

    for (int i = 0; i < threads; i++) {
        try {
            this->threads_.emplace_back(std::bind(&ThreadPool::threadRun, this));
        } catch (ZiaException const& e) {
            std::cerr <<  e.what() << std::endl;
            exit(84);
        }
    }

}

ThreadPool::~ThreadPool()
{
    {
        std::unique_lock<std::mutex> lock(this->lock_);
        this->shutdown_ = true;
        this->condVar_.notify_all();
    }

    for (auto& thread : this->threads_)
        thread.join();
}

void	ThreadPool::doJob(std::function <void ()> func)
{
    std::unique_lock<std::mutex>		lock(lock_);

    this->jobs_.emplace(func);
    this->condVar_.notify_one();
}

void	ThreadPool::threadRun()
{
    std::function<void ()>	job;

    while (true)
    {
        {
            std::unique_lock <std::mutex> lock (this->lock_);

            while (!this->shutdown_ && this->jobs_.empty())
                this->condVar_.wait(lock);

            if (this->jobs_.empty())
                return;

            job = std::move(this->jobs_.front());
            this->jobs_.pop();
        }

        if (this->lock_.try_lock())
        {
            job();
            this->lock_.unlock();
        }
    }
}
