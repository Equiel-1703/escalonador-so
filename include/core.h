#pragma once

#include <string>

#include "task.h"

namespace escalonador
{
    class Core
    {
    private:
        int core_id_;
        Task *current_task_;
        int task_in_;

    public:
        Core(int core_id);

        int getId();
        void setTask(Task *task);
        bool isOccupied();
        Task *getTask();
        void process();
        std::string getCurrentTaskInfo();
    };
} // namespace escalonador