#include <thread> 
#include <string> 
#include <iostream>
#include "SearchThread.h" 
#include "WorkerThread.h"
#include "SyncQueue.h"
#include "MTable.h"

void producer(SyncQueue& queue, const std::vector<std::string>& files) {
    for (const auto& f : files) {
        std::cout << "[Producer] -> " << f << "\n";
        queue.push(f);
    }
    queue.close(); // signal no more files
    std::cout << "[Producer] All files pushed. Queue closed.\n";
}

void worker(SyncQueue& queue, int id, WorkerThread& manager) {
    std::string file;
    while (queue.pop(file)) {
        std::cout << "[Worker " << id << "] <- " << file << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        manager.processFile(file);   // process file (count top words)
    }
    auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::cout << "[Worker " << id << "] Queue closed. Exiting.\n";
}

int main() { 
    std::string directoryPath; 
    std::cout << "Enter the directory path to list files: "; 
    std::getline(std::cin, directoryPath);

    SearchThread searchThread; 
    std:: thread t1(&SearchThread::SearchThreadStart, &searchThread, directoryPath); 
    t1.join(); 
    searchThread.showList(); 

    SyncQueue queue;

    const auto& files = searchThread.getFileList();
    if (files.empty()) {
        std::cout << "No .txt files found.\n";
        return 0;
    }

    std::thread prodThread(producer, std::ref(queue), std::ref(files));

    MTable globalTable;
    WorkerThread manager(globalTable);

    std::thread w1(worker, std::ref(queue), 1, std::ref(manager));
    std::thread w2(worker, std::ref(queue), 2, std::ref(manager));
    std::thread w3(worker, std::ref(queue), 3, std::ref(manager));

    prodThread.join();
    w1.join();
    w2.join();
    w3.join();

    globalTable.printTop10();
    std::cout << "All threads finished.\n";

    return 0; 
}
