#include "core.h"
#include "task.h"
#include <list>

namespace escalonador
{
    class Scheduler
    {
    private:
        int core_num_;
        Core *cores_;
        static int time_counter_;

    public:
        enum SchedulerPolicy
        {
            kSJF,
            kGJF
        };

        Scheduler(int core_num);
        ~Scheduler();

        static int getCounter();
        std::list<std::string> simulateProcessing(std::list<Task> task_list, SchedulerPolicy policy);
    };
} // namespace escalonador