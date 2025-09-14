#include <iostream>
#include "filehandler.h"

int main() {
    FileHandler fh{};
    std::vector<std::string> files = fh.getFileList();
    
    std::cout << "Hei verden " << files.size() <<std::endl;

    for (const auto& file : files){
        std::cout << file << std::endl;
    }

    return 0;
}
