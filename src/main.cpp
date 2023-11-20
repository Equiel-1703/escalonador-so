#include <iostream>
#include <list>
#include <unordered_map>
#include <stdexcept>
#include <string>

#include "file_manager.h"
#include "scheduler.h"

int main(int argc, char const *argv[])
{
    if (argc != 3)
    {
        std::cout << "Simulador de escalonador, feito por Henrique Rodrigues. Forma de usar: " << std::endl;
        std::cout << "simulador-so.exe arquivo_com_tarefas.txt nro_de_cores" << std::endl;
        exit(EXIT_SUCCESS);
    }

    // Gerenciador de arquivos
    escalonador::FileManager fm;
    // Escalonador
    escalonador::Scheduler *s;

    try
    {
        const int core_no = std::stoi(argv[2]);
        s = new escalonador::Scheduler(core_no);
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << "Argumento invalido: " << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }

    // Lê lista de tarefas
    auto task_list = fm.readFile(argv[1]);

    std::cout << "Tarefas lidas do arquivo: " << std::endl;

    // Imprimindo tasks lidas
    for (auto i : *task_list)
    {
        i.print();
    }
    std::cout << std::endl;

    std::unordered_map<int, std::list<std::string>> *result;
    try
    {
        result = s->simulateProcessing(*task_list, escalonador::Scheduler::kSJF);

        // Como temos que percorrer cada lista de cada chave, esse laço é O(k * n)
        for (auto it : *result)
        {
            std::cout << "Tarefas realizadas pelo nucleo [" << it.first << "]" << std::endl;
            for (auto it_list : it.second)
            {
                std::cout << it_list << std::endl;
            }
            std::cout << std::endl;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    fm.writeFile("saida.txt", *result);

    delete s;
    delete result;
    delete task_list;

    return 0;
}