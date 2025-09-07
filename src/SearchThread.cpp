#include <iostream>
#include <filesystem>
#include <thread>
#include <vector>
#include <string>
#include "SearchThread.h"

namespace fs = std::filesystem;

void SearchThread::showList() const
{
    std::cout<<" Below are the files list printed from vector"<<std::endl;
    for (auto i=0; i<txtFilelists.size(); i++)
    {
        std::cout<<txtFilelists[i]<<std::endl;
    }
}

void SearchThread::listFilesRecursively(const fs::path& path) {
    try {
        for (const auto& entry : fs::directory_iterator(path)) {
            if (fs::is_regular_file(entry.status())) {
                if (entry.path().extension() == ".txt") {
                    txtFilelists.push_back(entry.path());
                }
            }
            else if (fs::is_directory(entry.status())) {
                listFilesRecursively(entry.path());
            }

        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}
void SearchThread::SearchThreadStart(const std::string& directoryPath)
{
    fs::path initialPath(directoryPath);

    if (fs::exists(initialPath) && fs::is_directory(initialPath)) {
        std::cout << "Listing files in: " << initialPath << std::endl;
        listFilesRecursively(initialPath);
    } else {
        std::cerr << "Error: Directory not found or is not a valid directory." << std::endl;
    }
}
