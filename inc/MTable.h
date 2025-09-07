#ifndef MTABLE_H
#define MTABLE_H

#include <unordered_map>
#include <string>
#include <vector>
#include <mutex>
#include <algorithm>
#include <iostream>

class MTable {
public:
    void addWord(const std::string& word, int count = 1) {
        std::lock_guard<std::mutex> lock(mtx);
        table[word] += count;
    }

    void printTop10() {
        std::lock_guard<std::mutex> lock(mtx);
        std::vector<std::pair<std::string, int>> vec(table.begin(), table.end());

        std::sort(vec.begin(), vec.end(),
                  [](auto& a, auto& b) { return a.second > b.second; });

        std::cout << "\n===== Global Top 10 Words =====\n";
        for (size_t i = 0; i < 10 && i < vec.size(); i++) {
            std::cout << vec[i].first << " : " << vec[i].second << "\n";
        }
        std::cout << "===============================\n";
    }

private:
    std::unordered_map<std::string, int> table;
    std::mutex mtx;
};

#endif // MTABLE_H
