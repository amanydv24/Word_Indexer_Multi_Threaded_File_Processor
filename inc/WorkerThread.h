#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include <string>
#include <vector>
#include <mutex>
#include "MTable.h"

class WorkerThread {
public:
    WorkerThread(MTable& t) : mtable(t) {};
    ~WorkerThread() = default;

    void processFile(const std::string& filePath);

private:
    std::mutex coutMutex;
    MTable& mtable;
   
    std::string normalizeWord(const std::string& word);
};

#endif // WORKERTHREAD_H
