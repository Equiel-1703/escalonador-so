#include "../include/file_manager.h"
#include "../include/scheduler.h"

int main(int argc, char const *argv[])
{
    // Gerenciador de arquivos
    escalonador::FileManager fm;
    escalonador::Scheduler s(1);

    // Lê lista de tarefas
    auto task_list = fm.readFile("teste.txt");

    // Imprimindo tasks lidas
    for (auto i : *task_list) {
        i.print();
    }

    s.simulateProcessing(*task_list, escalonador::Scheduler::kSJF);

    delete task_list;


    return 0;
}