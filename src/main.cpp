#include "../include/file_manager.h"

int main(int argc, char const *argv[])
{
    // Gerenciador de arquivos
    escalonador::FileManager fm;

    // Lê lista de tarefas
    auto task_list = fm.readFile("teste.txt");

    // Imprimindo tasks lidas
    for (auto i : task_list) {
        i.print();
    }

    

    return 0;
}