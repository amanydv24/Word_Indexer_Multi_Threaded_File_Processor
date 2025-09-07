#ifndef SEARCHTHREAD_H
#define SEARCHTHREAD_H

#include <string>
#include <thread>
#include <vector>
#include <filesystem>
namespace fs = std::filesystem;


class SearchThread {
public:
    SearchThread() = default;
    void SearchThreadStart(const std::string& rootPath);
    void listFilesRecursively(const fs::path& path);
    void showList() const;
    const std::vector<std::string>& getFileList() const 
    {
        return txtFilelists;
    }   

private:
    std::vector <std::string> txtFilelists;

};

#endif //SEARCHTHREAD_H