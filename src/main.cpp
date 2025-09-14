#include <iostream>
#include "filehandler.h"

int main() {
    FileHandler fh{};
    std::vector<std::string> files = fh.getFileList();
    
    for (const auto& file : files){
        std::cout << file << std::endl;
    }

    return 0;
}
