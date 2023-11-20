#pragma once

#include <list>
#include <unordered_map>

#include "core.h"
#include "task.h"

namespace escalonador
{
    class Scheduler
    {
    public:
        enum SchedulerPolicy
        {
            kSJF,
            kGJF
        };

    private:
        const int num_of_cores_;
        Core *cores_;
        static int time_counter_;

        // Check if a given list is ordered
        template <typename T>
        bool isListOrdered(const std::list<T>& list) const
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
                if ((*prev_it) <= (*it))
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

        Task *getNextTask(SchedulerPolicy policy, std::list<Task> &task_list);

    public:
        Scheduler(int num_of_cores);
        ~Scheduler();

        static int getCounter();

        // Note: this method only works properly if task_list is ordered!
        std::unordered_map<int, std::list<std::string>> *simulateProcessing(std::list<Task> &task_list, SchedulerPolicy policy);
    };
} // namespace escalonador