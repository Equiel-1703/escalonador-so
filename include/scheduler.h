#pragma once

#include "core.h"
#include "task.h"
#include <list>

namespace escalonador
{
    class Scheduler
    {
    private:
        int num_of_cores_;
        Core *cores_;
        static int time_counter_;

        template <typename T>
        bool isListOrdered(std::list<T> &list)
        {
            if (list.empty())
                return false;

            if (list.size() < 2)
                return true;

            auto prev_it = list.begin();
            auto it = list.begin();
            ++it;
            
            while (it != list.end())
            {
                if ((*prev_it) < (*it))
                {
                    ++prev_it;
                    ++it;
                }
                else
                {
                    return false;
                }
            }

            return true;
        }

    public:
        enum SchedulerPolicy
        {
            kSJF,
            kGJF
        };

        Scheduler(int num_of_cores);
        ~Scheduler();

        static int getCounter();

        // Note: this method only works properly if task_list is ordered!
        std::list<std::string> *simulateProcessing(std::list<Task> &task_list, SchedulerPolicy policy);
    };
} // namespace escalonador