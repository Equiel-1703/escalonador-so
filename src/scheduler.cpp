#include <stdexcept>
#include <iostream>

#include "scheduler.h"

namespace escalonador
{
    int Scheduler::time_counter_ = 0;

    Scheduler::Scheduler(int num_of_cores)
    {
        num_of_cores_ = num_of_cores;

        // Creates and initializes array of cores
        cores_ = (Core *)malloc(sizeof(Core));
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

    std::list<std::string> *Scheduler::simulateProcessing(std::list<Task> &task_list, Scheduler::SchedulerPolicy policy)
    {
        auto is_list_ordered = Scheduler::isListOrdered<Task>(task_list);

        if(!is_list_ordered)
            throw std::runtime_error("TaskList is not ordered for scheduling simulation!");
        
        std::cout << "List is ordered" << std::endl;

        
        
        return (std::list<std::string> *) NULL; // placeholder, delete this bitch later
    }
} // namespace escalonador