#include "scheduler.h"

namespace escalonador
{
    int Scheduler::time_counter_ = 0;

    Scheduler::Scheduler(int core_num)
    {
        core_num_ = core_num;

        // Creates and initializes array of cores
        cores_ = (Core *)malloc(sizeof(Core));
        for (int i = 0; i < core_num_; i++)
            cores_[i] = Core(i);
    }
    
    Scheduler::~Scheduler()
    {
        // Free memory
        free(cores_);
    }

    static int getCounter();
    std::list<std::string> simulateProcessing(std::list<Task> task_list, SchedulerPolicy policy);
} // namespace escalonador