#include "scheduler.h"

#include <stdexcept>
#include <iostream>
#include <memory>

#include "simulation_results.h"

namespace escalonador
{
    int Scheduler::time_counter_ = 0;

    Scheduler::Scheduler(int num_of_cores, std::shared_ptr<std::list<Task>> task_list, SchedulerPolicy policy)
    : num_of_cores_(validateNumOfCores(num_of_cores)), cores_(new Core[num_of_cores_])
    {
        task_list_ = task_list;
        policy_ = policy;
    }

    int Scheduler::getCounter()
    {
        return time_counter_;
    }

    void Scheduler::resetCounter()
    {
        time_counter_ = 0;
    }

    int Scheduler::validateNumOfCores(int val)
    {
        if (val < 1)
            throw std::invalid_argument("O numero de cores nao pode ser menor que 1!");

        return val;
    }

    std::unique_ptr<Task> Scheduler::getNextTask()
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

        return std::unique_ptr<Task>(next_task);
    }

    std::unique_ptr<SimulationResults> Scheduler::simulateProcessing()
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

                    if (cores_[i].getTask().isDone())
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

        return std::unique_ptr<SimulationResults>(result_processing);
    }
} // namespace escalonador