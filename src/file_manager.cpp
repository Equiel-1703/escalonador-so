#include "file_manager.h"

#include <list>
#include <regex>
#include <stdexcept>
#include <iostream>
#include <unordered_map>

namespace escalonador
{

    std::list<Task> *FileManager::readFile(std::string file_path)
    {
        // Cria ponteiro pra lista
        std::list<escalonador::Task> *task_list;

        file_in.open(file_path);

        if (file_in.is_open())
        {
            std::string line;
            std::regex regex("[a-zA-Z0-9]+ \\d+");
            std::smatch result;

            std::string name_task;
            int task_duration;

            // Aloca lista de fato
            task_list = new std::list<escalonador::Task>;

            // Percorre arquivo linha a linha
            while (std::getline(file_in, line))
            {
                // Procurando por padrão na linha atual
                std::regex_search(line, result, regex);

                if (result.empty())
                    continue;

                // Calcula índice do espaço e pega a duração e o nome da tarefa
                int space_index = (int)result.str(0).find_first_of(' ');
                name_task = result.str(0).substr(0, space_index);
                task_duration = std::stoi(result.str(0).substr(space_index + 1));

                // Pega o iterador apontando pro primeiro elemento
                auto it = task_list->begin();

                // Faz it apontar pro priemeiro elemento maior que a tarefa que vamos inserir
                while (it != task_list->end() && task_duration > it->getDuration())
                    ++it;

                // A lista cria uma cópia de Task quando insere, por isso não precisamos alocar memória
                task_list->insert(it, Task(name_task, task_duration));
            }
        }
        else
        {
            std::cerr << "Erro ao abrir arquivo \"" << file_path << "\"" << std::endl;
            throw std::runtime_error("File not found exception");
        }

        file_in.close();

        return task_list;
    }

    void FileManager::writeFile(std::string file_path, std::list<std::string> &text)
    {
        file_out.open(file_path);

        for (auto it : text)
        {
            file_out << it;
        }

        file_out.close();
    }

} // namespace escalonador