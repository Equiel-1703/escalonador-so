#include "task.h"
#include <fstream>
#include <list>
#include <string>

namespace escalonador
{

    class FileManager
    {
    private:
        std::fstream file_in;

    public:
        std::list<Task> &readFile(std::string file_path);
        void writeFile(std::string file_path, std::list<std::string> &text); // Falta implementar
    };

} // namespace escalonador