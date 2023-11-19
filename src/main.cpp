#include "../include/file_manager.h"

int main(int argc, char const *argv[])
{
    escalonador::FileManager fm;

    auto task_list = fm.readFile("teste.txt");

    for (auto i : task_list) {
        i.print();
    }

    return 0;
}