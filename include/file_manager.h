#pragma once

#include <fstream>
#include <list>
#include <string>
#include <unordered_map>

#include "task.h"

namespace escalonador
{

    class FileManager
    {
    private:
        std::ifstream file_in;
        std::ofstream file_out;

    public:
        // This method returns a ordered list of tasks
        std::list<Task> *readFile(std::string file_path);
        void writeFile(std::string file_path, std::unordered_map<int, std::list<std::string>> &text);
    };

} // namespace escalonador