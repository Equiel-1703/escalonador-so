#pragma once

#include <list>
#include <unordered_map>

#include "core.h"
#include "task.h"
#include "simulation_results.h"

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
        std::list<Task> *task_list_;
        SchedulerPolicy policy_;

        // Check if a given list is ordered
        template <typename T>
        bool isListOrdered(const std::list<T> &list) const
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

        Task *getNextTask();

    public:
        Scheduler(int num_of_cores, std::list<Task> *&&task_list, SchedulerPolicy policy);
        ~Scheduler();

        static int getCounter();
        static void resetCounter();

        // Note: this method only works properly if task_list is ordered!
        SimulationResults *simulateProcessing();
    };
} // namespace escalonador