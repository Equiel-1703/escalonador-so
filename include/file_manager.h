#pragma once

#include <fstream>
#include <list>
#include <string>

#include "task.h"

namespace escalonador
{

    class FileManager
    {
    private:
        std::fstream file_in;

    public:
        // This method returns a ordered list of tasks
        std::list<Task> *readFile(std::string file_path);

        
        void writeFile(std::string file_path, std::list<std::string> &text); // Falta implementar
    };

} // namespace escalonador