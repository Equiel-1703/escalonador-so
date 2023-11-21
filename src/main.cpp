#include <iostream>
#include <list>
#include <stdexcept>
#include <string>
#include <memory>

#include "file_manager.h"
#include "scheduler.h"
#include "simulation_results.h"

int main(int argc, char const *argv[])
{
    if (argc < 3 || argc > 4)
    {
        std::cout << "Simulador de escalonador, feito por Henrique Rodrigues." << std::endl
                  << "Forma de usar: \n\n";
        std::cout << "simulador-so.exe <arquivo_com_tarefas.txt> <nro_de_cores> [OPCIONAL]<politica: s(padrao) | g>" << std::endl;
        return EXIT_SUCCESS;
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
    std::unique_ptr<escalonador::Scheduler> s;
    try
    {
        const int core_no = std::stoi(argv[2]);
        s = std::make_unique<escalonador::Scheduler>(core_no, task_list, policy);
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << "Argumento invalido!" << std::endl
                  << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    // Processando e imprimindo resultados
    std::unique_ptr<std::list<std::string>> report;
    try
    {
        auto result = s->simulateProcessing();
        report = std::move(result->getReport());
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

        // Como temos que percorrer cada lista de cada chave, esse laço é O(k * n)
    for (auto it : *report)
        std::cout << it;

    fm.writeFile("saida.txt", *report);

    return 0;
}