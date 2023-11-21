#include <iostream>
#include <list>
#include <stdexcept>
#include <string>

#include "file_manager.h"
#include "scheduler.h"
#include "simulation_results.h"

int main(int argc, char const *argv[])
{
    if (argc < 3 || argc > 4)
    {
        std::cout << "Simulador de escalonador, feito por Henrique Rodrigues. Forma de usar: " << std::endl;
        std::cout << "simulador-so.exe <arquivo_com_tarefas.txt> <nro_de_cores> [OPCIONAL]<politica: s(padrao) | g>" << std::endl;
        exit(EXIT_SUCCESS);
    }

    // Gerenciador de arquivos
    escalonador::FileManager fm;

    // Lê lista de tarefas
    auto task_list = fm.readFile(argv[1]);

    std::cout << "Tarefas lidas do arquivo: " << std::endl;

    // Imprimindo tasks lidas
    for (auto i : *task_list)
    {
        i.print();
    }
    std::cout << std::endl;

    // Configurando política
    escalonador::Scheduler::SchedulerPolicy policy = escalonador::Scheduler::kSJF;
    if (argc == 4)
    {
        char pol = argv[3][0];
        switch (pol)
        {
        case 'g':
        case 'G':
            policy = escalonador::Scheduler::kGJF;
            break;
        }
    }

    // Escalonador
    escalonador::Scheduler *s;
    try
    {
        const int core_no = std::stoi(argv[2]);
        s = new escalonador::Scheduler(core_no, std::move(task_list), policy);
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << "Argumento invalido: " << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }

    // Processando e imprimindo resultados
    std::list<std::string> *report;
    try
    {
        auto result = s->simulateProcessing();
        report = result->getReport();
        delete result;

        // Como temos que percorrer cada lista de cada chave, esse laço é O(k * n)
        for (auto it : *report)
            std::cout << it;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    fm.writeFile("saida.txt", *report);

    delete s;
    delete report;

    return 0;
}