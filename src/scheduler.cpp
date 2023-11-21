#include "scheduler.h"

#include <stdexcept>
#include <iostream>

#include "simulation_results.h"

namespace escalonador
{
    int Scheduler::time_counter_ = 0;

    Scheduler::Scheduler(int num_of_cores, std::list<Task> *&&task_list, SchedulerPolicy policy) : num_of_cores_(num_of_cores)
    {
        // Creates and initializes array of cores
        cores_ = (Core *)malloc(sizeof(Core) * num_of_cores_);
        for (int i = 0; i < num_of_cores_; i++)
            cores_[i] = Core(i);

        task_list_ = task_list;
        task_list = nullptr;

        policy_ = policy;
    }

    Scheduler::~Scheduler()
    {
        free(cores_);
        delete task_list_;
    }

    int Scheduler::getCounter()
    {
        return time_counter_;
    }

    void Scheduler::resetCounter()
    {
        time_counter_ = 0;
    }

    Task *Scheduler::getNextTask()
    {
        Task *next_task;

        if (task_list_->empty())
            return nullptr;

        switch (policy_)
        {
        // Shortest Job First
        case SchedulerPolicy::kSJF:
            next_task = new Task(task_list_->front());
            task_list_->pop_front();
            break;

        // Greatest Job First
        case SchedulerPolicy::kGJF:
            next_task = new Task(task_list_->back());
            task_list_->pop_back();
            break;
        }

        return next_task;
    }

    SimulationResults *Scheduler::simulateProcessing()
    {
        auto is_list_ordered = Scheduler::isListOrdered<Task>(*task_list_);

        if (!is_list_ordered)
            throw std::runtime_error("Erro: A lista de tarefas esta vazia ou nao esta ordenada para a simulacao!");

        std::cout << "A lista de tarefas esta ordenada\n\n";

        int terminated_tasks = 0;
        int const no_of_tasks = (int)task_list_->size();
        auto result_processing = new SimulationResults();

        std::cout << "Nro de tasks: " << no_of_tasks << std::endl;
        std::cout << "Nro de cores: " << num_of_cores_ << "\n\n";

        // Inicializa os núcleos
        for (int i = 0; i < num_of_cores_; ++i)
            cores_[i].setTask(getNextTask());

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
                        result_processing->addCoreResult(cores_[i].getId(), task_done_desc);

                        // Coloca tarefa nova no core
                        cores_[i].setTask(getNextTask());

                        // Incrementa contador de tarefas prontas
                        ++terminated_tasks;
                    }
                }
            }
        }

        result_processing->setTotalTime(time_counter_);
        resetCounter();

        return result_processing;
    }
} // namespace escalonador