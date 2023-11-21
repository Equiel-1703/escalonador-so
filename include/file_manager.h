#pragma once

#include <fstream>
#include <list>
#include <string>
#include <unordered_map>
#include <memory>

#include "task.h"

namespace escalonador
{

    class FileManager
    {
    private:
        std::ifstream file_in_;
        std::ofstream file_out_;

    public:
        // This method returns a ordered list of tasks
        std::shared_ptr<std::list<Task>> readFile(std::string file_path);
        void writeFile(std::string file_path, std::list<std::string> &text);
    };

} // namespace escalonador