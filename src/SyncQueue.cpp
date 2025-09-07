// inc/SyncQueue.h
#pragma once
#include <queue>
#include <mutex>
#include <condition_variable>
#include <string>
#include "SyncQueue.h"

void SyncQueue::push(const std::string& item) {
    {
        std::unique_lock<std::mutex> lock(mutex_);
        queue_.push(item);
    }
    condVar_.notify_one();
}

bool SyncQueue::pop(std::string& item) {
    std::unique_lock<std::mutex> lock(mutex_);
    condVar_.wait(lock, [this] { return !queue_.empty() || closed_; });

    if (queue_.empty() && closed_) {
        return false; // no more items
    }

    item = queue_.front();
    queue_.pop();
    return true;
}

void SyncQueue::close() {
    {
        std::unique_lock<std::mutex> lock(mutex_);
        closed_ = true;
    }
    condVar_.notify_all();
}