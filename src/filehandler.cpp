#include <vector>
#include <string>
#include "filehandler.h"
#include <filesystem>


   
std::vector<std::string> FileHandler::getFileList(){

    std::vector<std::string> paths{};
    for (auto const& entry : std::filesystem::directory_iterator{"."}){
        paths.push_back(entry.path());
    }

    return paths;
}


