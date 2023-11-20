#include "scheduler.h"

#include <stdexcept>
#include <iostream>

namespace escalonador
{
    int Scheduler::time_counter_ = 0;

    Scheduler::Scheduler(int num_of_cores) : num_of_cores_(num_of_cores)
    {
        // Creates and initializes array of cores
        cores_ = (Core *)malloc(sizeof(Core) * num_of_cores_);
        for (int i = 0; i < num_of_cores_; i++)
            cores_[i] = Core(i);
    }

    Scheduler::~Scheduler()
    {
        // Free memory
        free(cores_);
    }

    int Scheduler::getCounter()
    {
        return time_counter_;
    }

    Task *Scheduler::getNextTask(SchedulerPolicy policy, std::list<Task> &task_list)
    {
        Task *next_task;

        if (task_list.empty())
            return nullptr;

        switch (policy)
        {
        // Shortest Job First
        case SchedulerPolicy::kSJF:
            next_task = new Task(task_list.front());
            task_list.pop_front();
            break;

        // Greatest Job First
        case SchedulerPolicy::kGJF:
            next_task = new Task(task_list.back());
            task_list.pop_back();
            break;
        }

        return next_task;
    }

    std::unordered_map<int, std::list<std::string>> *Scheduler::simulateProcessing(std::list<Task> &task_list, Scheduler::SchedulerPolicy policy)
    {
        auto is_list_ordered = Scheduler::isListOrdered<Task>(task_list);

        if (!is_list_ordered)
            throw std::runtime_error("Erro: A lista de tarefas esta vazia ou nao esta ordenada para a simulacao!");

        std::cout << "A lista de tarefas foi ordenada." << std::endl;

        int terminated_tasks = 0;
        int const no_of_tasks = (int)task_list.size();
        auto result_processing = new std::unordered_map<int, std::list<std::string>>();

        std::cout << "Nro de tasks: " << no_of_tasks << std::endl;
        std::cout << "Nro de cores: " << num_of_cores_ << std::endl;

        // Inicializa os núcleos e as listas de resultado
        for (int i = 0; i < num_of_cores_; ++i)
        {
            cores_[i].setTask(getNextTask(policy, task_list));
            result_processing->insert(std::make_pair(cores_[i].getId(), std::list<std::string>()));
        }

        // Executa a simulação até todas as tarefas estarem prontas
        while (terminated_tasks < no_of_tasks)
        {
            ++time_counter_;

            // Verifica os núcleos
            for (int i = 0; i < num_of_cores_; ++i)
            {
                if (cores_[i].isOccupied())
                {
                    cores_[i].process();

                    if (cores_[i].getTask()->isDone())
                    {
                        // Insere descrição da tarefa pronta na lista de resultados do core
                        std::string task_done_desc = cores_[i].getCurrentTaskInfo();
                        result_processing->at(cores_[i].getId()).push_back(task_done_desc);

                        // Coloca tarefa nova no core
                        cores_[i].setTask(getNextTask(policy, task_list));

                        // Incrementa contador de tarefas prontas
                        ++terminated_tasks;
                    }
                }
            }
        }

        return result_processing;
    }
} // namespace escalonador