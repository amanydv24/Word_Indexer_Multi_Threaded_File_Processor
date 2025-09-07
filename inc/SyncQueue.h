#ifndef SYNQQUEUE_H
#define SYNQQUEUE_H

#include <queue>
#include <string>
#include <mutex>
#include <condition_variable>

class SyncQueue {
public:
    SyncQueue() = default;
    ~SyncQueue() = default;

    void push(const std::string& item);
    bool pop(std::string& item);
    void close();

private:
    std::queue<std::string> queue_;
    std::mutex mutex_;
    std::condition_variable condVar_;
    bool closed_ = false;
};

#endif //SYNQQUEUE_H