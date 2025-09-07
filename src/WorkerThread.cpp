#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <map>
#include "WorkerThread.h"

void WorkerThread::processFile(const std::string& filePath) {
    std::ifstream inFile(filePath);
    if (!inFile) {
        std::lock_guard<std::mutex> lock(coutMutex);
        std::cerr << "[Error] Cannot open file: " << filePath << "\n";
        return;
    }

    std::map<std::string, int> wordCount;
    std::string word;

    while (inFile >> word) {
        word = normalizeWord(word);
        if (!word.empty()) {
            wordCount[word]++;
            mtable.addWord(word);
        }
    }

    std::vector<std::pair<std::string, int>> sortedWords(wordCount.begin(), wordCount.end());
    std::sort(sortedWords.begin(), sortedWords.end(),
              [](const auto& a, const auto& b) {
                  return a.second > b.second;
              });

    std::lock_guard<std::mutex> lock(coutMutex);
    std::cout << "----------------------\n";

}

std::string WorkerThread::normalizeWord(const std::string& word) {
    std::string cleaned;
    for (char c : word) {
        if (std::isalpha(static_cast<unsigned char>(c))) {
            cleaned += std::tolower(static_cast<unsigned char>(c));
        }
    }
    return cleaned;
}
