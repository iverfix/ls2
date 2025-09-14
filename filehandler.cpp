#include <vector>
#include <string>
#include "filehandler.h"
#include <filesystem>
#include <iostream>


   
std::vector<std::string> FileHandler::getFileList(){

    std::vector<std::string> paths{};
    for (auto const& entry : std::filesystem::directory_iterator{"."}){
        paths.push_back(entry.path());
        std::cout << "Her da folkens" << std::endl;
    }

    return paths;
}


